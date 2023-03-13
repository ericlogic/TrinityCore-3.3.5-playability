#ifndef _REWARD_POINT_MGR_H
#define _REWARD_POINT_MGR_H

#include "Define.h"

enum RewardPointCause
{
    RPC_GAMEMASTER_GIVE = 100,
    RPC_DAILY_LOGIN,
    RPC_QUEST_COMPLETE,
    RPC_DUNGEON_BOSS_KILL,
    RPC_NORMAL_KILL,
    RPC_ELITE_KILL,
    RPC_RARE_ELITE_KILL,
    RPC_WORLD_BOSS_KILL,
    RPC_RARE_KILL,
    RPC_FRIEND_RECRUIT,
    RPC_RECRUIT_FRIEND,
    RPC_COUPON_REDEEM,

    RPC_GAMEMASTER_TAKE = 500,
    RPC_CHARACTER_BOOST_60,
    RPC_CHARACTER_BOOST_70,
};

enum RewardPointText : uint32
{
    // System/Command text
    RPTXT_GET_REWARD_POINTS = 80000,        // You got %d reward point(s).
    RPTXT_TELL_REWARD_POINTS = 80001,       // You have %d reward point(s).
    RPTXT_GIVE_GAMEMASTER = 80002,          // You gave {1} reward point(s) to {0}.
    RPTXT_GIVE_PLAYER = 80003,              // {0} gave {1} reward point(s) to you.
    RPTXT_TAKE_GAMEMASTER = 80004,          // You took {1} reward point(s) from {0}.
    RPTXT_TAKE_PLAYER = 80005,              // {0} took {1} reward point(s) from you.
    RPTXT_RESERVE_SPACE = 80006,            // Please reserve %d inventory spaces for starting equipments!

    // Gossip item
    RPTXT_HOWMANY = 80100,                  // How many reward points do I have?
    RPTXT_WHATIS = 80101,                   // What is reward points?
    RPTXT_HOWTO = 80102,                    // How to earn reward points?
    RPTXT_NEVERMIND = 80103,                // Nevermind!
    RPTXT_GOTIT = 80104,                    // Got it!
    RPTXT_BOOST_TO_LV60 = 80105,            // Boost to level 60 (%d reward points).
    RPTXT_BOOST_TO_LV70 = 80106,            // Boost to level 70 (%d reward points).
    RPTXT_BOOST_TO_LV60_CONFIRM = 80107,    // Cost %d reward points to boost to level 60?
    RPTXT_BOOST_TO_LV70_CONFIRM = 80108,    // Cost %d reward points to boost to level 70?
    RPTXT_WELL = 80109,                     // Well!
    PRTXT_REDEEM_CODE = 80110,              // I have a code!

    // Gossip text
    RPTXT_TELL_WHATIS = 80200,              // Reward points are tokens shared between characters of your account. There are opportunities to earn reward points when you venture through the world.  You can use these points to redeem items or value-added services!
    RPTXT_TELL_HOWTO = 80201,               // There are many ways to earn reward points. Complete quests, kill dungeon bosses, etc. Reward points are also available from some of special events.
    RPTXT_CHARACTER_BOOSTER_HELLO = 80202,  // Hello, $C. I can boost your level, but you have to prove to me that you're already a battle-tested adventurer.
    RPTXT_NOT_ENOUGH_POINTS = 80203,        // Sorry! You don't have enough reward points!
    RPTXT_POWERFUL_ENOUGH = 80204,          // You look powerful and don't need this service anymore!
    RPTXT_INVALID_CODE = 80205,             // Sorry! I can't redeem this code for you! Maybe the code is wrong or already redeemed!
};

struct CreatureTemplate;

class Player;
class Quest;

class TC_GAME_API RewardPointMgr
{
public:
    static const std::string& LocalizedNpcText(Player const* forPlayer, uint32 textId);

private:
    RewardPointMgr();
    ~RewardPointMgr();
    RewardPointMgr(RewardPointMgr const&) = delete;
    RewardPointMgr& operator=(RewardPointMgr const&) = delete;

public:
    static RewardPointMgr* instance();

    int32 GetAvailable(Player *player);
    void MonsterKilled(Player *player, CreatureTemplate const* cInfo, ObjectGuid guid);
    void QuestCompleted(Player *player, Quest const* quest);
    void Update(Player *player, uint32 targetId, RewardPointCause cause, int32 points);
    bool IsRewarded(Player *player, uint32 targetId, RewardPointCause cause, bool daily);
    bool IsRewarded(Player *player, RewardPointCause cause);
    bool RedeemCoupon(Player *player, const std::string& code);
    void NotifyGotPoints(Player* player, int32 points);

private:
    void Update(uint32 accountId, uint32 characterId, uint32 targetId, RewardPointCause cause, int32 points);

public:
    int32 GetDungeonBossPoints();
    int32 GetNormalPoints();
    int32 GetElitePoints();
    int32 GetRareElitePoints();
    int32 GetWorldBossPoints();
    int32 GetRarePoints();
    int32 GetQuestPoints();

    int32 GetInviterPoints();
    int32 GetInviteePoints();

    int32 GetCharacterBoost60Points();
    int32 GetCharacterBoost70Points();

private:
    int32 dungeonBossPoints;
    int32 normalPoints;
    int32 elitePoints;
    int32 rareElitePoints;
    int32 worldBossPoints;
    int32 rarePoints;
    int32 questPoints;

    int32 inviterPoints;
    int32 inviteePoints;

    int32 characterBoost60Points;
    int32 characterBoost70Points;
};

#define sRewardPointMgr RewardPointMgr::instance()

void AddRewardPointScripts();

#endif//_REWARD_POINT_MGR_H
