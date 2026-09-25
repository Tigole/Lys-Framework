target("lys-working-thread")
    set_kind("static")
    add_files("source/lys/lys-working-thread/**.cpp")
    add_headerfiles(
        "include/lys/(lys-working-thread/**.hpp)"
        "include/lys/lys-module-working-thread.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-working-thread")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    
for _, testfile in ipairs(os.files("tests/working-thread/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-working-thread")
        add_files(testfile)
        add_tests("lys-working-thread", {timeout = 5})
        set_group("test")
end