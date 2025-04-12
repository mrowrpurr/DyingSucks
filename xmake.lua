add_rules("mode.debug", "mode.release")

set_languages("c++23")

option("commonlib")
    set_default("skyrim-commonlib-ae")
option_end()

if not has_config("commonlib") then
    return
end

add_repositories("SkyrimScripting     https://github.com/SkyrimScripting/Packages.git")
add_repositories("SkyrimScriptingBeta https://github.com/SkyrimScriptingBeta/Packages.git")
add_repositories("MrowrLib            https://github.com/MrowrLib/Packages.git")

includes("xmake/*.lua")

add_requires(get_config("commonlib"))
add_requires("SkyrimScripting.Plugin", { configs = { commonlib = get_config("commonlib") } })

target("Build Papyrus Scripts")
    set_kind("phony")
    compile_papyrus_scripts()
    
skse_plugin({
    name = "Hello Plugin",
    version = "0.0.1",
    author = "Your Name",
    email = "your.name@example.com",
    mod_files = {"Scripts"},
    deps = {"Build Papyrus Scripts"},
    packages = {"SkyrimScripting.Plugin"},
})
