#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

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

        uint32 GetSpellPrice(uint32 spellId) override
        {
            return CraftsmanBaseAI::GetSpellPrice(spellId) / 100;
        }

        uint32 GetSpellCount(uint32 spellId) override
        {
            return 10;
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
