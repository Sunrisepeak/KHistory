--includes("third-party/DSViusal/xmake.lua")

set_languages("c++17")

-- libs
add_requires("imgui 1.88", {configs = {glfw_opengl3 = true}})

add_includedirs(
    "include",
    "third-party/DSVisual",
    "third-party/DStruct"
)

add_packages("imgui")

add_files("third-party/DSVisual/dsv-core/dsvisual-core.cpp")

add_links("X11")

add_files("platform/linux_platform_impl.cpp")

target("KeyHistory-test")
    set_kind("binary")
    add_cxxflags("-g")
    add_files("tests/test.cpp")

target("KeyHistory")
    set_kind("binary")
    add_cxxflags("-g")
    add_files("src/*.cpp")