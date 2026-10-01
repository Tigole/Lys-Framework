target("lys-particle-system")
    set_kind("headeronly")
    --add_files("source/lys/lys-particle-system/**.cpp")
    add_headerfiles(
        "include/lys/(lys-particle-system/**.hpp)",
        "include/lys/lys-module-particle-system.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-particle-system")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    
for _, testfile in ipairs(os.files("tests/particle-system/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_files(testfile)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-particle-system")
        add_tests("lys-particle-system", {timeout = 5})
        set_group("test")
end