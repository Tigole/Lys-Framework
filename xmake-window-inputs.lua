add_requires("sfml")

target("lys-window-inputs-sfml")
    set_kind("static")
    add_headerfiles(
        "include/lys/(lys-window-inputs/**.hpp)",
        "include/lys/lys-module-window-inputs.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-window-inputs")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    add_defines("LYS_CONFIG_BACKEND_SFML", {public = true})
    add_files("source/lys/lys-window-inputs/lys-window-inputs-sfml.cpp")
    add_packages("sfml")

target("lys-window-inputs-raylib")
    set_kind("static")
    add_headerfiles(
        "include/lys/(lys-window-inputs/**.hpp)",
        "include/lys/lys-module-window-inputs.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-window-inputs")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    add_defines("LYS_CONFIG_BACKEND_RAYLIB", {public = true})
    add_files("source/lys/lys-window-inputs/lys-window-inputs-raylib.cpp")
    add_packages("raylib")

target("lys-window-inputs")
    set_kind("static")
    if has_config("backend", "sfml") then
        print("backend sfml")
        add_deps("lys-window-inputs-sfml")
        add_defines("LYS_CONFIG_BACKEND_SFML", {public = true})
    elseif has_config("backend", "raylib") then
        print("backend raylib")
        add_deps("lys-window-inputs-raylib")
        add_defines("LYS_CONFIG_BACKEND_RAYLIB", {public = true})
    else
        set_default(false)
    end
    
for _, testfile in ipairs(os.files("tests/window-inputs/sfml/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_packages("sfml")
        add_deps("lys-window-inputs-sfml")
        add_files(testfile)
        add_tests("lys-window-inputs", {timeout = 5})
        set_group("test")
end
    
--for _, testfile in ipairs(os.files("tests/window-inputs/**.cpp")) do
--    local name = path.basename(testfile)
--    target(name)
--        set_kind("binary")
--        set_default(false)
--        add_packages("gtest", {main = true, gmok = false})
--        add_deps("lys-window-inputs")
--        add_files(testfile)
--        add_tests("lys-window-inputs", {timeout = 5})
--        set_group("test")
--end