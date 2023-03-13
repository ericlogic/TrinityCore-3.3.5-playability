#include "Bag.h"
#include "Creature.h"
#include "CommonNpcAI.h"
#include "Player.h"
#include "RewardPointMgr.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "StringFormat.h"

const std::vector<std::vector<uint32>> CHARACTER_GIFTS_LV60 {
    {}, //  0 Unknown
    { 16959, 16960, 16961, 16962, 16963, 16964, 16965, 16966 }, //  1 Warrior
    { 16951, 16952, 16953, 16954, 16955, 16956, 16957, 16958 }, //  2 Paladin
    { 16935, 16936, 16937, 16938, 16939, 16940, 16941, 16942 }, //  3 Hunter
    { 16832, 16905, 16906, 16907, 16908, 16909, 16910, 16911 }, //  4 Rogue
    { 16919, 16920, 16921, 16922, 16923, 16924, 16925, 16926 }, //  5 Priest
    {}, //  6 Death Knight
    { 16943, 16944, 16945, 16946, 16947, 16948, 16949, 16950 }, //  7 Shaman
    { 16818, 16912, 16913, 16914, 16915, 16916, 16917, 16918 }, //  8 Mage
    { 16927, 16928, 16929, 16930, 16931, 16932, 16933, 16934 }, //  9 Warlock
    {}, // 10 Unknown
    { 16897, 16898, 16899, 16900, 16901, 16902, 16903, 16904 }, // 11 Druid
};

const std::vector<std::vector<uint32>> CHARACTER_GIFTS_LV70 {
    {}, //  0 Unknown
    { 30969, 30972, 30975, 30977, 30979, 34441, 34546, 34569 }, //  1 Warrior
    { 30982, 30989, 30990, 30993, 30997, 34431, 34485, 34561 }, //  2 Paladin
    { 31001, 31003, 31004, 31005, 31006, 34443, 34549, 34570 }, //  3 Hunter
    { 31026, 31027, 31028, 31029, 31030, 34448, 34558, 34575 }, //  4 Rogue
    { 31061, 31064, 31065, 31067, 31070, 34434, 34528, 34563 }, //  5 Priest
    {}, //  6 Death Knight
    { 31011, 31015, 31018, 31021, 31024, 34439, 34545, 34567 }, //  7 Shaman
    { 31055, 31056, 31057, 31058, 31059, 34447, 34557, 34574 }, //  8 Mage
    { 31050, 31051, 31052, 31053, 31054, 34436, 34541, 34564 }, //  9 Warlock
    {}, // 10 Unknown
    { 31034, 31039, 31042, 31044, 31048, 34444, 34556, 34573 }, // 11 Druid
};

uint32 GetFreeContainerSpace(Player* player)
{
    uint32 freeSpace = 0;

    // Check backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
    {
        Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!item)
            freeSpace += 1;
    }

    // Check bags
    for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
    {
        if (Bag* bag = player->GetBagByPos(i))
        {
            if (ItemTemplate const* bagTemplate = bag->GetTemplate())
            {
                if (bagTemplate->Class == ITEM_CLASS_CONTAINER && bagTemplate->SubClass == ITEM_SUBCLASS_CONTAINER)
                    freeSpace += bag->GetFreeSlots();
            }
        }
    }

    return freeSpace;
}

class character_booster : public CreatureScript
{
public:
    character_booster() : CreatureScript("rpsc_character_booster") { }

    struct character_booster_AI : public RewardPointCommonNpcAI
    {
        character_booster_AI(Creature* creature) : RewardPointCommonNpcAI(creature) {}

        void SendGossipHello(Player *player) override
        {
            player->PlayerTalkClass->ClearMenus();

            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(
                -1, GOSSIP_ICON_TALK,
                Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_BOOST_TO_LV60), sRewardPointMgr->GetCharacterBoost60Points()),
                GOSSIP_SENDER_HELLO, GOSSIP_ACTION_CHARACTER_BOOST_60,
                Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_BOOST_TO_LV60_CONFIRM), sRewardPointMgr->GetCharacterBoost60Points()),
                0, false
                );
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(
                -1, GOSSIP_ICON_TALK,
                Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_BOOST_TO_LV70), sRewardPointMgr->GetCharacterBoost70Points()),
                GOSSIP_SENDER_HELLO, GOSSIP_ACTION_CHARACTER_BOOST_70,
                Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_BOOST_TO_LV70_CONFIRM), sRewardPointMgr->GetCharacterBoost70Points()),
                0, false
                );

            AddCommonGossipItems(player, GOSSIP_SENDER_HELLO);
            AddCloseGossipItem(player, RewardPointMgr::LocalizedNpcText(player, RPTXT_NEVERMIND), GOSSIP_SENDER_HELLO);

            player->PlayerTalkClass->SendGossipMenu(RPTXT_CHARACTER_BOOSTER_HELLO, me->GetGUID());
        }

        bool OnGossipHello(Player* player) override
        {
            if (me->isMoving())
                me->BotStopMovement();

            SendGossipHello(player);
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            switch (sender)
            {
                case GOSSIP_SENDER_HELLO:
                    return HandleHelloGossip(player, action);
                case GOSSIP_SENDER_NOT_ENOUGH_POINTS:
                    return HandleNotEnouthPointsGossip(player, action);
                case GOSSIP_SENDER_POWERFUL_ENOUGH:
                    return HandlePowerfulEnoughGossip(player, action);
                default:
                    return HandleCommonGoosip(player, action);
            }

            return true;
        }

        bool OnGossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, char const* code) override
        {
            uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
            uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);

            return HandleCommonGoosipCode(player, action, code);
        }

        bool HandleHelloGossip(Player* player, uint32 action)
        {
            switch (action)
            {
                case GOSSIP_ACTION_CHARACTER_BOOST_60:
                    return HandleCharacterBoost60(player);
                case GOSSIP_ACTION_CHARACTER_BOOST_70:
                    return HandleCharacterBoost70(player);
                default:
                    return HandleCommonGoosip(player, action);
            }
        }

        bool HandleNotEnouthPointsGossip(Player* player, uint32 action)
        {
            SendGossipHello(player);
            return true;
        }

        bool HandlePowerfulEnoughGossip(Player* player, uint32 action)
        {
            SendGossipHello(player);
            return true;
        }

        bool HandleCharacterBoost60(Player* player)
        {
            int32 points = sRewardPointMgr->GetCharacterBoost60Points();
            if (points > 0)
            {
                int32 available = sRewardPointMgr->GetAvailable(player);
                if (available < points)
                {
                    SendNotEnoughPoints(player);
                    return true;
                }
            }

            if (player->GetLevel() > 50)
            {
                SendPowerfulEnough(player);
                return true;
            }

            const std::vector<uint32>& gift = CHARACTER_GIFTS_LV60[player->GetClass()];
            uint32 freeSpace = GetFreeContainerSpace(player);
            if (freeSpace < gift.size())
            {
                me->Whisper(Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_RESERVE_SPACE), gift.size()),
                    LANG_UNIVERSAL, player);
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            player->GiveLevel(60);
            player->InitTalentForLevel();

            player->UpdateWeaponsSkillsToMaxSkillsForLevel();

            player->ModifyMoney(5000000);

            for (std::vector<uint32>::const_iterator it = gift.begin(); it != gift.end(); ++it)
            {
                ItemPosCountVec dest;
                player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, *it, 1, NULL);
                player->StoreNewItem(dest, *it, true, GenerateItemRandomPropertyId(*it));
            }

            if (points > 0)
            {
                sRewardPointMgr->Update(player, 60, RPC_CHARACTER_BOOST_60, -points);
            }

            return true;
        }

        bool HandleCharacterBoost70(Player* player)
        {
            int32 points = sRewardPointMgr->GetCharacterBoost70Points();
            if (points > 0)
            {
                int32 available = sRewardPointMgr->GetAvailable(player);
                if (available < points)
                {
                    SendNotEnoughPoints(player);
                    return true;
                }
            }

            if (player->GetLevel() >= 60)
            {
                SendPowerfulEnough(player);
                return true;
            }

            const std::vector<uint32>& gift = CHARACTER_GIFTS_LV70[player->GetClass()];
            uint32 freeSpace = GetFreeContainerSpace(player);
            if (freeSpace < gift.size())
            {
                me->Whisper(Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_RESERVE_SPACE), gift.size()),
                    LANG_UNIVERSAL, player);
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }

            player->GiveLevel(70);
            player->InitTalentForLevel();

            player->UpdateWeaponsSkillsToMaxSkillsForLevel();

            player->ModifyMoney(5000000);

            for (std::vector<uint32>::const_iterator it = gift.begin(); it != gift.end(); ++it)
            {
                ItemPosCountVec dest;
                player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, *it, 1, NULL);
                player->StoreNewItem(dest, *it, true, GenerateItemRandomPropertyId(*it));
            }

            if (points > 0)
            {
                sRewardPointMgr->Update(player, 70, RPC_CHARACTER_BOOST_70, -points);
            }

            return true;
        }

        void SendNotEnoughPoints(Player *player)
        {
            player->PlayerTalkClass->ClearMenus();
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, RewardPointMgr::LocalizedNpcText(player, RPTXT_WELL), GOSSIP_SENDER_NOT_ENOUGH_POINTS, GOSSIP_ACTION_BACK);
            player->PlayerTalkClass->SendGossipMenu(RPTXT_NOT_ENOUGH_POINTS, me->GetGUID());
        }

        void SendPowerfulEnough(Player *player)
        {
            player->PlayerTalkClass->ClearMenus();
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, RewardPointMgr::LocalizedNpcText(player, RPTXT_WELL), GOSSIP_SENDER_POWERFUL_ENOUGH, GOSSIP_ACTION_BACK);
            player->PlayerTalkClass->SendGossipMenu(RPTXT_POWERFUL_ENOUGH, me->GetGUID());
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new character_booster_AI(creature);
    }
};

void AddSC_rpsc_character_booster()
{
    new character_booster();
}
