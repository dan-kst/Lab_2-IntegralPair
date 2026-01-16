find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

add_executable(gui_app 
    main_gui.cpp 
    MainWindow.cpp
)

target_include_directories(gui_app PRIVATE 
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(gui_app PRIVATE ${GTKMM_CFLAGS_OTHER})

target_link_libraries(gui_app 
    PRIVATE 
    core_logic 
    database_logic 
    ${GTKMM_LIBRARIES}
)
