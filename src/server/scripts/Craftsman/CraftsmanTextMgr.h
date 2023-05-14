#ifndef TRINITY_CRAFTSMAN_TEXT_MGR_H
#define TRINITY_CRAFTSMAN_TEXT_MGR_H

#include "Common.h"
#include "SharedDefines.h"

#include <unordered_map>
#include <vector>

enum eCraftsmanText : uint32
{
    CMTEXT_TAILORING_SERVICE    = 1000,     // Tailoring service
    CMTEXT_SMELTING_SERVICE     = 1001,     // Smelt ores
    CMTEXT_CURRENT_KEYWORD      = 1100,     // Keyword: {0}
    CMTEXT_INPUT_KEYWORD        = 1101,     // <Click here to enter keyword for search>
    CMTEXT_NEED_REAGNETS        = 1102,     // You must supply {1} to make {0}.
    CMTEXT_NOT_ENOUGH_SLOT      = 1103,     // Your bag is full!
    CMTEXT_START_WORKING        = 1104,     // {0} is being made, please wait...
    CMTEXT_OFFER_RECIPE         = 1105,     // I have a recipe.
    CMTEXT_BACK                 = 1106,     // <Back>
    CMTEXT_NO_SUCH_ITEM         = 1107,     // You don't have such item.
    CMTEXT_RECIPE_LEARNED       = 1108,     // I've learned it, thank you!
    CMTEXT_WELL                 = 1109,     // Well!
    CMTEXT_UR_WELCOME           = 1110,     // You are welcome!
};

class TC_GAME_API Player;

class TC_GAME_API CraftsmanTextMgr
{
private:
    CraftsmanTextMgr() { }
    ~CraftsmanTextMgr() { }
public:
    static CraftsmanTextMgr* instance();

    void LoadCraftsmanTexts();
    void LoadCraftsmanTextLocales();

    const std::string& GetText(LocaleConstant locale, eCraftsmanText textId);
    const std::string& GetText(const Player* player, eCraftsmanText textId);

private:
    std::unordered_map<uint32, std::vector<std::string>> craftsmanTexts;

};

#define sCraftsmanTextMgr CraftsmanTextMgr::instance()

#endif
