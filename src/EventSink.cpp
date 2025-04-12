// #include "EventSink.h"

// #include <SkyrimScripting/Logging.h>

// EventSink* EventSink::GetSingleton() {
//     static EventSink singleton;
//     return &singleton;
// }

// void EventSink::InstallHooks() {
//     auto* scriptEventSource = RE::ScriptEventSourceHolder::GetSingleton();
//     if (scriptEventSource) {
//         scriptEventSource->AddEventSink<RE::TESDeathEvent>(GetSingleton());
//         Log("TESDeathEvent sink installed.");
//     } else {
//         Log("Failed to install EventSink for TESDeathEvent.");
//     }

//     auto* player = RE::PlayerCharacter::GetSingleton();
//     if (player) {
//         player->AsBGSActorDeathEventSource()->AddEventSink<RE::BGSActorDeathEvent>(GetSingleton());
//         Log("BGSActorDeathEvent sink installed.");
//     } else {
//         Log("Failed to install EventSink for BGSActorDeathEvent.");
//     }
// }

// RE::BSEventNotifyControl EventSink::ProcessEvent(const RE::BGSActorDeathEvent* event, RE::BSTEventSource<RE::BGSActorDeathEvent>* eventSource) {
//     Log("[BGSActorDeathEvent] Player died!");
//     return RE::BSEventNotifyControl::kContinue;
// }

// RE::BSEventNotifyControl EventSink::ProcessEvent(const RE::TESDeathEvent* event, RE::BSTEventSource<RE::TESDeathEvent>* eventSource) {
//     if (event && event->actorDying && event->actorDying->IsPlayerRef()) {
//         auto* player = RE::PlayerCharacter::GetSingleton();

//         uintptr_t* vtbl = *(uintptr_t**)player;

//         Log("[TESDeathEvent] Player dead or dying. Dead: {}", event->dead ? "true" : "false");
//     }
//     return RE::BSEventNotifyControl::kContinue;
// }
