#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

namespace stl {
    using namespace SKSE::stl;

    template <class T>
    void write_thunk_call(std::uintptr_t a_src) {
        auto& trampoline = SKSE::GetTrampoline();
        T::func          = trampoline.write_call<5>(a_src, T::thunk);
    }

    template <class F, std::size_t idx, class T>
    void write_vfunc() {
        REL::Relocation<std::uintptr_t> vtbl{F::VTABLE[0]};
        T::func = vtbl.write_vfunc(idx, T::thunk);
    }
}