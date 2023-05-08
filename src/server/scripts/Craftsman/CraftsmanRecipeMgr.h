#ifndef TRINITY_CRAFTSMAN_RECIPE_MGR_H
#define TRINITY_CRAFTSMAN_RECIPE_MGR_H

#include "Common.h"
#include "ScriptMgr.h"

#include <string>
#include <unordered_map>
#include <vector>

class TC_GAME_API Player;

struct TC_GAME_API CraftsmanRecipe
{
    CraftsmanRecipe(Player* player, uint32 recipeId);

    Player* player;
    uint32 recipeId;
    std::string name;
    uint32 spellId;
    uint32 skillId;
    uint32 skillRank;
};

class TC_GAME_API CraftsmanRecipeMgr
{
private:
    CraftsmanRecipeMgr() { }
    ~CraftsmanRecipeMgr() { }
public:
    static CraftsmanRecipeMgr* instance();

    const std::vector<CraftsmanRecipe>& GetRecipesByPlayer(Player* player);
    const CraftsmanRecipe* GetRecipeBySpellId(Player* player, uint32 spellId);
    const CraftsmanRecipe* GetRecipeById(Player* player, uint32 recipeId);
    void AddRecipeForPlayer(Player* player, uint32 recipeId);

    const std::string& GetKeyword(Player* player);
    void SetKeyword(Player* player, const std::string& keyword);

private:
    void LoadFromDBForPlayer(Player* player);
    void UnloadForPlayer(Player* player);

private:
    friend class TC_GAME_API CraftsmanRecipeLoader;
    std::unordered_map<uint32, std::vector<CraftsmanRecipe>> craftsmanRecipes;
    std::unordered_map<uint32, std::string> keywords;
};

#define sCraftsmanRecipeMgr CraftsmanRecipeMgr::instance()

#endif
