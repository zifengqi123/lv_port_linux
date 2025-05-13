cmake_minimum_required(VERSION 3.10)
project(lvgl)


set(CONF_PATH "${PROJECT_SOURCE_DIR}/lv_conf.h")


# Uncomment if the program needs debugging
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

set(CMAKE_C_STANDARD 99) # LVGL officially supports C99 and above
set(CMAKE_CXX_STANDARD 17) #C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


foreach(arg ${PKG_CONFIG_LIB})
    string(APPEND LVGL_PKG_CONFIG_EXT_LIB " -l${arg}")
endforeach()

file(GLOB LV_LINUX_SRC 
    src/input_dev/lv_port_indev.cpp
    src/sw_status_bar/sw_status_ui.cpp
    src/factory_test/language/language_def.cpp
    src/factory_test/sw_ui/sw_menu.cpp
    src/factory_test/sw_ui/sw_notice.cpp
    src/factory_test/test_main.cpp
    )

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/src/input_dev/
    ${PROJECT_SOURCE_DIR}/../../smartwin_devices/include/
    ${PROJECT_SOURCE_DIR}/src/sw_status_bar/
    ${PROJECT_SOURCE_DIR}/src/factory_test/
    ${PROJECT_SOURCE_DIR}/src/factory_test/language/
    ${PROJECT_SOURCE_DIR}/src/factory_test/sw_ui/
    
    )

add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${PKG_CONFIG_INC})

add_executable(sw_demo src/main.cpp ${LV_LINUX_SRC})
target_link_libraries(sw_demo lvgl lvgl::examples lvgl::demos lvgl::thorvg m pthread ${PKG_CONFIG_LIB}
    ${PROJECT_SOURCE_DIR}/../../smartwin_devices/build/lib/libsmartwin_devices.so
    )

