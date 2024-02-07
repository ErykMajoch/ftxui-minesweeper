cmake_minimum_required (VERSION 3.11)

find_package(ftxui 5 QUIET)
if (NOT ${ftxui_FOUND})
    include(FetchContent)
    set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    FetchContent_Declare(ftxui
            GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
            GIT_TAG main # Important: Specify a version or a commit hash here.
    )
    FetchContent_MakeAvailable(ftxui)
endif()

project(Minesweeper LANGUAGES CXX VERSION 1.0.0)
add_executable(Minesweeper source/main.cpp)
target_link_libraries(Minesweeper
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component # Not needed for this example.
)

