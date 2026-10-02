target("lys-log")
    set_kind("static")
    add_files("source/lys/lys-log/**.cpp")
    add_headerfiles(
        "include/lys/(lys-log/**.hpp)", 
        "include/lys/lys-module-log.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-log")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    add_deps("lys-working-thread")
    
for _, testfile in ipairs(os.files("tests/log/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-log")
        add_files(testfile)
        add_tests("lys-log", {timeout = 5})
        set_group("test")
end

target("examples")
    set_kind("binary")
    add_deps("lys-log")
    add_files("examples/log/**.cpp")