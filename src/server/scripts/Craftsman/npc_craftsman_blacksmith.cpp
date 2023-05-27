#include "CraftsmanBaseAI.h"
#include "CraftsmanRecipeMgr.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

static const std::vector<CraftsmanCommonRecipe> commonRecipes =
{
    { 2660, 1 },
    { 3115, 1 },
    { 2663, 1 },
    { 12260, 1 },
    { 2662, 1 },
    { 2737, 15 },
    { 2738, 20 },
    { 3319, 20 },
    { 2739, 25 },
    { 3320, 25 },
    { 8880, 30 },
    { 9983, 30 },
    { 2661, 35 },
    { 3293, 35 },
    { 3323, 40 },
    { 3324, 45 },
    { 2665, 65 },
    { 3116, 65 },
    { 7408, 65 },
    { 2666, 70 },
    { 3294, 70 },
    { 3326, 75 },
    { 2664, 90 },
    { 3292, 95 },
    { 7817, 95 },
    { 7818, 100 },
    { 19666, 100 },
    { 34979, 100 },
    { 2668, 105 },
    { 2670, 105 },
    { 3491, 105 },
    { 2740, 110 },
    { 3328, 110 },
    { 6517, 110 },
    { 2741, 115 },
    { 2672, 120 },
    { 2742, 120 },
    { 2674, 125 },
    { 3117, 125 },
    { 3337, 125 },
    { 9985, 125 },
    { 3296, 130 },
    { 3331, 130 },
    { 9986, 130 },
    { 3333, 135 },
    { 9987, 135 },
    { 2675, 145 },
    { 8768, 150 },
    { 14379, 150 },
    { 19667, 150 },
    { 3506, 155 },
    { 3501, 165 },
    { 3502, 170 },
    { 3508, 180 },
    { 15972, 180 },
    { 7223, 185 },
    { 9916, 200 },
    { 9918, 200 },
    { 9920, 200 },
    { 9921, 200 },
    { 14380, 200 },
    { 19668, 200 },
    { 34981, 200 },
    { 9926, 205 },
    { 9928, 205 },
    { 9931, 210 },
    { 9993, 210 },
    { 9935, 215 },
    { 9954, 225 },
    { 9959, 230 },
    { 9961, 230 },
    { 10001, 230 },
    { 9968, 235 },
    { 10003, 235 },
    { 9954, 245 },
    { 9974, 245 },
    { 10007, 245 },
    { 10011, 250 },
    { 16639, 250 },
    { 16640, 250 },
    { 16641, 250 },
    { 16642, 250 },
    { 16643, 250 },
    { 16644, 255 },
    { 10015, 260 },
    { 16969, 275 },
    { 19669, 275 },
    { 20201, 275 },
    { 16652, 280 },
    { 16653, 280 },
    { 16971, 280 },
    { 16662, 300 },
    { 29545, 300 },
    { 29551, 300 },
    { 29654, 300 },
    { 32655, 300 },
    { 34607, 300 },
    { 34982, 300 },
    { 29547, 305 },
    { 29552, 310 },
    { 29557, 310 },
    { 29548, 315 },
    { 29549, 315 },
    { 29553, 315 },
    { 29558, 315 },
    { 29556, 320 },
    { 29565, 320 },
    { 29550, 325 },
    { 32284, 325 },
    { 34983, 350 },
    { 52568, 350 },
    { 52569, 350 },
    { 59405, 350 },
    { 52572, 360 },
    { 54550, 360 },
    { 55834, 360 },
    { 52567, 370 },
    { 52571, 370 },
    { 55835, 370 },
    { 52570, 375 },
    { 54917, 375 },
    { 54918, 380 },
    { 55200, 380 },
    { 55201, 380 },
    { 54941, 385 },
    { 54944, 385 },
    { 55202, 385 },
    { 55203, 385 },
    { 54557, 390 },
    { 54945, 390 },
    { 55013, 390 },
    { 55174, 390 },
    { 55204, 390 },
    { 54551, 395 },
    { 54554, 395 },
    { 54946, 395 },
    { 54947, 395 },
    { 55055, 395 },
    { 55177, 395 },
    { 59436, 395 },
    { 54552, 400 },
    { 54553, 400 },
    { 54948, 400 },
    { 54949, 400 },
    { 55056, 400 },
    { 55179, 400 },
    { 59438, 400 },
    { 54555, 405 },
    { 54556, 405 },
    { 55057, 405 },
    { 55181, 405 },
    { 55206, 405 },
    { 59440, 405 },
    { 55014, 410 },
    { 55017, 410 },
    { 55182, 410 },
    { 56280, 410 },
    { 59442, 410 },
    { 55015, 415 },
    { 55058, 415 },
    { 55656, 415 },
    { 59441, 415 },
    { 55298, 420 },
    { 55300, 420 },
    { 55301, 420 },
    { 55305, 420 },
    { 55306, 420 },
    { 55307, 420 },
    { 55308, 420 },
    { 55309, 420 },
    { 55732, 420 },
    { 55839, 420 },
    { 56357, 420 },
    { 56549, 420 },
    { 56550, 420 },
    { 56551, 420 },
    { 56552, 420 },
    { 56553, 420 },
    { 61009, 420 },
    { 61010, 420 },
    { 55302, 425 },
    { 55303, 425 },
    { 55304, 425 },
    { 55310, 425 },
    { 55311, 425 },
    { 55312, 425 },
    { 56554, 425 },
    { 56555, 425 },
    { 56556, 425 },
    { 61008, 425 },
    { 59406, 430 },
    { 55369, 440 },
    { 55370, 440 },
    { 55371, 440 },
    { 55372, 440 },
    { 55373, 440 },
    { 55374, 440 },
    { 55375, 440 },
    { 55376, 440 },
    { 55377, 440 },
    { 56234, 440 },
    { 56400, 440 },
    { 63182, 440 },
};

static const std::vector<CraftsmanCommonRecipe> recommandedRecipes =
{
    { 2660, 1 },
    { 3115, 1 },
    { 2665, 65 },
    { 3116, 65 },
    { 2674, 125 },
    { 3117, 125 },
    { 9918, 200 },
    { 9921, 200 },
    { 16641, 250 },
    { 16640, 250 },
    { 29654, 300 },
    { 34607, 300 },
};

static const std::map<uint32, Reagents> equivalents =
{
    {  3470, { {  2835,  2 } } },                   // Rough Grinding Stone
    {  3478, { {  2836,  2 } } },                   // Coarse Grinding Stone
    {  3486, { {  2838,  3 } } },                   // Heavy Grinding Stone
    {  7966, { {  7912,  4 } } },                   // Solid Grinding Stone
    { 12644, { { 12365,  4 } } },                   // Dense Grinding Stone
};

static const std::vector<uint32> materialSpellIds = {
    3470,   // Rough Grinding Stone
    3478,   // Coarse Grinding Stone
    3486,   // Heavy Grinding Stone
    7966,   // Solid Grinding Stone
    12644,  // Dense Grinding Stone
};

class npc_craftsman_blacksmith : public CreatureScript
{
public:
    npc_craftsman_blacksmith() : CreatureScript("npc_craftsman_blacksmith") { }

    struct npc_craftsman_blacksmithAI : public CraftsmanBaseAI
    {
        npc_craftsman_blacksmithAI(Creature* creature) : CraftsmanBaseAI(creature)
        {
            trainerId = 28699;
            skillId = 197;
            recipeSubclass = 2;
        }

        void PrepareMainMenuItems(Player* player) override
        {
            std::string tailingText = sCraftsmanTextMgr->GetText(player, CMTEXT_BLACKSMITH_SERVICE);
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

        const std::vector<CraftsmanCommonRecipe>& GetDefaultRecipe() const override
        {
            return recommandedRecipes;
        }

        const std::vector<CraftsmanCommonRecipe>& GetCommonRecipe() const override
        {
            return commonRecipes;
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_craftsman_blacksmithAI(creature);
    }

};

void AddSC_npc_craftsman_blacksmith()
{
    new npc_craftsman_blacksmith();
}
