cmake_minimum_required (VERSION 3.11)

find_package(ftxui 5 QUIET)
if (NOT ${ftxui_FOUND})
    include(FetchContent)
    set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    FetchContent_Declare(ftxui
            GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
            GIT_TAG main
    )
    FetchContent_MakeAvailable(ftxui)
endif()

project(Minesweeper LANGUAGES CXX VERSION 1.0.0)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

add_executable(Minesweeper ${SOURCES} ${HEADERS})

target_include_directories(Minesweeper
        PRIVATE include
)

set_target_properties(Minesweeper PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_link_libraries(Minesweeper
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)

