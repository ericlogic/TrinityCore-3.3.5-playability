#include "CraftsmanBaseAI.h"
#include "CraftsmanRecipeMgr.h"
#include "CraftsmanTextMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"

static const std::vector<CraftsmanCommonRecipe> commonRecipes =
{
    {  3170,  15 },
    {  2331,  25 },
    {  2332,  40 },
    {  2334,  50 },
    { 53042,  50 },
    {  2337,  55 },
    {  7836,  80 },
    {  3171,  90 },
    {  7179,  90 },
    {  7841, 100 },
    {  3447, 110 },
    {  3173, 120 },
    {  3176, 125 },
    {  3177, 130 },
    {  7837, 130 },
    { 63732, 135 },
    {  7845, 140 },
    {  7181, 155 },
    {  3452, 160 },
    {  3448, 165 },
    {  3450, 175 },
    { 11449, 185 },
    { 11450, 195 },
    { 12609, 200 },
    { 11448, 205 },
    { 11451, 205 },
    { 11457, 215 },
    { 22808, 215 },
    { 15833, 230 },
    { 11460, 230 },
    { 11465, 235 },
    { 11461, 235 },
    { 11467, 240 },
    { 11478, 250 },
    { 17551, 250 },
    { 17552, 255 },
    { 17553, 260 },
    { 17555, 270 },
    { 17556, 275 },
    { 17557, 275 },
    { 17572, 285 },
    { 17573, 285 },
    { 33740, 300 },
    { 33738, 300 },
    { 33732, 300 },
    { 28544, 305 },
    { 28545, 310 },
    { 33733, 310 },
    { 39636, 310 },
    { 33741, 315 },
    { 39638, 320 },
    { 38070, 325 },
    { 45061, 325 },
    { 28551, 325 },
    { 53838, 350 },
    { 28580, 350 },
    { 28581, 350 },
    { 28582, 350 },
    { 28583, 350 },
    { 28584, 350 },
    { 28585, 350 },
    { 28587, 350 },
    { 28588, 350 },
    { 28589, 350 },
    { 28590, 350 },
    { 28591, 350 },
    { 53841, 355 },
    { 53839, 360 },
    { 41458, 360 },
    { 41500, 360 },
    { 41501, 360 },
    { 41502, 360 },
    { 41503, 360 },
    { 53842, 365 },
    { 53848, 375 },
    { 62409, 375 },
    { 53899, 375 },
    { 53812, 375 },
    { 53900, 380 },
    { 53847, 385 },
    { 62213, 385 },
    { 54218, 385 },
    { 53898, 390 },
    { 53840, 395 },
    { 60367, 395 },
    { 53905, 395 },
    { 60350, 395 },
    { 60403, 400 },
    { 60396, 400 },
    { 60405, 400 },
    { 60893, 400 },
    { 53771, 400 },
    { 53773, 400 },
    { 53774, 400 },
    { 53775, 400 },
    { 53776, 400 },
    { 53777, 400 },
    { 53779, 400 },
    { 53780, 400 },
    { 53781, 400 },
    { 53782, 400 },
    { 53783, 400 },
    { 53784, 400 },
    { 53836, 405 },
    { 58868, 410 },
    { 58871, 410 },
    { 53837, 410 },
    { 67025, 425 },
    { 57427, 425 },
    { 57425, 430 },
    { 54213, 435 },
    { 53903, 435 },
    { 53902, 435 },
    { 53901, 435 },
    { 66658, 450 },
    { 66660, 450 },
    { 66662, 450 },
    { 66663, 450 },
    { 66664, 450 },
};

static const std::vector<CraftsmanCommonRecipe> recommandedRecipes =
{
    {  7179,  90 },     // Elixir of Water Breathing
    {  7841, 100 },     // Swim Speed Potion
    { 22808, 215 },     // Elixir of Greater Water Breathing
    { 41458, 360 },     // Cauldron of Major Arcane Protection
    { 41500, 360 },     // Cauldron of Major Fire Protection
    { 41501, 360 },     // Cauldron of Major Frost Protection
    { 41502, 360 },     // Cauldron of Major Nature Protection
    { 41503, 360 },     // Cauldron of Major Shadow Protection
};

static const std::map<uint32, Reagents> equivalents =
{
    {  6370, { {  6358,  2 } } },                                   // Blackmouth Oil
    {  6371, { {  6359,  2 } } },                                   // Fire Oil
    { 13423, { { 13422,  1 } } },                                   // Stonescale Oil
};

static const std::vector<uint32> transmuteSpellIds =
{
    54020,      // Transmute: Eternal Might

    28580,      // Transmute: Primal Shadow to Water
    28581,      // Transmute: Primal Water to Shadow
    28582,      // Transmute: Primal Mana to Fire
    28583,      // Transmute: Primal Fire to Mana
    28584,      // Transmute: Primal Life to Earth
    28585,      // Transmute: Primal Earth to Life

    17187,      // Transmute: Arcanite

    17559,      // Transmute: Air to Fire
    17560,      // Transmute: Fire to Earth
    17561,      // Transmute: Earth to Water
    17562,      // Transmute: Water to Air
    17563,      // Transmute: Undeath to Water
    17564,      // Transmute: Water to Undeath
    17565,      // Transmute: Life to Earth
    17566,      // Transmute: Earth to Life
    32765,      // Transmute: Earthstorm Diamond
    32766,      // Transmute: Skyfire Diamond

    28566,      // Transmute: Primal Air to Fire
    28567,      // Transmute: Primal Earth to Water
    28568,      // Transmute: Primal Fire to Earth
    28569,      // Transmute: Primal Water to Air

    29688,      // Transmute: Primal Might
    60350,      // Transmute: Titanium

    53771,      // Transmute: Eternal Life to Shadow
    53773,      // Transmute: Eternal Life to Fire
    53774,      // Transmute: Eternal Fire to Water
    53775,      // Transmute: Eternal Fire to Life
    53776,      // Transmute: Eternal Air to Water
    53777,      // Transmute: Eternal Air to Earth
    53779,      // Transmute: Eternal Shadow to Earth
    53780,      // Transmute: Eternal Shadow to Life
    53781,      // Transmute: Eternal Earth to Air
    53782,      // Transmute: Eternal Earth to Shadow
    53783,      // Transmute: Eternal Water to Air
    53784,      // Transmute: Eternal Water to Fire

    57427,      // Transmute: Earthsiege Diamond
    57425,      // Transmute: Skyflare Diamond

    66658,      // Transmute: Ametrine
    66659,      // Transmute: Cardinal Ruby
    66660,      // Transmute: King's Amber
    66662,      // Transmute: Dreadstone
    66663,      // Transmute: Majestic Zircon
    66664,      // Transmute: Eye of Zul

    24266,      // Gurubashi Mojo Madness

    17635,      // Flask of the Titans
    17636,      // Flask of Distilled Wisdom
    17637,      // Flask of Supreme Power
    17638,      // Flask of Chromatic Resistance

    28587,      // Flask of Fortification
    28588,      // Flask of Mighty Restoration
    28589,      // Flask of Relentless Assault
    28590,      // Flask of Blinding Light
    28591,      // Flask of Pure Death

    53899,      // Lesser Flask of Toughness
    42736,      // Flask of Chromatic Wonder
    62213,      // Lesser Flask of Resistance
    67025,      // Flask of the North
    53901,      // Flask of the Frost Wyrm
    54213,      // Flask of Pure Mojo
    53902,      // Flask of Stoneblood
    53903,      // Flask of Endless Rage

    41458,      // Cauldron of Major Arcane Protection
    41500,      // Cauldron of Major Fire Protection
    41501,      // Cauldron of Major Frost Protection
    41502,      // Cauldron of Major Nature Protection
    41503,      // Cauldron of Major Shadow Protection

    17632,      // Alchemist's Stone
    47046,      // Guardian's Alchemist Stone
    47048,      // Sorcerer's Alchemist Stone
    47049,      // Redeemer's Alchemist Stone
    47050,      // Assassin's Alchemist Stone
    60396,      // Mercurial Alchemist Stone
    60403,      // Indestructible Alchemist Stone
    60405,      // Mighty Alchemist Stone

    11459,      // Philosopher's Stone
    38070,      // Mercurial Stone
};

class npc_craftsman_alchemist : public CreatureScript
{
public:
    npc_craftsman_alchemist() : CreatureScript("npc_craftsman_alchemist") { }

    struct npc_craftsman_alchemistAI : public CraftsmanBaseAI
    {
        npc_craftsman_alchemistAI(Creature* creature) : CraftsmanBaseAI(creature)
        {
            trainerId = 28699;
            skillId = 165;
            recipeSubclass = 1;
        }

        void PrepareMainMenuItems(Player* player) override
        {
            std::string tailingText = sCraftsmanTextMgr->GetText(player, CMTEXT_ALCHEMY_SERVICE);
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

            return price / 50;
        }

        uint32 GetSpellCount(uint32 spellId) override
        {
            if (std::find(transmuteSpellIds.begin(), transmuteSpellIds.end(), spellId) != transmuteSpellIds.end())
                return 1;

            return 10;
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
        return new npc_craftsman_alchemistAI(creature);
    }

};

void AddSC_npc_craftsman_alchemist()
{
    new npc_craftsman_alchemist();
}
