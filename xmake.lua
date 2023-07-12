add_rules("mode.debug", "mode.release")

set_project("key-history")

set_languages("cxx17")

-- config common third-party libs
add_requires("imgui 1.88", {configs = {glfw_opengl3 = true}})
add_packages("imgui")
-- use dsvisual framework
add_includedirs("third-party/DSVisual")
add_files("third-party/DSVisual/dsv-core/dsvisual-core.cpp")
add_includedirs("third-party/DStruct")
add_links("X11")

-- config os platform
if is_host("windows") then
    add_files("platform/win_platform_impl.cpp")
elseif is_host("macosx") then
    add_files("platform/mac_platform_impl.cpp")
else
    add_files("platform/linux_platform_impl.cpp")
end

-- config key-history include path
add_includedirs("include")

target("KeyHistory")
    set_kind("binary")
    add_files("src/*.cpp")

target("KeyHistory-test")
    set_kind("binary")
    add_files("tests/test.cpp")