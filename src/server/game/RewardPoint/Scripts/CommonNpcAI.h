#ifndef _BASE_NPC_AI_H
#define _BASE_NPC_AI_H

#include "CreatureAI.h"

class Creature;

enum RewardPointGossipsSender : uint32
{
    GOSSIP_SENDER_BEGIN                     = 1000,
    GOSSIP_SENDER_HELLO,
    GOSSIP_SENDER_INTRODUCE,
    GOSSIP_SENDER_HOWTO,
    GOSSIP_SENDER_NOT_ENOUGH_POINTS,
    GOSSIP_SENDER_POWERFUL_ENOUGH,
    GOSSIP_SENDER_INVALID_CODE,
};

enum RewardPointGossipsAction : uint32
{
    GOSSIP_ACTION_BEGIN                     = 1000,
    GOSSIP_ACTION_CLOSE,
    GOSSIP_ACTION_BACK,
    GOSSIP_ACTION_REDEEM_CODE,

    GOSSIP_ACTION_TELL_MY_POINTS,
    GOSSIP_ACTION_INTRODUCE,
    GOSSIP_ACTION_HOWTO_GET_POINTS,

    GOSSIP_ACTION_CHARACTER_BOOST_60,
    GOSSIP_ACTION_CHARACTER_BOOST_70,
};

class RewardPointCommonNpcAI : public CreatureAI
{
public:
    RewardPointCommonNpcAI(Creature* creature) : CreatureAI(creature) {}
    virtual ~RewardPointCommonNpcAI();

    virtual void UpdateAI(uint32 /*diff*/) override {}

    virtual void SendGossipHello(Player *player) = 0;

    void SendGossipIntroduce(Player* player);
    void SendGossipHowTo(Player* player);
    void SendGossipRedeemFailed(Player* player);

protected:
    void AddCommonGossipItems(Player *player, uint32 sender);
    void AddCloseGossipItem(Player *player, std::string const& text, uint32 sender);
    void AddBackGossipItem(Player *player, std::string const& text, uint32 sender);
    bool HandleCommonGoosip(Player* player, uint32 action);
    bool HandleCommonGoosipCode(Player* player, uint32 action, char const *code);

private:
    bool HandleRedeemCode(Player* player, char const *code);
};

#endif//_BASE_NPC_AI_H
