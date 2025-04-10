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

file(GLOB LV_LINUX_SRC src/lib/*.c)
set(LV_LINUX_INC src/lib)

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/../../smartwin_devices/include
    ${PROJECT_SOURCE_DIR}/../../smartwin_gui/include
    )

add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/input_dev ${PKG_CONFIG_INC})

add_executable(sw_demo src/main.cpp ${LV_LINUX_SRC} src/input_dev/lv_port_indev.cpp)
target_link_libraries(sw_demo lvgl lvgl::examples lvgl::demos lvgl::thorvg m pthread ${PKG_CONFIG_LIB}
    ${PROJECT_SOURCE_DIR}/../../smartwin_devices/build/lib/libsmartwin_devices.so
    ${PROJECT_SOURCE_DIR}/../../smartwin_gui/build/lib/libsmartwin_gui.so
    )

