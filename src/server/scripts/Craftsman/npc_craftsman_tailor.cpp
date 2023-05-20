#include "CraftsmanBaseAI.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

static const std::vector<CraftsmanCommonRecipe> commonRecipes =
{
    { 2963, 1 },
    { 2387, 1 },
    { 12044, 1 },
    { 2393, 1 },
    { 3915, 1 },
    { 2385, 10 },
    { 8776, 15 },
    { 12045, 20 },
    { 3914, 30 },
    { 7623, 30 },
    { 7624, 30 },
    { 3840, 35 },
    { 2392, 40 },
    { 2394, 40 },
    { 8465, 40 },
    { 3755, 45 },
    { 2397, 60 },
    { 3841, 60 },
    { 2386, 65 },
    { 2395, 70 },
    { 2396, 70 },
    { 3842, 70 },
    { 2402, 75 },
    { 2964, 75 },
    { 12046, 75 },
    { 3757, 80 },
    { 3845, 80 },
    { 2399, 85 },
    { 3843, 85 },
    { 6521, 90 },
    { 2401, 95 },
    { 2406, 100 },
    { 3848, 110 },
    { 3850, 110 },
    { 3866, 110 },
    { 8467, 110 },
    { 3839, 125 },
    { 3855, 125 },
    { 63742, 125 },
    { 3852, 130 },
    { 6690, 135 },
    { 8758, 140 },
    { 8760, 145 },
    { 3813, 150 },
    { 3859, 150 },
    { 8483, 160 },
    { 8762, 160 },
    { 3871, 170 },
    { 8764, 170 },
    { 3865, 175 },
    { 8489, 175 },
    { 8766, 175 },
    { 8772, 175 },
    { 8774, 180 },
    { 3861, 185 },
    { 8791, 185 },
    { 8770, 190 },
    { 8799, 195 },
    { 12048, 205 },
    { 12049, 205 },
    { 8804, 210 },
    { 12050, 210 },
    { 12052, 210 },
    { 12053, 215 },
    { 12055, 215 },
    { 12061, 215 },
    { 12065, 225 },
    { 12067, 225 },
    { 12069, 225 },
    { 12070, 225 },
    { 12071, 225 },
    { 12072, 230 },
    { 12073, 230 },
    { 12074, 230 },
    { 12076, 235 },
    { 12077, 235 },
    { 12079, 235 },
    { 12082, 240 },
    { 12088, 245 },
    { 12092, 250 },
    { 18401, 250 },
    { 18402, 255 },
    { 18403, 255 },
    { 18406, 260 },
    { 18407, 260 },
    { 18409, 265 },
    { 18410, 265 },
    { 18411, 265 },
    { 18413, 270 },
    { 18414, 270 },
    { 18415, 270 },
    { 18416, 275 },
    { 18417, 275 },
    { 18420, 275 },
    { 18421, 275 },
    { 18423, 280 },
    { 18424, 280 },
    { 18437, 285 },
    { 18438, 285 },
    { 18441, 290 },
    { 18442, 290 },
    { 18444, 295 },
    { 18446, 300 },
    { 18449, 300 },
    { 18450, 300 },
    { 18451, 300 },
    { 18453, 300 },
    { 26745, 300 },
    { 31460, 300 },
    { 60969, 300 },
    { 26764, 310 },
    { 26765, 310 },
    { 26746, 315 },
    { 26770, 320 },
    { 26771, 325 },
    { 26772, 335 },
    { 55899, 350 },
    { 55902, 350 },
    { 56031, 350 },
    { 55898, 360 },
    { 55903, 360 },
    { 55904, 360 },
    { 55908, 370 },
    { 55906, 375 },
    { 55907, 380 },
    { 56030, 380 },
    { 55910, 385 },
    { 55913, 385 },
    { 55911, 390 },
    { 56014, 390 },
    { 55901, 395 },
    { 55914, 395 },
    { 55919, 395 },
    { 56015, 395 },
    { 55900, 400 },
    { 55920, 400 },
    { 55995, 400 },
    { 56000, 400 },
    { 56008, 400 },
    { 56010, 400 },
    { 64729, 400 },
    { 55921, 405 },
    { 55922, 405 },
    { 56034, 405 },
    { 56039, 405 },
    { 64730, 405 },
    { 55923, 410 },
    { 55924, 410 },
    { 56007, 410 },
    { 55925, 415 },
    { 55943, 415 },
    { 56001, 415 },
    { 56002, 415 },
    { 56003, 415 },
    { 59582, 415 },
    { 59583, 415 },
    { 55642, 420 },
    { 55769, 420 },
    { 55777, 420 },
    { 55941, 420 },
    { 56019, 420 },
    { 56020, 420 },
    { 56022, 420 },
    { 56023, 420 },
    { 59584, 420 },
    { 59585, 420 },
    { 59586, 420 },
    { 59587, 420 },
    { 59588, 420 },
    { 59589, 420 },
    { 60990, 420 },
    { 60994, 420 },
    { 56018, 425 },
    { 56021, 425 },
    { 60971, 425 },
    { 60993, 425 },
    { 56025, 435 },
    { 56027, 435 },
    { 56029, 435 },
    { 56024, 440 },
    { 56026, 440 },
    { 56028, 440 }
};

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

        uint32 GetSpellPrice(Player* player, uint32 spellId) override
        {
            uint32 price = CraftsmanBaseAI::GetSpellPrice(player, spellId);

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

        const std::vector<CraftsmanCommonRecipe>& GetCommonRecipe() const override
        {
            return commonRecipes;
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
