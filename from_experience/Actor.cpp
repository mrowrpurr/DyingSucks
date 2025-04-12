#include "Actor.h"

#include <SkyrimScripting/Logging.h>

#include "Offsets.h"

using namespace RE;

bool ActorEx::IsPlayerOrTeam(Actor* actor) {
    if (actor->GetPlayerControls()) {
        return true;
    }

    if (actor->IsPlayerTeammate()) {
        return true;
    }

    if (auto cmdr = actor->GetCommandingActor()) {
        if (IsPlayerOrTeam(cmdr.get())) {
            return true;
        }
    }
    return false;
}

// Actor::DamageHealth
void ActorEx::ModTrackedDamage_Hook(AIProcess* process, Actor* attacker, float damage) {
    auto* target = process ? process->GetUserData() : nullptr;
    if (attacker && target) {
        if (auto* attackerBase = attacker->GetActorBase()) {
            if (auto* targetBase = target->GetActorBase()) {
                Log("[DamageHealth] attacker: {} target: {} damage: {}", attackerBase->GetName(), targetBase->GetName(), damage);
            }
        }
    }
    _ModTrackedDamage(process, attacker, damage);
}

// Unknown::HandleAction
void ActorEx::KillMoveStart_Hook(Actor* victim, Actor* killer) {
    float currentHealth = victim->GetActorValue(ActorValue::kHealth);
    if (victim && victim->IsPlayerRef()) {
        Log("Muhahahahahaa you can't kill cam me!");
    } else {
        _KillMoveStart(victim, killer);
    }
}

void ActorEx::Install(SKSE::Trampoline& trampoline) {
    _ModTrackedDamage = trampoline.write_call<5>(Offset::Actor::DamageHealth.address() + OFFSET(0xFD, 0x131, 0xFD), &ActorEx::ModTrackedDamage_Hook);
    _KillMoveStart    = trampoline.write_call<5>(Offset::Unknown::HandleAction.address() + OFFSET(0x1A7, 0x1D1, 0x1A7), &ActorEx::KillMoveStart_Hook);
}
