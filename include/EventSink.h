// #pragma once

// #include <RE/Skyrim.h>

// class EventSink : public RE::BSTEventSink<RE::BGSActorDeathEvent>,
//                   RE::BSTEventSink<RE::TESDeathEvent>

// {
// public:
//     static EventSink* GetSingleton();
//     static void       InstallHooks();

//     RE::BSEventNotifyControl ProcessEvent(const RE::BGSActorDeathEvent* _event, RE::BSTEventSource<RE::BGSActorDeathEvent>* eventSource) override;
//     RE::BSEventNotifyControl ProcessEvent(const RE::TESDeathEvent* event, RE::BSTEventSource<RE::TESDeathEvent>* eventSource) override;
// };
