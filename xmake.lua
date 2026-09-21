set_project("Lys-Framework")
set_version("99.99.99")

add_repositories("TigoleRepo https://github.com/Tigole/xmake-repo.git")

add_rules("mode.debug", "mode.release")
set_policy("build.ccache", false)

add_requires("sfml master", { configs = { shared = true }})
add_requires("gtest", "magic_enum", "glm", "fmt")
add_requires("glew", "opengl")
add_requires("clay")
add_requires("tinyxml-boosted")
add_requires("raylib", {configs = { debug = true}})

set_languages("c++20")

target("Lys")
    set_kind("shared")
    add_files("source/Lys/**.cpp")
    remove_files("source/Lys/GUIModule/_Backup/**.cpp")
    remove_files("source/Lys/GUIModule/**.cpp")
    add_defines("LYS_BUILD_DLL")
    add_defines("GLM_ENABLE_EXPERIMENTAL", {public = true})
    add_includedirs("include/", {public = true})
    add_packages("glm", "sfml", "glew", {public = true})
    add_syslinks("opengl32")
    add_packages("tinyxml-boosted", { public = true })

target("exemple")
    set_kind("binary")
    add_files("examples/**.cpp")
    add_deps("Lys")