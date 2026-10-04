target("lys-tiled-map-loading")
    set_kind("headeronly")
    --add_files("source/lys/lys-tiled-map-loading/**.cpp")
    add_headerfiles(
        "include/lys/(lys-tiled-map-loading/**.hpp)",
        "include/lys/(lys-tiled-map-loading/**.inl)",
        "include/lys/lys-module-tiled-map-loading.hpp",
        "include/lys/lys-config.hpp", 
        {public = true})
    add_includedirs("include/lys/lys-tiled-map-loading")
    add_includedirs("include/lys/", {public = true})
    add_defines("LYS_BUILD_STATIC", {public = true})
    add_packages("tinyxml-boosted", {public = true})
    add_deps("lys-types")
    add_deps("lys-log")

for _, testfile in ipairs(os.files("tests/tiled-map-loading/**.cpp")) do 
    local name = path.basename(testfile)
    target(name)
        set_kind("binary")
        set_default(false)
        add_files(testfile)
        add_packages("gtest", {main = true, gmok = false})
        add_deps("lys-tiled-map-loading")
        add_tests("lys-tiled-map-loading", {timeout = 5})
        set_group("test")
end