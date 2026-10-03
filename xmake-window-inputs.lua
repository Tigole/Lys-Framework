target("lys-window-inputs")
    set_kind("static")
    if has_config("backend-sfml") then
        add_packages("sfml")
        add_files("source/lys/lys-window-inputs/lys-window-input-sfml.cpp")
        add_defines("LYS_OPTION_BACKEND_SFML", {public = true})
    elseif has_config("backend-raylib") then
        add_packages("raylib")
        add_files("source/lys/lys-window-inputs/lys-window-input-raylib.cpp")
        add_defines("LYS_OPTION_BACKEND_RAYLIB", {public = true})
    else
        set_default(false)
    end
    add_headerfiles(
        "include/lys/(lys-window-inputs/**.hpp)",
        "include/lys/lys-module-window-inputs.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-window-inputs")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    
for _, testfile in ipairs(os.files("tests/window-inputs/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-window-inputs")
        add_files(testfile)
        add_tests("lys-window-inputs", {timeout = 5})
        set_group("test")
end