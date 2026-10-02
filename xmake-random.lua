target("lys-random")
    set_kind("static")
    add_files("source/lys/lys-random/**.cpp")
    add_headerfiles(
        "include/lys/(lys-random/**.hpp)",
        "include/lys/lys-module-random.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-random")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    
for _, testfile in ipairs(os.files("tests/random/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-random")
        add_files(testfile)
        add_tests("lys-random", {timeout = 5})
        set_group("test")
end