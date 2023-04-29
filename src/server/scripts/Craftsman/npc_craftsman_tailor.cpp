#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

class npc_craftsman_tailor : public CreatureScript
{
public:
    npc_craftsman_tailor() : CreatureScript("npc_craftsman_tailor") { }

    struct npc_craftsman_tailorAI : public CraftsmanBaseAI
    {
        npc_craftsman_tailorAI(Creature* creature) : CraftsmanBaseAI(creature)
        {
            trainerId = 28699;
            skillId = 197;
            recipeSubclass = 2;
        }

        void PrepareMainMenuItems(Player* player) override
        {
            std::string tailingText = sCraftsmanTextMgr->GetText(player, CMTEXT_TAILORING_SERVICE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, tailingText, GOSSIP_SENDER_CRAFTSMAN_MAIN, GOSSIP_ACTION_OEM_SERVICE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_craftsman_tailorAI(creature);
    }

};

void AddSC_npc_craftsman_tailor()
{
    new npc_craftsman_tailor();
}
