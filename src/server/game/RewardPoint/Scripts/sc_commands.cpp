#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "RBAC.h"
#include "WorldSession.h"
#include "RewardPointMgr.h"

using namespace Trinity::ChatCommands;

class rdkp_commandscript : public CommandScript
{
public:
    rdkp_commandscript() : CommandScript("rdkp_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable rdkpCommandTable =
        {
            { "give",       HandleRdkpGiveCommand,  rbac::RBAC_PERM_COMMAND_CHARACTER_LEVEL,    Console::No },
            { "take",       HandleRdkpTakeCommand,  rbac::RBAC_PERM_COMMAND_CHARACTER_LEVEL,    Console::No },
            { "",           HandleRdkpCommand,      rbac::RBAC_PERM_COMMAND_ACCOUNT,            Console::No },
        };

        static ChatCommandTable commandTable =
        {
            { "rdkp",       rdkpCommandTable },
        };
        return commandTable;
    }

    static bool HandleRdkpGiveCommand(ChatHandler* handler, uint32 amount)
    {
        Player* target = handler->getSelectedPlayer();
        Player* master = handler->GetPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (amount > 0xffff || amount == 0)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        sRewardPointMgr->Update(target, 0, RPC_GAMEMASTER_GIVE, static_cast<int32>(amount));

        std::string message;
        message = fmt::format(RewardPointMgr::LocalizedNpcText(target, RPTXT_GIVE_PLAYER), handler->GetNameLink(master), amount);
        ChatHandler targetHandler(target->GetSession());
        targetHandler.SendSysMessage(message);

        message = fmt::format(RewardPointMgr::LocalizedNpcText(target, RPTXT_GIVE_GAMEMASTER), handler->GetNameLink(target), amount);
        handler->SendSysMessage(message);

        return true;
    }

    static bool HandleRdkpTakeCommand(ChatHandler* handler, uint32 amount)
    {
        Player* target = handler->getSelectedPlayer();
        Player* master = handler->GetPlayer();
        if (!target)
        {
            handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (amount > 0xffff || amount == 0)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        sRewardPointMgr->Update(target, 0, RPC_GAMEMASTER_TAKE, -static_cast<int32>(amount));

        std::string message;
        message = fmt::format(RewardPointMgr::LocalizedNpcText(target, RPTXT_TAKE_PLAYER), handler->GetNameLink(master), amount);
        ChatHandler targetHandler(target->GetSession());
        targetHandler.SendSysMessage(message);

        message = fmt::format(RewardPointMgr::LocalizedNpcText(target, RPTXT_TAKE_GAMEMASTER), handler->GetNameLink(target), amount);
        handler->SendSysMessage(message);

        return true;
    }

    static bool HandleRdkpCommand(ChatHandler* handler)
    {
        Player* target = handler->GetSession()->GetPlayer();
        int32 points = sRewardPointMgr->GetAvailable(target);

        handler->PSendSysMessage(RewardPointMgr::LocalizedNpcText(target, RPTXT_TELL_REWARD_POINTS).c_str(), points);

        return true;
    }

};

void AddSC_rpsc_commands()
{
    new rdkp_commandscript();
}
