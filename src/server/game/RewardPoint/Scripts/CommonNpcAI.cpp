#include "CommonNpcAI.h"

#include "Player.h"
#include "World.h"
#include "Creature.h"
#include "WorldSession.h"
#include "GossipDef.h"
#include "ObjectMgr.h"
#include "Log.h"
#include "ScriptedGossip.h"
#include "RewardPointMgr.h"

RewardPointCommonNpcAI::~RewardPointCommonNpcAI()
{

}

void RewardPointCommonNpcAI::SendGossipIntroduce(Player* player)
{
    player->PlayerTalkClass->ClearMenus();

    AddBackGossipItem(player, RewardPointMgr::LocalizedNpcText(player, RPTXT_GOTIT), GOSSIP_SENDER_INTRODUCE);

    player->PlayerTalkClass->SendGossipMenu(RPTXT_TELL_WHATIS, me->GetGUID());
}

void RewardPointCommonNpcAI::SendGossipHowTo(Player* player)
{
    player->PlayerTalkClass->ClearMenus();

    player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, GOSSIP_ICON_TALK, RewardPointMgr::LocalizedNpcText(player, PRTXT_REDEEM_CODE),
        GOSSIP_SENDER_HOWTO, GOSSIP_ACTION_REDEEM_CODE, "", 0, true);

    AddBackGossipItem(player, RewardPointMgr::LocalizedNpcText(player, RPTXT_GOTIT), GOSSIP_SENDER_HOWTO);

    player->PlayerTalkClass->SendGossipMenu(RPTXT_TELL_HOWTO, me->GetGUID());
}

void RewardPointCommonNpcAI::SendGossipRedeemFailed(Player* player)
{
    player->PlayerTalkClass->ClearMenus();

    AddBackGossipItem(player, RewardPointMgr::LocalizedNpcText(player, RPTXT_GOTIT), GOSSIP_SENDER_INVALID_CODE);

    player->PlayerTalkClass->SendGossipMenu(RPTXT_INVALID_CODE, me->GetGUID());
}

void RewardPointCommonNpcAI::AddCommonGossipItems(Player *player, uint32 sender)
{
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, RewardPointMgr::LocalizedNpcText(player, RPTXT_HOWMANY), sender, GOSSIP_ACTION_TELL_MY_POINTS);
    AddGossipItemFor(player, GOSSIP_ICON_TALK, RewardPointMgr::LocalizedNpcText(player, RPTXT_WHATIS), sender, GOSSIP_ACTION_INTRODUCE);
    AddGossipItemFor(player, GOSSIP_ICON_TALK, RewardPointMgr::LocalizedNpcText(player, RPTXT_HOWTO), sender, GOSSIP_ACTION_HOWTO_GET_POINTS);
}

void RewardPointCommonNpcAI::AddCloseGossipItem(Player *player, std::string const& text, uint32 sender)
{
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, text, sender, GOSSIP_ACTION_CLOSE);
}

void RewardPointCommonNpcAI::AddBackGossipItem(Player *player, std::string const& text, uint32 sender)
{
    AddGossipItemFor(player, GOSSIP_ICON_CHAT, text, sender, GOSSIP_ACTION_BACK);
}

bool RewardPointCommonNpcAI::HandleCommonGoosip(Player* player, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_TELL_MY_POINTS:
            me->Whisper(Trinity::StringFormat(RewardPointMgr::LocalizedNpcText(player, RPTXT_TELL_REWARD_POINTS),
                sRewardPointMgr->GetAvailable(player)), LANG_UNIVERSAL, player);
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        case GOSSIP_ACTION_INTRODUCE:
            SendGossipIntroduce(player);
            return true;
        case GOSSIP_ACTION_HOWTO_GET_POINTS:
            SendGossipHowTo(player);
            return true;
        case GOSSIP_ACTION_CLOSE:
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        case GOSSIP_ACTION_BACK:
            SendGossipHello(player);
            return true;
        default:
            return false;
    }
}

bool RewardPointCommonNpcAI::HandleCommonGoosipCode(Player* player, uint32 action, char const *code)
{
    switch (action)
    {
        case GOSSIP_ACTION_REDEEM_CODE:
            return HandleRedeemCode(player, code);
        default:
            return false;
    }
}

bool RewardPointCommonNpcAI::HandleRedeemCode(Player* player, char const *code)
{
    std::ostringstream oss;
    bool valid = true;
    for (char const* p = code; *p; ++p)
    {
        if ((*p >= 48 && *p <= 57) || (*p >= 65 && *p <= 90))
        {
            oss << *p;
        }
        else if (*p >= 97 && *p <= 122)
        {
            oss << (char)((*p) - 32);
        }
        else
        {
            valid = false;
        }
    }

    if (!valid || !sRewardPointMgr->RedeemCoupon(player, oss.str()))
    {
        SendGossipRedeemFailed(player);
        return true;
    }

    player->PlayerTalkClass->SendCloseGossip();
    return true;
}
