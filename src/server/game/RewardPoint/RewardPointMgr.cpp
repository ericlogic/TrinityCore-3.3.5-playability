#include "RewardPointMgr.h"

#include "Chat.h"
#include "Config.h"
#include "Creature.h"
#include "DatabaseEnv.h"
#include "Formulas.h"
#include "GossipDef.h"
#include "Group.h"
#include "GroupReference.h"
#include "Log.h"
#include "Map.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "QuestDef.h"
#include "WorldSession.h"

std::map<uint32, std::string> unk_npcstrings;
const std::string& RewardPointMgr::LocalizedNpcText(Player const* forPlayer, uint32 textId)
{
    LocaleConstant loc = forPlayer ? forPlayer->GetSession()->GetSessionDbLocaleIndex() : sWorld->GetDefaultDbcLocale();

    if (GossipText const* nt = sObjectMgr->GetGossipText(textId))
    {
        std::wstring wnamepart;
        NpcTextLocale const* ntl = sObjectMgr->GetNpcTextLocale(textId);
        if (loc != DEFAULT_LOCALE && ntl && !ntl->Text_0[0][loc].empty() && Utf8FitTo(ntl->Text_0[0][loc], wnamepart))
            return ntl->Text_0[0][loc];
        else
            return nt->Options[0].Text_0;
    }

    if (!unk_npcstrings.count(textId))
    {
        TC_LOG_ERROR("entities.player", "RewardPoint: npc text string #%u is not localized, at least for %s",
            textId, localeNames[loc]);

        std::ostringstream msg;
        msg << (loc == DEFAULT_LOCALE ? "<undefined string " : "<unlocalized string ") << textId << ">";
        unk_npcstrings[textId] = msg.str();
    }

    return unk_npcstrings[textId];
}

RewardPointMgr::RewardPointMgr()
: normalPoints(-1), elitePoints(-1), rareElitePoints(-1), worldBossPoints(-1), rarePoints(-1), questPoints(-1)
, inviterPoints(-1), inviteePoints(-1)
, characterBoost60Points(-1), characterBoost70Points(-1)
{
}

RewardPointMgr::~RewardPointMgr()
{
}

RewardPointMgr* RewardPointMgr::instance()
{
    static RewardPointMgr instance;
    return &instance;
}

int32 RewardPointMgr::GetAvailable(Player *player)
{
    uint32 const accountId = player->GetSession()->GetAccountId();
    char sql[256];

    sprintf(sql, "SELECT `points` FROM `account_reward_points` WHERE `accountId` = %u", accountId);
    QueryResult result = CharacterDatabase.Query(sql);

    if (!result)
        return 0;

    Field *fileds = result->Fetch();
    return fileds[0].GetInt32();
}

void RewardPointMgr::MonsterKilled(Player *player, CreatureTemplate const* cInfo, ObjectGuid guid)
{
    if (!guid)
        return;

    Creature* killed = player->GetMap()->GetCreature(guid);

    if (!killed)
        return;

    Group* group = player->GetGroup();
    uint8 playerLevel = player->GetLevel();
    uint8 maxMemberLevel = playerLevel;
    if (group)
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            if (Player* member = itr->GetSource())
                if (member->GetLevel() > maxMemberLevel)
                    maxMemberLevel = member->GetLevel();


    uint8 grayLevel = Trinity::XP::GetGrayLevel(maxMemberLevel);
    if (killed->GetLevel() <= grayLevel && maxMemberLevel - playerLevel > 8)
        return;

    RewardPointCause cause;
    int32 points = 0;

    if (killed->isWorldBoss())
    {
        points = GetWorldBossPoints();
        cause = RPC_WORLD_BOSS_KILL;
    }
    else if (killed->IsDungeonBoss())
    {
        points = GetDungeonBossPoints();
        cause = RPC_DUNGEON_BOSS_KILL;
    }
    else if (cInfo->rank == CREATURE_ELITE_RAREELITE)
    {
        points = GetRareElitePoints();
        cause = RPC_RARE_ELITE_KILL;
    }
    else if (cInfo->rank == CREATURE_ELITE_RARE)
    {
        points = GetRarePoints();
        cause = RPC_RARE_KILL;
    }
    else if (cInfo->rank == CREATURE_ELITE_ELITE)
    {
        points = GetElitePoints();
        cause = RPC_ELITE_KILL;
    }
    else
    {
        points = GetNormalPoints();
        cause = RPC_NORMAL_KILL;
    }

    if (points <= 0)
        return;

    if (IsRewarded(player, guid, cause, true))
        return;

    Update(player, guid, cause, points);
    NotifyGotPoints(player, points);
}

void RewardPointMgr::QuestCompleted(Player *player, Quest const* quest)
{
    int32 points = GetQuestPoints();
    if (points <= 0)
        return;

    Update(player, quest->GetQuestId(), RPC_QUEST_COMPLETE, points);
    NotifyGotPoints(player, points);
}

void RewardPointMgr::Update(Player *player, uint32 targetId, RewardPointCause cause, int32 points)
{
    uint32 const accountId = player->GetSession()->GetAccountId();
    uint32 const characterId = player->GetGUID().GetCounter();

    Update(accountId, characterId, targetId, cause, points);
}

void RewardPointMgr::Update(uint32 accountId, uint32 characterId, uint32 targetId, RewardPointCause cause, int32 points)
{
    char sql[256];

    sprintf(sql, "SELECT `points` FROM `account_reward_points` WHERE `accountId` = %u", accountId);
    QueryResult result = CharacterDatabase.Query(sql);

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
    if (!result)
    {
        sprintf(sql, "INSERT INTO `account_reward_points`(`accountId`, `points`)  VALUES(%u, %d)", accountId, points);
        trans->Append(sql);
    }
    else
    {
        sprintf(sql, "UPDATE `account_reward_points` SET `points` = `points` + %d WHERE `accountId` = %u", points, accountId);
        trans->Append(sql);
    }

    sprintf(sql,
        "INSERT INTO `reward_point_journal`(`timestamp`, `date`, `accountId`, `characterId`, `cause`, `targetId`, `points`) VALUES(NOW(), DATE_FORMAT(NOW(), '%%Y%%m%%d'), %u, %u, %u, %u, %d)",
        accountId, characterId, cause, targetId, points
        );
    trans->Append(sql);

    CharacterDatabase.CommitTransaction(trans);
}

bool RewardPointMgr::IsRewarded(Player *player, uint32 targetId, RewardPointCause cause, bool daily)
{
    uint32 const accountId = player->GetSession()->GetAccountId();
    uint32 const characterId = player->GetGUID().GetCounter();

    char sql[256];
    sprintf(sql, "SELECT * FROM `reward_point_journal` WHERE accountId = %u AND characterId = %u AND targetId = %u AND cause = %u", accountId, characterId, targetId, cause);

    if (daily)
        strcat(sql, " AND `date` = DATE_FORMAT(NOW(), '%Y%m%d')");

    QueryResult result = CharacterDatabase.Query(sql);

    return !!result;
}

bool RewardPointMgr::IsRewarded(Player *player, RewardPointCause cause)
{
    uint32 const accountId = player->GetSession()->GetAccountId();

    char sql[256];
    sprintf(sql, "SELECT * FROM `reward_point_journal` WHERE accountId = %u AND cause = %u", accountId, cause);

    QueryResult result = CharacterDatabase.Query(sql);

    return !!result;
}

bool RewardPointMgr::RedeemCoupon(Player *player, const std::string& code)
{
    QueryResult result;
    char sql[256];

    sprintf(sql, "SELECT `id`, `points` FROM `reward_point_coupon` WHERE `code` = '%s' AND `rest` > 0", code.c_str());
    result = CharacterDatabase.Query(sql);
    if (result)
    {
        Field *fileds = result->Fetch();
        uint32 couponId = fileds[0].GetUInt32();
        int32 points = fileds[1].GetInt32();

        if (points <= 0 || IsRewarded(player, couponId, RPC_COUPON_REDEEM, false))
            return false;

        sprintf(sql, "UPDATE `reward_point_coupon` SET `rest` = `rest` - 1 WHERE `id` = %u", couponId);
        result = CharacterDatabase.Query(sql);

        Update(player, couponId, RPC_COUPON_REDEEM, points);
        NotifyGotPoints(player, points);
        return true;
    }
    else
    {
        if (IsRewarded(player, RPC_FRIEND_RECRUIT))
            return false;

        uint32 const inviteeId = player->GetSession()->GetAccountId();
        uint32 const characterId = player->GetGUID().GetCounter();

        sprintf(sql, "SELECT `id` FROM `account` WHERE `username` = '%s'", code.c_str());
        result = LoginDatabase.Query(sql);

        if (!result)
            return false;

        uint32 const inviterId = result->Fetch()[0].GetUInt32();

        if (inviteeId == inviterId)
            return false;

        int32 inviteePoints = GetInviteePoints();
        int32 inviterPoints = GetInviterPoints();

        if (inviteePoints <= 0)
            return false;

        if (inviterPoints > 0)
            Update(inviterId, 0, inviteeId, RPC_RECRUIT_FRIEND, inviterPoints);

        Update(inviteeId, characterId, inviterId, RPC_FRIEND_RECRUIT, inviteePoints);
        NotifyGotPoints(player, inviteePoints);
        return true;
    }
}

void RewardPointMgr::NotifyGotPoints(Player* player, int32 points)
{
    ChatHandler handler(player->GetSession());
    std::ostringstream message;
    handler.PSendSysMessage(LocalizedNpcText(player, RPTXT_GET_REWARD_POINTS).c_str(), points);
}

int32 RewardPointMgr::GetDungeonBossPoints()
{
    if (dungeonBossPoints < 0) {
        dungeonBossPoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.DungeonBoss", 0);
        if (dungeonBossPoints < 0) dungeonBossPoints = 0;
    }

    return dungeonBossPoints;
}

int32 RewardPointMgr::GetNormalPoints()
{
    if (normalPoints < 0) {
        normalPoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.Normal", 0);
        if (normalPoints < 0) normalPoints = 0;
    }

    return normalPoints;
}

int32 RewardPointMgr::GetElitePoints()
{
    if (elitePoints < 0) {
        elitePoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.Elite", 0);
        if (elitePoints < 0) elitePoints = 0;
    }

    return elitePoints;
}

int32 RewardPointMgr::GetRareElitePoints()
{
    if (rareElitePoints < 0) {
        rareElitePoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.RareElite", 0);
        if (rareElitePoints < 0) rareElitePoints = 0;
    }

    return rareElitePoints;
}

int32 RewardPointMgr::GetWorldBossPoints()
{
    if (worldBossPoints < 0) {
        worldBossPoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.WorldBoss", 0);
        if (worldBossPoints < 0) worldBossPoints = 0;
    }

    return worldBossPoints;
}

int32 RewardPointMgr::GetRarePoints()
{
    if (rarePoints < 0) {
        rarePoints = sConfigMgr->GetIntDefault("RewardPoint.MonsterKill.Rare", 0);
        if (rarePoints < 0) rarePoints = 0;
    }

    return rarePoints;
}

int32 RewardPointMgr::GetQuestPoints()
{
    if (questPoints < 0) {
        questPoints = sConfigMgr->GetIntDefault("RewardPoint.Quest", 0);
        if (questPoints < 0) questPoints = 0;
    }

    return questPoints;
}

int32 RewardPointMgr::GetInviterPoints()
{
    if (inviterPoints < 0) {
        inviterPoints = sConfigMgr->GetIntDefault("RewardPoint.FriendsRecruit.Inviter", 0);
        if (inviterPoints < 0) inviterPoints = 0;
    }

    return inviterPoints;
}

int32 RewardPointMgr::GetInviteePoints()
{
    if (inviteePoints < 0) {
        inviteePoints = sConfigMgr->GetIntDefault("RewardPoint.FriendsRecruit.Invitee", 0);
        if (inviteePoints < 0) inviteePoints = 0;
    }

    return inviteePoints;
}

int32 RewardPointMgr::GetCharacterBoost60Points()
{
    if (characterBoost60Points < 0) {
        characterBoost60Points = sConfigMgr->GetIntDefault("RewardPoint.CharacterBoost.60", 0);
        if (characterBoost60Points < 0) characterBoost60Points = 0;
    }

    return characterBoost60Points;
}

int32 RewardPointMgr::GetCharacterBoost70Points()
{
    if (characterBoost70Points < 0) {
        characterBoost70Points = sConfigMgr->GetIntDefault("RewardPoint.CharacterBoost.70", 0);
        if (characterBoost70Points < 0) characterBoost70Points = 0;
    }

    return characterBoost70Points;
}

void AddSC_rpsc_character_booster();
void AddSC_rpsc_commands();

void AddRewardPointScripts()
{
    AddSC_rpsc_character_booster();
    AddSC_rpsc_commands();
}
