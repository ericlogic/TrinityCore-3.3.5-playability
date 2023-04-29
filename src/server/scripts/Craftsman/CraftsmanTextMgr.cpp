#include "CraftsmanTextMgr.h"
#include "DatabaseEnv.h"
#include "Player.h"
#include "WorldSession.h"

void AddLocaleString(std::string&& value, LocaleConstant locale, std::vector<std::string>& texts)
{
    if (!value.empty())
    {
        if (texts.size() <= size_t(locale))
            texts.resize(locale + 1);

        texts[locale] = std::move(value);
    }
}

CraftsmanTextMgr* CraftsmanTextMgr::instance()
{
    static CraftsmanTextMgr instance;
    return &instance;
}

void CraftsmanTextMgr::LoadCraftsmanTexts()
{
    QueryResult result = WorldDatabase.Query("SELECT id, text FROM craftsman_text");
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 id = fields[0].GetUInt32();

        std::vector<std::string>& texts = craftsmanTexts[id];
        AddLocaleString(fields[1].GetString(), LOCALE_enUS, texts);
    } while (result->NextRow());
}

void CraftsmanTextMgr::LoadCraftsmanTextLocales()
{
    QueryResult result = WorldDatabase.Query("SELECT id, locale, text FROM craftsman_text_locale");
    if (!result)
        return;

    do
    {
        Field* fields = result->Fetch();
        uint32 id = fields[0].GetUInt32();
        std::string localeName  = fields[1].GetString();
        LocaleConstant locale = GetLocaleByName(localeName);

        std::vector<std::string>& texts = craftsmanTexts[id];
        AddLocaleString(fields[2].GetString(), locale, texts);
    } while (result->NextRow());
}

const std::string& CraftsmanTextMgr::GetText(LocaleConstant locale, eCraftsmanText textId)
{
    static const std::string emptyString = "<Unknown Craftsman Text>";

    std::unordered_map<uint32, std::vector<std::string>>::iterator matched = craftsmanTexts.find(textId);
    if (matched == craftsmanTexts.end())
        return emptyString;

    if (matched->second.size() > locale && !matched->second[locale].empty())
        return matched->second[locale];

    return matched->second[LOCALE_enUS];
}

const std::string& CraftsmanTextMgr::GetText(const Player* player, eCraftsmanText textId)
{
    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();
    return GetText(locale, textId);
}

void AddSC_craftsman_text_manager()
{
    sCraftsmanTextMgr->LoadCraftsmanTexts();
    sCraftsmanTextMgr->LoadCraftsmanTextLocales();
}
