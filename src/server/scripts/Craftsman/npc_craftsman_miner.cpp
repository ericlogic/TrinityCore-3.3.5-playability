#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

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
    { 49258, 400 },
    { 55208, 450 },
    { 55211, 450 }
};

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

        uint32 GetSpellPrice(Player *player, uint32 spellId) override
        {
            return CraftsmanBaseAI::GetSpellPrice(player, spellId) / 100;
        }

        uint32 GetSpellCount(uint32 spellId) override
        {
            return 10;
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
