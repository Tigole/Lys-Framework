
target("lys-application-states")
    set_kind("static")
    add_files("source/lys/lys-application-states/**.cpp")
    add_headerfiles("include/lys/lys-application-states/**.hpp", {public = true})
    add_headerfiles("include/lys/lys-module-application-states.hpp", {public = true})
    add_headerfiles("include/lys/lys-config.hpp", {public = true})
    add_includedirs("include/lys/lys-application-states")
    add_includedirs("include/lys/", {public = true})
    add_deps("lys-working-thread")
    add_defines("LYS_BUILD_STATIC", {public = true})
    
for _, testfile in ipairs(os.files("tests/application-states/**.cpp")) do
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-application-states")
        add_files(testfile)
        add_tests("lys-application-states", {timeout = 5})
        set_group("test")
end

target("examples")
    set_kind("binary")
    add_deps("lys-application-states")
    add_files("examples/application-states/**.cpp")