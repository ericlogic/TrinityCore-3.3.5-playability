#include "CraftsmanBaseAI.h"
#include "CraftsmanRecipeMgr.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "SpellInfo.h"

static const std::vector<CraftsmanCommonRecipe> commonRecipes =
{
    { 2657, 1 },
    { 2659, 65 },
    { 3304, 65 },
    { 2658, 75 },
    { 3307, 125 },
    { 3308, 155 },
    { 3569, 165 },
    { 10097, 175 },
    { 10098, 230 },
    { 16153, 250 },
    { 70524, 250 },
    { 29356, 300 },
    { 35750, 300 },
    { 35751, 300 },
    { 29358, 325 },
    { 29359, 350 },
    { 29360, 350 },
    { 29361, 350 },
    { 49252, 350 },
    { 29686, 375 },
    { 46353, 375 },
    { 49258, 400 },
    { 55208, 450 },
    { 55211, 450 },
};

static const std::map<uint32, Reagents> equivalents =
{
    {  2840, { {  2770,  1 } } },    // Copper Bar
    {  3576, { {  2771,  1 } } },    // Tin Bar
    {  3575, { {  2772,  1 } } },    // Iron Bar
    { 12359, { { 10620,  1 } } },    // Thorium Bar
    { 23445, { { 23424,  2 } } },    // Fel Iron Bar
    { 23446, { { 23425,  2 } } },    // Eternium Bar
    { 23447, { { 23427,  2 } } },    // Adamantite Bar
    { 23449, { { 23426,  2 } } },    // Khorum Bar
    { 23573, { { 23425, 20 } } },    // Hardened Adamantite Bar
    { 41163, { { 36910,  2 } } },    // Titanium Bar
};

static std::map<uint32, SpellInfo> overrideSpellInfos;

class npc_craftsman_miner : public CreatureScript
{
public:
    npc_craftsman_miner() : CreatureScript("npc_craftsman_miner") { }

    struct npc_craftsman_minerAI : public CraftsmanBaseAI
    {
        npc_craftsman_minerAI(Creature* creature) : CraftsmanBaseAI(creature)
        {
            trainerId = 28698;
            skillId = 186;
            recipeSubclass = 0;
        }

        void PrepareMainMenuItems(Player* player) override
        {
            std::string tailingText = sCraftsmanTextMgr->GetText(player, CMTEXT_SMELTING_SERVICE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, tailingText, GOSSIP_SENDER_CRAFTSMAN_MAIN, GOSSIP_ACTION_OEM_SERVICE);
        }

        const SpellInfo* GetSpellInfoOverride(const SpellInfo* spellInfo) override {
            if (!spellInfo->RequiresSpellFocus)
                return spellInfo;

            std::map<uint32, SpellInfo>::iterator it = overrideSpellInfos.find(spellInfo->Id);
            if (it != overrideSpellInfos.end())
                return &(it->second);

            overrideSpellInfos.insert({spellInfo->Id, *spellInfo});
            SpellInfo* overrideSpellInfo = &overrideSpellInfos.at(spellInfo->Id);
            overrideSpellInfo->RequiresSpellFocus = 0;
            return overrideSpellInfo;
        }

        uint32 AddReagents(Reagents& reagents, uint32 itemId, uint32 count) override
        {
            uint32 money = 0;

            std::map<uint32, Reagents>::const_iterator eqitor = equivalents.find(itemId);

            if (eqitor != equivalents.end())
            {
                for (Reagents::const_iterator it = eqitor->second.begin(); it  != eqitor->second.end(); ++it)
                {
                    if (it->first != 0)
                    {
                        reagents[it->first] += it->second * count;
                    }
                    else
                    {
                        money += it->second * count;
                    }
                }
            }
            else
            {
                reagents[itemId] += count;
            }

            return money;
        }

        uint32 GetSpellPrice(Player *player, uint32 spellId) override
        {
            return CraftsmanBaseAI::GetSpellPrice(player, spellId) / 100;
        }

        uint32 GetSpellCount(uint32 spellId) override
        {
            return 10;
        }

        const std::vector<CraftsmanCommonRecipe>& GetDefaultRecipe() const override
        {
            return commonRecipes;
        }

        const std::vector<CraftsmanCommonRecipe>& GetCommonRecipe() const override
        {
            return commonRecipes;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_craftsman_minerAI(creature);
    }

};

void AddSC_npc_craftsman_miner()
{
    new npc_craftsman_miner();
}
