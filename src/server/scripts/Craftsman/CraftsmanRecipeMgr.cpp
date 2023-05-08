#include "CraftsmanRecipeMgr.h"
#include "DatabaseEnv.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "WorldSession.h"

CraftsmanRecipe::CraftsmanRecipe(Player* player, uint32 recipeId) : player(player), recipeId(recipeId)
{
    const ItemTemplate* item = sObjectMgr->GetItemTemplate(recipeId);
    if (item == nullptr)
        return;

    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();

    spellId = item->Spells[1].SpellId;

    const SpellInfo* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    name = spellInfo->SpellName[locale];

    skillId = item->RequiredSkill;
    skillRank = item->RequiredSkillRank;
}

class TC_GAME_API CraftsmanRecipeLoader : public PlayerScript
{
public:
    CraftsmanRecipeLoader() : PlayerScript("CraftsmanRecipeLoader") { }

    void OnLogin(Player* player, bool firstLogin) override
    {
        sCraftsmanRecipeMgr->LoadFromDBForPlayer(player);
    }

    void OnLogout(Player* player) override
    {
        sCraftsmanRecipeMgr->UnloadForPlayer(player);
    }

};

const std::vector<CraftsmanRecipe>& CraftsmanRecipeMgr::GetRecipesByPlayer(Player* player)
{
    uint32 characterId = player->GetGUID().GetCounter();
    return craftsmanRecipes[characterId];
}

const CraftsmanRecipe* CraftsmanRecipeMgr::GetRecipeBySpellId(Player* player, uint32 spellId)
{
    uint32 characterId = player->GetGUID().GetCounter();
    const std::vector<CraftsmanRecipe>& recipes = craftsmanRecipes[characterId];

    for (std::vector<CraftsmanRecipe>::const_iterator it = recipes.begin(); it != recipes.end(); ++it)
    {
        if (it->spellId == spellId)
            return &(*it);
    }

    return nullptr;
}

const CraftsmanRecipe* CraftsmanRecipeMgr::GetRecipeById(Player* player, uint32 recipeId)
{
    uint32 characterId = player->GetGUID().GetCounter();
    const std::vector<CraftsmanRecipe>& recipes = craftsmanRecipes[characterId];

    for (std::vector<CraftsmanRecipe>::const_iterator it = recipes.begin(); it != recipes.end(); ++it)
    {
        if (it->recipeId == recipeId)
            return &(*it);
    }

    return nullptr;
}

void CraftsmanRecipeMgr::AddRecipeForPlayer(Player* player, uint32 recipeId)
{
    uint32 characterId = player->GetGUID().GetCounter();
    std::string sql = fmt::format("INSERT INTO character_craftsman_recipes(`guid`, `recipeid`, `time`) VALUES({0}, {1}, NOW())", characterId, recipeId);
    CharacterDatabase.Query(sql.c_str());

    CraftsmanRecipe recipe(player, recipeId);
    craftsmanRecipes[characterId].push_back(recipe);
}

const std::string& CraftsmanRecipeMgr::GetKeyword(Player* player)
{
    uint32 characterId = player->GetGUID().GetCounter();
    return keywords[characterId];
}

void CraftsmanRecipeMgr::SetKeyword(Player* player, const std::string& keyword)
{
    uint32 characterId = player->GetGUID().GetCounter();
    keywords[characterId] = keyword;
}

void CraftsmanRecipeMgr::LoadFromDBForPlayer(Player* player)
{
    uint32 characterId = player->GetGUID().GetCounter();
    std::string sql = fmt::format("SELECT `recipeid` FROM character_craftsman_recipes WHERE `guid` = {0} ORDER BY `time` DESC", characterId);
    QueryResult result = CharacterDatabase.Query(sql.c_str());
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 recipeId = fields[0].GetUInt32();

        CraftsmanRecipe recipe(player, recipeId);
        craftsmanRecipes[characterId].push_back(recipe);
    } while (result->NextRow());
}

void CraftsmanRecipeMgr::UnloadForPlayer(Player* player)
{
    uint32 characterId = player->GetGUID().GetCounter();
    craftsmanRecipes.erase(characterId);
    keywords.erase(characterId);
}

CraftsmanRecipeMgr* CraftsmanRecipeMgr::instance()
{
    static CraftsmanRecipeMgr instance;
    return &instance;
}

void AddSC_craftsman_recipe_loader()
{
    new CraftsmanRecipeLoader();
}
