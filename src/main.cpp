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

#include "status_ui.h"
#include "menu_ui.h"
#include "notice_ui.h"
#include "input_ui.h"

#include "smartwin_devices.h"
#include "lv_port_indev.h"

#include "lvgl/demos/lv_demos.h"

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


void test_communication_mode(int i)
{
    notice_ui_init(lv_screen_active());
    notice_ui_show("test_communication_mode");
    while (1)
    {
        uint8_t key;
        int ret = _devices->keyboard_get_input(key);

        if(ret == 0) {
            if(key == KEY_CONFIRM) {
                break;
            }
        }

        lv_timer_handler();
        usleep(5 * 1000);
    }
    notice_ui_del();
    // menu_ui_set_select(i);
}

void test_magnetic_stripe_card(int i)
{
    notice_ui_init(lv_screen_active());
    notice_ui_show("اختبار بطاقة الشريط المغناطيسي");
    while (1)
    {
        uint8_t key;
        int ret = _devices->keyboard_get_input(key);

        if(ret == 0) {
            if(key == KEY_CONFIRM) {
                break;
            }
        }

        lv_timer_handler();
        usleep(5 * 1000);
    }
    notice_ui_del();
    // menu_ui_set_select(i);
}

void factory_main_menu()
{
#if LANGUAGE_AL
    char page1[6][64] = {
        "1 . اختبار نموذج الاتصال",
        "2 - إصدار بيتا",
        "3 . اختبار قفل",
        "4 - عمق الاختبار",
        "5 . اختبار",
        "6 . اختبار إعدادات النظام"};

    char page2[6][64] = {
        "1 . اختبار بطاقة الشريط المغناطيسي",
        "2 - الاختبار",
        "3 - اختبار المركز",
        "4 . اختبار بطاقة",
        "5 . اختبار بطاقة البحث",
        "6 . اختبار المسح الضوئي"};
#else
    char page1[6][64] = {
        "1. test_communication_mode",
        "2. test_version",
        "3. test_clock",
        "4. test_beep",
        "5. test_led",
        "6. test_system_reset"};

    char page2[6][64] = {
        "1. test_magnetic_stripe_card",
        "2. test_ic",
        "3. test_icc",
        "4. test_mifare_card",
        "5. test_search_card",
        "6. test_scan"};

#endif

    int cnt_page = 0;

    menu_ui_init(lv_screen_active());

    _devices->keyboard_open();
    _devices->keyboard_set_sound(1);
    _devices->keyboard_set_backlight(1);

    menu_ui_show(page1, 6);
    menu_ui_show_pageflag(false, true);
    while (1)
    {
        uint8_t key;
        int ret = _devices->keyboard_get_input(key);

        if(ret == 0) {
            printf("key : %x\n", key);

            switch (key)
            {
            case KEY_1:
                if(cnt_page == 0) {
                    test_communication_mode(key - 0x30);
                }
                else {
                    test_magnetic_stripe_card(key - 0x30);
                }
                break;
            case KEY_UP:
                if (cnt_page > 0)
                {
                    menu_ui_show(page1, 6);
                    menu_ui_show_pageflag(false, true);
                    cnt_page --;
                }
                break;
            case KEY_DOWN:
                if (cnt_page < 1)
                {
                    menu_ui_show(page2, 6);
                    menu_ui_show_pageflag(true, false);
                    cnt_page ++;
                }
                break;
            default:
                break;
            }

            // if(key == KEY_CONFIRM) {
            //     break;
            // }

        }

        lv_timer_handler();
        usleep(5 * 1000);
    }
}

static void event_cb(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);
    
    lv_obj_t * obj = lv_event_get_target_obj(e);
    if(key == LV_KEY_ESC) {
        lv_obj_send_event(lv_menu_get_main_header_back_button(obj), LV_EVENT_CLICKED, NULL);
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
    lv_indev_set_group(lv_port_getkeypad_indev(), g);

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

    smartwin_gui::status_ui *ui = new smartwin_gui::status_ui(lv_screen_active());

}


void load_ttf_test()
{

    lv_font_t * font = lv_freetype_font_create("/root/arial.ttf",
        LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
        24,
        LV_FREETYPE_FONT_STYLE_NORMAL);

    if(!font) {
        LV_LOG_ERROR("freetype font create failed.");
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "عنوان\nإدخال المعلومات");
    lv_obj_center(label);

    smartwin_gui::status_ui *ui = new smartwin_gui::status_ui(lv_screen_active());
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
    _devices = smartwin::smartwin_devices::getInstance();

    /* Initialize LVGL. */
    lv_init();

    /* Initialize display*/
    lv_display_t * dsp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(dsp, "/dev/fb0");

    /* Initialize input*/
    lv_port_indev_init();

    
    /*Create a Demo*/
    // lv_demo_widgets();
    // lv_demo_widgets_start_slideshow();


    // load_ttf_test();

    lv_example_menu_1();


#if 0
    factory_main_menu();

#if LANGUAGE_AL
    char items[6][64] = {
        "البند 1",
        "البند 2",
        "البند 3",
        "البند 4",
        "البند 5",
        "البند 6"};
#else
    char items[6][64] = {
        "1. Item 1",
        "2. Item 2",
        "3. Item 3",
        "4. Item 1",
        "5. Item 2",
        "6. Item 3"};
#endif

    menu_ui_init(lv_screen_active());

    _devices->keyboard_open();
    _devices->keyboard_set_sound(1);
    _devices->keyboard_set_backlight(1);

    menu_ui_show(items, 6);
    menu_ui_show_pageflag(true, true);
    while (1)
    {
        uint8_t key;
        int ret = _devices->keyboard_get_input(key);

        if(ret == 0) {
            printf("key : %x\n", key);
            if(key >= KEY_1 && key <= KEY_6) {
                menu_ui_set_select(key - 0x30);
            }

            // if(key == KEY_CONFIRM) {
            //     break;
            // }
        }
        lv_timer_handler();
        usleep(5 * 1000);

    }
    _devices->keyboard_set_sound(0);
    _devices->keyboard_set_backlight(0);

    menu_ui_hide();
    menu_ui_del();

    input_ui_init(lv_screen_active());

#if LANGUAGE_AL

    input_ui_show("عنوان", "إدخال المعلومات");
#else
    input_ui_show("DO input:", "input something");
#endif
    input_ui_del();

    notice_ui_init(lv_screen_active());
#if LANGUAGE_AL

    notice_ui_show("عنوان\nإدخال المعلومات");
#else
    notice_ui_show("notice something");
#endif

#endif

    while (true)
    {
        lv_timer_handler();
        usleep(5 * 1000);

    }

    return 0;
}
