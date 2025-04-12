#include <SkyrimScripting/Plugin.h>

namespace MyHooks {
    using func_t     = void (*)(RE::Actor*, RE::Actor*, float, bool, bool);
    func_t _original = nullptr;

    void Hooked_KillImpl(RE::Actor* killedActor, RE::Actor* a_attacker, float a_damage, bool a_sendEvent, bool a_ragdollInstant) {
        Log("KillImpl hook: {} killed by {} for {} dmg (event: {}, ragdoll: {})", killedActor->GetName(), a_attacker ? a_attacker->GetName() : "Unknown", a_damage, a_sendEvent,
            a_ragdollInstant);

        if (killedActor->IsPlayerRef()) {
            Log("HAHAHAHAH you CAN'T KILL meeee!!!");
            return;
        }

        _original(killedActor, a_attacker, a_damage, a_sendEvent, a_ragdollInstant);
    }

    void Install() {
        constexpr std::uint32_t index = 270;
        const auto              hook  = reinterpret_cast<std::uintptr_t>(&Hooked_KillImpl);

        // Patch base Actor
        {
            REL::Relocation<std::uintptr_t> vtbl{RE::VTABLE_Actor[0]};
            std::uintptr_t                  old = vtbl.write_vfunc(index, hook);
            _original                           = reinterpret_cast<func_t>(old);
            Log("Hooked Actor::KillImpl");
        }

        // Patch Character (most NPCs)
        {
            REL::Relocation<std::uintptr_t> vtbl{RE::VTABLE_Character[0]};
            vtbl.write_vfunc(index, hook);
            Log("Hooked Character::KillImpl");
        }

        // Patch PlayerCharacters
        {
            REL::Relocation<std::uintptr_t> vtbl{RE::VTABLE_PlayerCharacter[0]};
            vtbl.write_vfunc(index, hook);
            Log("Hooked PlayerCharacter::KillImpl");
        }
    }
}

SKSEPlugin_Entrypoint { MyHooks::Install(); }