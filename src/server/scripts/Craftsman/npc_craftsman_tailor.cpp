#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

static const std::map<uint32, Reagents> equivalents =
{
    {  2996, { {  2589,  2 } } },                   // Bolt of Linen Cloth
    {  2997, { {  2592,  3 } } },                   // Bolt of Woolen Cloth
    {  4305, { {  4306,  4 } } },                   // Bolt of Silk Cloth
    {  4339, { {  4338,  4 } } },                   // Bolt of Mageweave
    { 14048, { { 14047,  4 } } },                   // Bolt of Runecloth
    { 14342, { { 14256,  2 } } },                   // Mooncloth
    { 21840, { { 21877,  5 } } },                   // Bolt of Nethercloth
    { 21842, { { 21877, 15 }, { 22445,  2 } } },    // Bolt of Imbued Nethercloth
    { 21844, { { 21877,  5 }, { 21882,  8 } } },    // Bolt of Soulcloth
    { 21845, { { 21877, 15 }, { 22445,  2 }, { 21886,  1 }, { 21885,  1 } } },  // Primal Mooncloth
    { 41510, { { 33470,  5 } } },                   // Bolt of Frostcloth
    { 41510, { { 33470, 10 }, { 34054,  2 } } },    // Bolt of Imbued Frostcloth
};

static const std::vector<uint32> materialSpellIds = {
    2963,   // Bolt of Linen Cloth
    2964,   // Bolt of Woolen Cloth
    3839,   // Bolt of Silk Cloth
    3865,   // Bolt of Mageweave
    18401,  // Bolt of Runecloth
    18560,  // Mooncloth
    26745,  // Bolt of Netherweave
    26751,  // Primal Mooncloth
    26747,  // Bolt of Imbued Netherweave
    26750,  // Bolt of Soulcloth
    55899,  // Bolt of Frostweave
    55900,  // Bolt of Imbued Frostweave
};

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

        uint32 GetSpellPrice(uint32 spellId) override
        {
            uint32 price = CraftsmanBaseAI::GetSpellPrice(spellId);

            if (std::find(materialSpellIds.begin(), materialSpellIds.end(), spellId) != materialSpellIds.end())
                price /= 100;

            return price;
        }

        uint32 GetSpellCount(uint32 spellId) override
        {
            if (std::find(materialSpellIds.begin(), materialSpellIds.end(), spellId) != materialSpellIds.end())
                return 10;

            return 1;
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
