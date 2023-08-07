#include "CraftsmanBaseAI.h"
#include "CraftsmanRecipeMgr.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

static const std::vector<CraftsmanCommonRecipe> commonRecipes =
{
    {  2881,   1 },
    {  2152,   1 },
    {  9058,   1 },
    {  9059,   1 },
    {  7126,   1 },
    {  2149,   1 },
    {  2153,  15 },
    {  3753,  25 },
    {  9060,  30 },
    {  9062,  30 },
    {  3816,  35 },
    {  2160,  40 },
    {  2161,  55 },
    {  3756,  55 },
    {  2162,  60 },
    {  9065,  70 },
    {  3759,  75 },
    {  3763,  80 },
    {  2159,  85 },
    {  3761,  85 },
    {  9068,  95 },
    {  2165, 100 },
    {  2167, 100 },
    {  3817, 100 },
    { 20648, 100 },
    {  2168, 110 },
    {  7135, 115 },
    {  2166, 120 },
    {  9074, 120 },
    {  3766, 125 },
    {  9145, 125 },
    {  3768, 130 },
    {  3770, 135 },
    {  3764, 145 },
    {  3760, 150 },
    {  3780, 150 },
    {  3818, 150 },
    {  9193, 150 },
    {  9194, 150 },
    { 20649, 150 },
    {  3774, 160 },
    {  7147, 160 },
    {  7151, 175 },
    {  9196, 175 },
    {  3776, 180 },
    {  9198, 180 },
    {  9201, 185 },
    {  6661, 190 },
    {  7156, 190 },
    {  9206, 195 },
    { 10482, 200 },
    { 10487, 200 },
    { 20650, 200 },
    { 10499, 205 },
    { 10507, 205 },
    { 10511, 210 },
    { 10518, 210 },
    { 10619, 225 },
    { 10621, 225 },
    { 14930, 225 },
    { 14932, 225 },
    { 10548, 230 },
    { 10552, 230 },
    { 10630, 230 },
    { 10556, 235 },
    { 10558, 235 },
    { 10632, 250 },
    { 10647, 250 },
    { 19047, 250 },
    { 19058, 250 },
    { 22331, 250 },
    { 10650, 255 },
    { 36074, 260 },
    { 36075, 260 },
    { 36076, 260 },
    { 19052, 265 },
    { 19055, 270 },
    { 19065, 275 },
    { 19071, 280 },
    { 19072, 280 },
    { 24655, 280 },
    { 19082, 290 },
    { 19083, 290 },
    { 19091, 300 },
    { 19092, 300 },
    { 19098, 300 },
    { 19102, 300 },
    { 19103, 300 },
    { 24654, 300 },
    { 32454, 300 },
    { 32456, 300 },
    { 32462, 300 },
    { 32466, 300 },
    { 32470, 300 },
    { 32478, 300 },
    { 45100, 300 },
    { 32463, 310 },
    { 32467, 310 },
    { 32479, 310 },
    { 32471, 315 },
    { 44343, 315 },
    { 44344, 315 },
    { 32464, 320 },
    { 32472, 320 },
    { 32480, 320 },
    { 32455, 325 },
    { 32468, 325 },
    { 32473, 330 },
    { 32481, 330 },
    { 36077, 330 },
    { 36078, 330 },
    { 36079, 330 },
    { 32465, 335 },
    { 32469, 335 },
    { 35540, 340 },
    { 44770, 350 },
    { 44970, 350 },
    { 50962, 350 },
    { 64661, 350 },
    { 50939, 370 },
    { 50941, 370 },
    { 50944, 370 },
    { 50948, 370 },
    { 50951, 370 },
    { 50955, 370 },
    { 50957, 370 },
    { 50959, 370 },
    { 35575, 375 },
    { 35576, 375 },
    { 35577, 375 },
    { 35580, 375 },
    { 35582, 375 },
    { 35584, 375 },
    { 35585, 375 },
    { 35587, 375 },
    { 35588, 375 },
    { 35589, 375 },
    { 35590, 375 },
    { 35591, 375 },
    { 50938, 375 },
    { 50942, 375 },
    { 50945, 375 },
    { 50947, 375 },
    { 50950, 375 },
    { 50952, 375 },
    { 50956, 375 },
    { 50961, 375 },
    { 50940, 380 },
    { 50943, 380 },
    { 50946, 380 },
    { 50949, 380 },
    { 50953, 380 },
    { 50954, 380 },
    { 50958, 380 },
    { 50960, 380 },
    { 60631, 380 },
    { 51571, 385 },
    { 51572, 385 },
    { 60599, 385 },
    { 60600, 385 },
    { 60607, 385 },
    { 60608, 385 },
    { 60622, 385 },
    { 60624, 385 },
    { 50936, 390 },
    { 50963, 395 },
    { 51569, 395 },
    { 51570, 395 },
    { 55199, 395 },
    { 60601, 395 },
    { 60604, 395 },
    { 60611, 395 },
    { 60613, 395 },
    { 60627, 395 },
    { 60629, 395 },
    { 50966, 400 },
    { 51568, 400 },
    { 57683, 400 },
    { 57690, 400 },
    { 57691, 400 },
    { 60584, 400 },
    { 60605, 400 },
    { 60620, 400 },
    { 60630, 400 },
    { 50964, 405 },
    { 60583, 405 },
    { 60643, 415 },
    { 60651, 420 },
    { 60652, 420 },
    { 60658, 420 },
    { 60665, 420 },
    { 60666, 420 },
    { 60671, 420 },
    { 50965, 425 },
    { 50967, 425 },
    { 60649, 425 },
    { 60655, 425 },
    { 60660, 425 },
    { 60669, 425 },
    { 62448, 425 },
    { 60637, 440 },
    { 60640, 440 },
    { 69386, 450 },
    { 69388, 450 },
};

static const std::vector<CraftsmanCommonRecipe> recommandedRecipes =
{
    {  2152,   1 },
    {  2165, 100 },
    {  3780, 150 },
    { 10487, 200 },
    { 19058, 250 },
    { 50962, 350 },
    { 50963, 395 },
    { 50966, 400 },
    { 50964, 405 },
    { 50965, 425 },
    { 62448, 425 },
    { 50967, 425 },
};

static const std::map<uint32, Reagents> equivalents =
{
    {  4231, { {   783,  1 }, {  4289,  1 } } },    // Cured Light Hide
    {  4233, { {  4232,  1 }, {  4289,  1 } } },    // Cured Medium Hide
    {  4236, { {  4235,  1 }, {  4289,  3 } } },    // Cured Heavy Hide
    {  8172, { {  8169,  1 }, {  8150,  1 } } },    // Cured Thick Hide
    { 15407, { {  8171,  1 }, {  8150,  1 } } },    // Cured Rugged Hide
    { 23793, { { 21887,  5 } } },                   // Heavy Knothide Leather
    { 38425, { { 33568,  6 } } },                   // Heavy Borean Leather
};

static const std::vector<uint32> materialSpellIds =
{
    2881,       // Light Leather
    3816,       // Cured Light Hide
    20648,      // Medium Leather
    3817,       // Cured Medium Hide
    20649,      // Heavy Leather
    3818,       // Cured Heavy Hide
    20650,      // Thick Leather
    10482,      // Cured Thick Hide
    22331,      // Rugged Leather
    19047,      // Cured Rugged Hide
    32454,      // Knothide Leather
    32455,      // Heavy Knothide Leather
    64661,      // Borean Leather
    50936,      // Heavy Borean Leather
};

static const std::vector<uint32> consumableSpellIds =
{
    2152,
    2165,
    3780,
    10487,
    19058,
    50962,
    50963,
    50966,
    50964,
    50965,
    62448,
    50967,
    35554,
    35557,
    35555,
    22727,
    35549,
    35520,
    35524,
    35522,
    35521,
    35523,
    32458,
    32457,
};

class npc_craftsman_tanner : public CreatureScript
{
public:
    npc_craftsman_tanner() : CreatureScript("npc_craftsman_tanner") { }

    struct npc_craftsman_tannerAI : public CraftsmanBaseAI
    {
        npc_craftsman_tannerAI(Creature* creature) : CraftsmanBaseAI(creature)
        {
            trainerId = 28699;
            skillId = 165;
            recipeSubclass = 1;
        }

        void PrepareMainMenuItems(Player* player) override
        {
            std::string tailingText = sCraftsmanTextMgr->GetText(player, CMTEXT_LEATHERWORKING_SERVICE);
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

            if (std::find(consumableSpellIds.begin(), consumableSpellIds.end(), spellId) != consumableSpellIds.end())
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
        return new npc_craftsman_tannerAI(creature);
    }

};

void AddSC_npc_craftsman_tanner()
{
    new npc_craftsman_tanner();
}
