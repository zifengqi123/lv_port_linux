/*******************************************************************
 *
 * main.c - LVGL simulator for GNU/Linux
 *
 * Based on the original file from the repository
 *
 * @note eventually this file won't contain a main function and will
 * become a library supporting all major operating systems
 *
 * To see how each driver is initialized check the
 * 'src/lib/display_backends' directory
 *
 * - Clean up
 * - Support for multiple backends at once
 *   2025 EDGEMTech Ltd.
 *
 * Author: EDGEMTech Ltd, Erik Tagirov (erik.tagirov@edgemtech.ch)
 *
 ******************************************************************/
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lvgl/lvgl.h"

#include "smartwin_devices.h"
#include "lv_port_indev.h"

#include "lvgl/demos/lv_demos.h"

#include "test_main.h"

/* Internal functions */
static void print_lvgl_version(void);
static smartwin::smartwin_devices* _devices;

/**
 * @brief Print LVGL version
 */
static void print_lvgl_version(void)
{
    fprintf(stdout, "%d.%d.%d-%s\n",
            LVGL_VERSION_MAJOR,
            LVGL_VERSION_MINOR,
            LVGL_VERSION_PATCH,
            LVGL_VERSION_INFO);
}

void memory_print(void)
{
    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
                mon.used_pct,
                mon.frag_pct,
                (int)mon.free_biggest_size);
}

void load_ttf_test();

static void event_cb(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);
    
    lv_obj_t * obj = lv_event_get_target_obj(e);
    if(key == LV_KEY_ESC) {
        lv_obj_send_event(lv_menu_get_main_header_back_button(obj), LV_EVENT_CLICKED, NULL);
    }
    if (key == LV_KEY_ENTER) {
        load_ttf_test();
        status_ui_show();
    }
}

void lv_example_menu_1(void)
{
    /*Create a menu object*/
    lv_group_t * g = lv_group_create();

    lv_obj_t * menu = lv_menu_create(lv_screen_active());
    lv_obj_set_size(menu, 320, 240-24);
    lv_obj_set_pos(menu, 0, 24);
    // lv_obj_center(menu);

    lv_group_add_obj(g, menu);
    lv_indev_set_group(lv_port_get_keypad_indev(), g);

    lv_obj_t * cont;
    lv_obj_t * label;

    /*Create a sub page*/
    lv_obj_t * sub_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(sub_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here");

    /*Create a main page*/
    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Item 1");

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Item 2");

    cont = lv_menu_cont_create(main_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Item 3 (Click me!)");
    lv_menu_set_load_page_event(menu, cont, sub_page);

    lv_obj_add_event_cb(menu, event_cb, LV_EVENT_KEY, NULL);

    lv_menu_set_page(menu, main_page);


}

static void event_cb_1(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);
    
    lv_obj_t * obj = lv_event_get_target_obj(e);
    if(key == LV_KEY_ESC) {
        status_ui_hide();

        lv_example_menu_1();
    }
}

void load_ttf_test()
{

    set_language(LANG_ZH);
    // lv_font_t * font = get_sw_font_bysize(SW_FONT_24);
    
    // lv_font_t * font = lv_freetype_font_create("/root/arial.ttf",
    //     LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
    //     24,
    //     LV_FREETYPE_FONT_STYLE_NORMAL);

    // if(!font) {
    //     LV_LOG_ERROR("freetype font create failed.");
    // }

    /*Create style with the new font*/
    // static lv_style_t style;
    // lv_style_init(&style);
    // lv_style_set_text_font(&style, font);
    // lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, get_sw_style_bysize(SW_FONT_24), 0);
    lv_obj_set_style_base_dir(label, LV_BASE_DIR_AUTO, 0);

    // lv_label_set_text(label, "عنوان\nإدخال المعلومات");
    // lv_label_set_text(label, "abc");
    lv_label_set_text(label, get_sw_strings_bydefine(STR_test_version));

    lv_obj_center(label);

    // lv_group_t * g = lv_group_create();
    // lv_group_add_obj(g, label);
    // lv_indev_set_group(lv_port_get_keypad_indev(), g);
    // lv_obj_add_event_cb(label, event_cb_1, LV_EVENT_KEY, NULL);

    memory_print();

}

static void sw_hal_init()
{
    smartwin::smartwin_devices::getInstance("/dev/ttyS1", 460800);

    lv_group_set_default(lv_group_create());

    /* Initialize display*/
    lv_port_display_init();

    /* Initialize input*/
    lv_port_indev_init();

    lv_indev_t *keypad = lv_port_get_keypad_indev();
    lv_indev_set_display(keypad, lv_port_get_display());
    lv_indev_set_group(keypad, lv_group_get_default());

    lv_indev_t *touchpad = lv_port_get_touchpad_indev();
    lv_indev_set_display(touchpad, lv_port_get_display());
    lv_indev_set_group(touchpad, lv_group_get_default());

}

/**
 * @brief entry point
 * @description start a demo
 * @param argc the count of arguments in argv
 * @param argv The arguments
 */
int main(int argc, char **argv)
{
    print_lvgl_version();
    
    /* Initialize LVGL. */
    lv_init();

    sw_hal_init();

    /*Create a Demo*/
    // lv_demo_widgets();
    // lv_demo_widgets_start_slideshow();

    // load_ttf_test();
    // lv_timer_handler();
    // usleep(1000 * 1000);

    // set_language(LANG_AR);
    // main_page_init(lv_screen_active());

    set_language(LANG_ZH);
    test_menu_ft();


    while (true)
    {
        lv_timer_handler();
        usleep(5 * 1000);

    }

    return 0;
}
