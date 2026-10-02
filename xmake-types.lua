target("lys-types")
    set_kind("headeronly")
    --add_files("source/lys/lys-types/**.cpp")
    add_headerfiles(
        "include/lys/(lys-types/**.hpp)",
        "include/lys/(lys-types/**.inl)",
        "include/lys/lys-module-types.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-types")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})

for _, testfile in ipairs(os.files("tests/types/**.cpp")) do 
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_files(testfile)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-types")
        add_tests("lys-types", {timeout = 5})
        set_group("test")
end