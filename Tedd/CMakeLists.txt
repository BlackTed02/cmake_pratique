cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(TEDD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/share/sfml") 
set(NLOHMANN_JSON_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/share/nlohmann_json")

find_package(SFML 2.6.2 COMPONENTS system window graphics audio CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

add_executable(TEDD ${SOURCES})

target_include_directories(TEDD PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_precompile_headers(TEDD PRIVATE include/pch.h)

target_link_libraries(TEDD PRIVATE 
    sfml-system sfml-network sfml-graphics sfml-window sfml-audio   
    nlohmann_json::nlohmann_json)

set_target_properties(TEDD PROPERTIES UNITY_BUILD ON)

set(ENGINE_SOURCES
    src/Component.cpp
    src/ColliderComponent.cpp
    src/FlatBodyComponent.cpp
    src/LightComponent.cpp
    src/RenderComponent.cpp
    src/TransformComponent.cpp
)

set(SFML_SOURCE
    src/Window.cpp
    src/View.cpp
)

set_source_files_properties(&{ENGINE_SOURCES}
    PROPERTIES
    UNITY_GROUP "engine_core"
    UNITY_BUILD_BATCH_SIZE 6
)

set_source_files_properties(&{SFML_SOURCE}
    PROPERTIES
    UNITY_GROUP "sfml_core"
    UNITY_BUILD_BATCH_SIZE 2
)

