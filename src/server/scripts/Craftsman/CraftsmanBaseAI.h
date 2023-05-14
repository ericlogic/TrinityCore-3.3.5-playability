#ifndef TRINITY_CRAFTSMAN_BASE_AI_H
#define TRINITY_CRAFTSMAN_BASE_AI_H

#include "Common.h"
#include "ScriptedCreature.h"
#include "SharedDefines.h"

#include <map>

namespace Trainer {
    class TC_GAME_API Spell;
}

class TC_GAME_API SpellInfo;

enum CraftsmanSender
{
    GOSSIP_SENDER_CRAFTSMAN_MAIN            = 0x80000000,
    GOSSIP_SENDER_CRAFTSMAN_RECIPES,
    GOSSIP_SENDER_CRAFTSMAN_OFFER_RECIPE,
    GOSSIP_SENDER_CRAFTSMAN_BUSY,
    GOSSIP_SENDER_CRAFTSMAN_ALREADY_LEARNED,
    GOSSIP_SENDER_CRAFTSMAN_RECIPE_LEARNED,
};

enum CraftsmanAction
{
    GOSSIP_ACTION_CRAFTSMAN_ACTION          = 0x80000000,
    GOSSIP_ACTION_OEM_SERVICE,
    GOSSIP_ACTION_OFFER_RECIPE,
    GOSSIP_ACTION_BACK,
};

enum CraftsmanGossip
{
    GOSSIP_TEXT_CRAFTSMAN_RECIPES           = 76000,    // What can I do for you, $R?
    GOSSIP_TEXT_CRAFTSMAN_BUSY              = 76001,    // Sorry! I'm busy now, please wait a moment.
    GOSSIP_TEXT_CRAFTSMAN_OFFER_RECIPE      = 76002,    // What are you going to give me?
    GOSSIP_TEXT_CRAFTSMAN_ALREADY_LEARNED   = 76003,    // Thanks! But I have already learned this before.
    GOSSIP_TEXT_CRAFTSMAN_RECIPE_LEARNED    = 76004,    // Thank you! $N!
};

class TC_GAME_API Player;
typedef std::map<uint32, uint32> Reagents;

struct TC_GAME_API CraftsmanBaseAI : public ScriptedAI
{
public:
    CraftsmanBaseAI(Creature* creature) : ScriptedAI(creature), customer(nullptr) { }

    bool OnGossipHello(Player* player) override;
    bool OnGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override;
    bool OnGossipSelectCode(Player* player, uint32 menuId, uint32 gossipListId, const char* code) override;
    void SpellHitTarget(WorldObject* wtarget, SpellInfo const* spell) override;

protected:
    void SendMainGossipMenuFor(Player* player);
    void SendRecipeGossipMenuFor(Player* player, std::string keyword);
    void SendOfferRecipeGossipMenuFor(Player* player);
    void SendBusyGossipMenuFor(Player* player);
    void SendAlreadyLearnedGossipMenuFor(Player* player);
    void SendRecipeLearnedGossipMenuFor(Player* player);

    void HandleMainSenderAction(Player* player, uint32 action);
    void HandleRecipesSenderAction(Player* player, uint32 action, const char* code = nullptr);
    void HandleOfferRecipeSenderAction(Player* player, uint32 action);
    void HandleBusySenderAction(Player* player, uint32 action);
    void HandleAlreadyLearnedSenderAction(Player* player, uint32 action);
    void HandleRecipeLearnedSenderAction(Player* player, uint32 action);

    uint PrepareRecipeMenuItems(Player* player, std::string keyword);

    void CastCreateItemSpellFor(Player* player, uint32 spellId);
    void LearnRecipeFor(Player* player, uint32 recipeId);

    void WhisperNeedReagentFor(Player* player, uint32 artifactId, const Reagents& reagents, uint32 count);
    void WhisperNotEnoughSlotFor(Player* player);
    void WhisperStartWorkingFor(Player* player, uint32 artifactId);
    void WhisperNoSuchItemFor(Player* player);

    virtual void PrepareDefaultRecipeMenuItems(Player* player) { };
    virtual void PrepareMainMenuItems(Player* player) = 0;

    virtual uint32 GetSpellPrice(uint32 spellId);
    virtual uint32 GetSpellCount(uint32 spellId) { return 1; };
    virtual uint32 GetReagents(const SpellInfo* spellInfo, Reagents& reagents);
    virtual uint32 AddReagents(Reagents& reagents, uint32 itemId, uint32 count);

protected:
    uint32 trainerId;
    uint32 skillId;
    uint32 recipeSubclass;

private:
    Player* customer;
    Reagents reagents;
    uint32 artifactId;
    uint32 count;
    uint32 cost;

};

#endif
