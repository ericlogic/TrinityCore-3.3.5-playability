#include "Bag.h"
#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "CraftsmanRecipeMgr.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "StringFormat.h"
#include "Spell.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Trainer.h"
#include "WorldSession.h"

uint32 GetSpellArtifactId(const SpellInfo *spell)
{
    for (uint8 i = 0; i != MAX_SPELL_EFFECTS; ++i)
    {
        switch (spell->_effects[i].Effect)
        {
            case SPELL_EFFECT_CREATE_ITEM:
            case SPELL_EFFECT_CREATE_ITEM_2:
                return spell->_effects[i].ItemType;
            default:
                break;
        }
    }

    return 0;
}

uint32 GetSpellPriceByRank(uint32 rank)
{
    if (rank > 425) return 1500000;
    if (rank > 350) return 750000;
    if (rank > 300) return 250000;
    if (rank > 275) return 80000;
    if (rank > 200) return 50000;
    if (rank > 125) return 10000;
    if (rank >  50) return 1500;
    return 200;
}

bool CheckReagentsForPlayer(Player *player, const Reagents& reagents, uint32 count)
{
    for (Reagents::const_iterator it = reagents.begin(); it != reagents.end(); ++it)
    {
        if (!player->HasItemCount(it->first, it->second * count))
        {
            return false;
        }
    }
    return true;
}

bool CheckInventorySlotForPlayer(Player* player, uint32 itemId, uint32 count, ItemPosCountVec* dest = nullptr)
{
    ItemPosCountVec ipcv;
    if (dest == nullptr)
        dest = &ipcv;

    uint32 no_space;
    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, *dest, itemId, count, &no_space);
    return msg == EQUIP_ERR_OK;
}

void TakeReagentsFromPlayer(Player *player, Reagents reagents, uint32 count)
{
    for (Reagents::const_iterator it = reagents.begin(); it != reagents.end(); ++it)
    {
        player->DestroyItemCount(it->first, it->second * count, true, false);
    }
}

std::string GetItemLink(Player const* forPlayer, ItemTemplate const* item)
{
    std::ostringstream oss;
    LocaleConstant locale = forPlayer->GetSession()->GetSessionDbcLocale();

    //color
    oss << "|c";
    switch (item->Quality)
    {
        case ITEM_QUALITY_POOR:     oss << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   oss << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: oss << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     oss << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     oss << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY:oss << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: oss << "ffe6cc80"; break;  //LIGHT YELLOW
        case ITEM_QUALITY_HEIRLOOM: oss << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    oss << "ff000000"; break;  //UNK BLACK
    }
    oss << "|Hitem:" << uint32(item->ItemId) << ':';

    //permanent enchantment, 3 gems, 4 unknowns, reporter_level (9)
    oss << "0:0:0:0:0:0:0:0:0";

    //name
    std::string name = item->Name1;
    ItemLocale const* itemInfo = sObjectMgr->GetItemLocale(item->ItemId);
    if (locale > 0 && itemInfo && !itemInfo->Name[locale].empty())
        name = itemInfo->Name[locale];

    oss << "|h[" << name << "]|h|r";
    return oss.str();
}

std::string GetItemLink(const Player* forPlayer, uint32 itemId)
{
    ItemTemplate const* item = sObjectMgr->GetItemTemplate(itemId);
    return GetItemLink(forPlayer, item);
}

bool IsRecipe(const Item* item, uint32 subclass)
{
    const ItemTemplate* tpl = item->GetTemplate();
    return tpl->Class == ITEM_CLASS_RECIPE && tpl->SubClass == subclass;
}


bool CraftsmanBaseAI::OnGossipHello(Player* player)
{
    SendMainGossipMenuFor(player);
    return true;
}

bool CraftsmanBaseAI::OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId)
{
    uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
    uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
    switch (sender)
    {
        case GOSSIP_SENDER_CRAFTSMAN_MAIN:
            HandleMainSenderAction(player, action);
            break;
        case GOSSIP_SENDER_CRAFTSMAN_RECIPES:
            HandleRecipesSenderAction(player, action);
            break;
        case GOSSIP_SENDER_CRAFTSMAN_OFFER_RECIPE:
            HandleOfferRecipeSenderAction(player, action);
            break;
        case GOSSIP_SENDER_CRAFTSMAN_BUSY:
            HandleBusySenderAction(player, action);
            break;
        case GOSSIP_SENDER_CRAFTSMAN_ALREADY_LEARNED:
            HandleAlreadyLearnedSenderAction(player, action);
            break;
        case GOSSIP_SENDER_CRAFTSMAN_RECIPE_LEARNED:
            HandleRecipeLearnedSenderAction(player, action);
            break;
        default:
            player->OnGossipSelect(me, gossipListId, menuId);
            break;
    }
    return true;
}

bool CraftsmanBaseAI::OnGossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, char const* code)
{
    uint32 const sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
    uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
    switch (sender)
    {
        case GOSSIP_SENDER_CRAFTSMAN_RECIPES:
            HandleRecipesSenderAction(player, action, code);
            break;
        default:
            break;
    }
    return true;
}

void CraftsmanBaseAI::SpellHitTarget(WorldObject* wtarget, SpellInfo const* spell)
{
    // Get and clear order information
    Player* player = this->customer;
    this->customer = nullptr;
    Reagents reagents = this->reagents;
    this->reagents.clear();
    uint32 artifactId = this->artifactId;
    this->artifactId = 0;
    uint32 count = this->count;
    this->count = 0;
    uint32 cost = this->cost;
    this->cost = 0;

    // Check customer
    if (player == nullptr || !player->IsInWorld())
        return;

    // Check reagents
    if (!CheckReagentsForPlayer(player, reagents, count))
    {
        CloseGossipMenuFor(player);
        WhisperNeedReagentFor(player, artifactId, reagents);
        return;
    }

    // Check money.
    if (player->GetMoney() < cost) {
        CloseGossipMenuFor(player);
        player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, nullptr, 0, 0);
        return;
    }

    // Check and find slots for created items
    ItemPosCountVec dest;
    if (!CheckInventorySlotForPlayer(player, artifactId, count, &dest))
    {
        CloseGossipMenuFor(player);
        WhisperNotEnoughSlotFor(player);
        return;
    }

    // Take reagents
    TakeReagentsFromPlayer(player, reagents, count);

    // Take money
    player->ModifyMoney(-cost);

    // Create new items for customer.
    Item* pItem = player->StoreNewItem(dest, artifactId, true, 0);
    player->SendNewItem(pItem, count, true, false, true);
}

void CraftsmanBaseAI::SendMainGossipMenuFor(Player* player)
{
    player->PrepareGossipMenu(me, me->GetCreatureTemplate()->GossipMenuId, true);
    PrepareMainMenuItems(player);
    player->SendPreparedGossip(me);
}

void CraftsmanBaseAI::SendRecipeGossipMenuFor(Player* player, std::string keyword)
{
    ClearGossipMenuFor(player);

    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();

    std::string searchText = sCraftsmanTextMgr->GetText(locale, CMTEXT_INPUT_KEYWORD);
    if (!keyword.empty())
        searchText = fmt::format(sCraftsmanTextMgr->GetText(locale, CMTEXT_CURRENT_KEYWORD), keyword);

    AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, searchText, GOSSIP_SENDER_CRAFTSMAN_RECIPES, GOSSIP_ACTION_OEM_SERVICE, "", 0, true);

    if (PrepareRecipeMenuItems(player, keyword) == 0)
        PrepareDefaultRecipeMenuItems(player);

    if (recipeSubclass != 0)
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, sCraftsmanTextMgr->GetText(locale, CMTEXT_OFFER_RECIPE), GOSSIP_SENDER_CRAFTSMAN_RECIPES, GOSSIP_ACTION_OFFER_RECIPE);

    std::string backText = sCraftsmanTextMgr->GetText(locale, CMTEXT_BACK);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, backText, GOSSIP_SENDER_CRAFTSMAN_RECIPES, GOSSIP_ACTION_BACK);

    SendGossipMenuFor(player, GOSSIP_TEXT_CRAFTSMAN_RECIPES, me);
}

void CraftsmanBaseAI::SendOfferRecipeGossipMenuFor(Player* player)
{
    // Clear menu.
    ClearGossipMenuFor(player);

    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();

    std::vector<const ItemTemplate*> recipes;
    // Find recipes in inventory(backpack).
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
    {
        const Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!item || !IsRecipe(item, recipeSubclass))
            continue;
        recipes.push_back(item->GetTemplate());
    }
    // Find recipes in bags
    for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
    {
        if (Bag* bag = player->GetBagByPos(i))
        {
            for (uint32 j = 0; j < bag->GetBagSize(); j++)
            {
                const Item* item = player->GetItemByPos(i, j);
                if (!item || !IsRecipe(item, recipeSubclass))
                    continue;
                recipes.push_back(item->GetTemplate());
            }
        }
    }

    // Add gossip menus.
    for (std::vector<const ItemTemplate*>::iterator it = recipes.begin(); it != recipes.end(); ++it)
    {
        std::string name = (*it)->Name1;
        ItemLocale const* itemInfo = sObjectMgr->GetItemLocale((*it)->ItemId);
        if (locale > 0 && itemInfo && !itemInfo->Name[locale].empty())
            name = itemInfo->Name[locale];
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, name, GOSSIP_SENDER_CRAFTSMAN_OFFER_RECIPE, (*it)->ItemId);
    }

    // Add back menu.
    std::string backText = sCraftsmanTextMgr->GetText(locale, CMTEXT_BACK);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, backText, GOSSIP_SENDER_CRAFTSMAN_OFFER_RECIPE, GOSSIP_ACTION_BACK);

    // Send to client.
    SendGossipMenuFor(player, GOSSIP_TEXT_CRAFTSMAN_OFFER_RECIPE, me);
}

void CraftsmanBaseAI::SendBusyGossipMenuFor(Player* player)
{
    ClearGossipMenuFor(player);

    std::string backText = sCraftsmanTextMgr->GetText(player, CMTEXT_WELL);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, backText, GOSSIP_SENDER_CRAFTSMAN_BUSY, GOSSIP_ACTION_BACK);

    SendGossipMenuFor(player, GOSSIP_TEXT_CRAFTSMAN_BUSY, me);
}

void CraftsmanBaseAI::SendAlreadyLearnedGossipMenuFor(Player* player)
{
    ClearGossipMenuFor(player);

    std::string backText = sCraftsmanTextMgr->GetText(player, CMTEXT_WELL);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, backText, GOSSIP_SENDER_CRAFTSMAN_ALREADY_LEARNED, GOSSIP_ACTION_BACK);

    SendGossipMenuFor(player, GOSSIP_TEXT_CRAFTSMAN_ALREADY_LEARNED, me);
}

void CraftsmanBaseAI::SendRecipeLearnedGossipMenuFor(Player* player)
{
    ClearGossipMenuFor(player);

    std::string backText = sCraftsmanTextMgr->GetText(player, CMTEXT_UR_WELCOME);
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, backText, GOSSIP_SENDER_CRAFTSMAN_RECIPE_LEARNED, GOSSIP_ACTION_BACK);

    SendGossipMenuFor(player, GOSSIP_TEXT_CRAFTSMAN_RECIPE_LEARNED, me);
}

void CraftsmanBaseAI::HandleMainSenderAction(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_OEM_SERVICE:
            SendRecipeGossipMenuFor(player, "");
            break;
        default:
            break;
    }
}

void CraftsmanBaseAI::HandleRecipesSenderAction(Player* player, uint32 action, const char* code)
{
    switch (action)
    {
        case GOSSIP_ACTION_OEM_SERVICE:
            SendRecipeGossipMenuFor(player, code ? code : "");
            break;
        case GOSSIP_ACTION_OFFER_RECIPE:
            SendOfferRecipeGossipMenuFor(player);
            break;
        case GOSSIP_ACTION_BACK:
            SendMainGossipMenuFor(player);
            break;
        default:
            CastCreateItemSpellFor(player, action, 1);
            break;
    }
}

void CraftsmanBaseAI::HandleOfferRecipeSenderAction(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_BACK:
            SendRecipeGossipMenuFor(player, "");
            break;
        default:
            LearnRecipeFor(player, action);
            break;
    }
}

void CraftsmanBaseAI::HandleBusySenderAction(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_BACK:
            SendMainGossipMenuFor(player);
            break;
        default:
            break;
    }
}

void CraftsmanBaseAI::HandleAlreadyLearnedSenderAction(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_BACK:
            SendOfferRecipeGossipMenuFor(player);
            break;
        default:
            break;
    }
}

void CraftsmanBaseAI::HandleRecipeLearnedSenderAction(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_BACK:
            SendOfferRecipeGossipMenuFor(player);
            break;
        default:
            break;
    }
}

void CraftsmanBaseAI::CastCreateItemSpellFor(Player* player, uint32 spellId, uint32 count)
{
    // Get spell info and artifactId
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    uint32 artifactId = GetSpellArtifactId(spellInfo);

    // Calculate reagents and price
    Reagents reagents;
    uint32 cost = GetSpellPrice(spellId);
    cost += GetReagents(spellInfo, reagents);

    // Check reagents
    if (!CheckReagentsForPlayer(player, reagents, count))
    {
        CloseGossipMenuFor(player);
        WhisperNeedReagentFor(player, artifactId, reagents);
        return;
    }

    // Is busy for another order
    if (customer != nullptr)
    {
        SendBusyGossipMenuFor(player);
        return;
    }

    // Check slots for created items
    if (!CheckInventorySlotForPlayer(player, artifactId, count))
    {
        CloseGossipMenuFor(player);
        WhisperNotEnoughSlotFor(player);
        return;
    }

    // Record order info
    this->customer = player;
    this->reagents = reagents;
    this->artifactId = artifactId;
    this->count = count;
    this->cost = cost;

    // Cast spell (npc animation)
    Spell* spell = new Spell(me, spellInfo, TRIGGERED_NONE, player->GetGUID());
    SpellCastTargets targets;
    spell->prepare(targets);

    // Close gossip menu and whisper to customer
    CloseGossipMenuFor(player);
    WhisperStartWorkingFor(player, artifactId);
}

void CraftsmanBaseAI::LearnRecipeFor(Player* player, uint32 recipeId)
{
    if (!player->HasItemCount(recipeId, 1)) {
        CloseGossipMenuFor(player);
        WhisperNoSuchItemFor(player);
        return;
    }

    if (sCraftsmanRecipeMgr->GetRecipeById(player, recipeId))
    {
        SendAlreadyLearnedGossipMenuFor(player);
        return;
    }

    sCraftsmanRecipeMgr->AddRecipeForPlayer(player, recipeId);
    player->DestroyItemCount(recipeId, 1, true, false);
    SendRecipeLearnedGossipMenuFor(player);
}

void CraftsmanBaseAI::WhisperNeedReagentFor(Player* player, uint32 artifactId, const Reagents& reagents)
{
    const std::string& needReagentsText = sCraftsmanTextMgr->GetText(player, CMTEXT_NEED_REAGNETS);

    std::string artifactText = GetItemLink(player, artifactId);

    std::ostringstream oss;
    for (Reagents::const_iterator it = reagents.begin(); it != reagents.end(); ++it)
    {
        if (it != reagents.begin())
            oss << ", ";
        oss << GetItemLink(player, it->first) << 'x' << it->second;
    }
    std::string reagentsText = oss.str();

    std::string message = fmt::format(needReagentsText, artifactText, reagentsText);
    me->Whisper(message, LANG_UNIVERSAL, player);
}

void CraftsmanBaseAI::WhisperNotEnoughSlotFor(Player* player)
{
    me->Whisper(sCraftsmanTextMgr->GetText(player, CMTEXT_NOT_ENOUGH_SLOT), LANG_UNIVERSAL, player);
}

void CraftsmanBaseAI::WhisperStartWorkingFor(Player* player, uint32 artifactId)
{
    const std::string& workingText = sCraftsmanTextMgr->GetText(player, CMTEXT_START_WORKING);
    std::string message = fmt::format(workingText, GetItemLink(player, artifactId));
    me->Whisper(message, LANG_UNIVERSAL, player);
}

void CraftsmanBaseAI::WhisperNoSuchItemFor(Player* player)
{
    me->Whisper(sCraftsmanTextMgr->GetText(player, CMTEXT_NO_SUCH_ITEM), LANG_UNIVERSAL, player);
}

uint CraftsmanBaseAI::PrepareRecipeMenuItems(Player* player, std::string keyword)
{
    if (trainerId == 0 || keyword.empty())
        return 0;

    const Trainer::Trainer* trainer = sObjectMgr->GetTrainer(trainerId);
    if (trainer == nullptr)
        return 0;

    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();

    int matched = 0;

    const std::vector<CraftsmanRecipe>& recipes = sCraftsmanRecipeMgr->GetRecipesByPlayer(player);
    for (std::vector<CraftsmanRecipe>::const_iterator it = recipes.begin(); it != recipes.end() && matched < 10; ++it)
    {
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(it->spellId);
        if (spellInfo == nullptr)
            continue;

        std::string name = it->name;
        if (name.find(keyword) == std::string::npos)
            continue;

        uint32 price = GetSpellPriceByRank(it->skillRank);
        Reagents reagents;
        price += GetReagents(spellInfo, reagents);

        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, name, GOSSIP_SENDER_CRAFTSMAN_RECIPES, it->spellId, name, price, false);
        ++matched;
    }

    const std::vector<Trainer::Spell>& trainerSpells = trainer->GetSpells();
    for (std::vector<Trainer::Spell>::const_iterator it = trainerSpells.begin(); it != trainerSpells.end() && matched < 10; ++it)
    {
        const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(it->SpellId);
        if (spellInfo == nullptr)
            continue;

        uint32 artifactId = GetSpellArtifactId(spellInfo);
        if (!artifactId)
            continue;

        std::string name = spellInfo->SpellName[locale];
        if (name.find(keyword) == std::string::npos)
            continue;

        uint32 price = GetSpellPriceByRank(it->ReqSkillRank);
        Reagents reagents;
        price += GetReagents(spellInfo, reagents);

        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, name, GOSSIP_SENDER_CRAFTSMAN_RECIPES, it->SpellId, name, price, false);
        ++matched;
    }

    return matched;
}

uint32 CraftsmanBaseAI::GetSpellPrice(uint32 spellId)
{
    if (trainerId == 0)
        return 0;

    const Trainer::Trainer* trainer = sObjectMgr->GetTrainer(trainerId);
    if (trainer == nullptr)
        return 0;

    const std::vector<Trainer::Spell>& trainerSpells = trainer->GetSpells();

    for (std::vector<Trainer::Spell>::const_iterator it = trainerSpells.begin(); it != trainerSpells.end(); ++it)
    {
        if (it->SpellId != spellId)
            continue;

        return GetSpellPriceByRank(it->ReqSkillRank);
    }

    return 0;
}

uint32 CraftsmanBaseAI::GetReagents(const SpellInfo* spellInfo, Reagents& reagents)
{
    uint money = 0;
    for (uint32 i = 0; i < MAX_SPELL_REAGENTS; ++i)
    {
        if (spellInfo->Reagent[i] <= 0)
            continue;

        money += AddReagents(reagents, spellInfo->Reagent[i], spellInfo->ReagentCount[i]);
    }
    return money;
}

uint32 CraftsmanBaseAI::AddReagents(Reagents& reagents, uint32 itemId, uint32 count)
{
    reagents[itemId] = count;
    return 0;
}
