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
#include "lvgl/demos/lv_demos.h"

#include "driver_backends.h"
#include "simulator_util.h"
#include "simulator_settings.h"

#include "status_ui.h"
#include "menu_ui.h"
#include "notice_ui.h"
#include "input_ui.h"

#include "smartwin_devices.h"

/* Internal functions */
static void configure_simulator(int argc, char **argv);
static void print_lvgl_version(void);
static void print_usage(void);

/* contains the name of the selected backend if user
 * has specified one on the command line */
static char *selected_backend;

/* Global simulator settings, defined in lv_linux_backend.c */
extern simulator_settings_t settings;


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

/**
 * @brief Print usage information
 */
static void print_usage(void)
{
    fprintf(stdout, "\nlvglsim [-V] [-B] [-b backend_name] [-W window_width] [-H window_height]\n\n");
    fprintf(stdout, "-V print LVGL version\n");
    fprintf(stdout, "-B list supported backends\n");
}

/**
 * @brief Configure simulator
 * @description process arguments recieved by the program to select
 * appropriate options
 * @param argc the count of arguments in argv
 * @param argv The arguments
 */
static void configure_simulator(int argc, char **argv)
{
    int opt = 0;
    char *backend_name;

    selected_backend = NULL;
    driver_backends_register();

    /* Default values */
    settings.window_width = atoi(getenv("LV_SIM_WINDOW_WIDTH") ? : "800");
    settings.window_height = atoi(getenv("LV_SIM_WINDOW_HEIGHT") ? : "480");

    /* Parse the command-line options. */
    while ((opt = getopt (argc, argv, "b:fmW:H:BVh")) != -1) {
        switch (opt) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        case 'V':
            print_lvgl_version();
            exit(EXIT_SUCCESS);
            break;
        case 'B':
            driver_backends_print_supported();
            exit(EXIT_SUCCESS);
            break;
        case 'b':
            if (driver_backends_is_supported(optarg) == 0) {
                die("error no such backend: %s\n", optarg);
            }
            selected_backend = strdup(optarg);
            break;
        case 'W':
            settings.window_width = atoi(optarg);
            break;
        case 'H':
            settings.window_height = atoi(optarg);
            break;
        case ':':
            print_usage();
            die("Option -%c requires an argument.\n", optopt);
            break;
        case '?':
            print_usage();
            die("Unknown option -%c.\n", optopt);
        }
    }
}

smartwin::smartwin_devices* _devices = smartwin::smartwin_devices::getInstance();

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

/**
 * @brief entry point
 * @description start a demo
 * @param argc the count of arguments in argv
 * @param argv The arguments
 */
int main(int argc, char **argv)
{

    configure_simulator(argc, argv);

    /* Initialize LVGL. */
    lv_init();

    /* Initialize the configured backend */
    if (driver_backends_init_backend(selected_backend) == -1) {
        die("Failed to initialize display backend");
    }

    /* Enable for EVDEV support */
#if LV_USE_EVDEV
    if (driver_backends_init_backend("EVDEV") == -1) {
        die("Failed to initialize evdev");
    }
#endif

    /*Create a Demo*/
    // lv_demo_widgets();
    // lv_demo_widgets_start_slideshow();


    smartwin_gui::status_ui *ui = new smartwin_gui::status_ui(lv_screen_active());

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


    /* Enter the run loop of the selected backend */
    driver_backends_run_loop();

    return 0;
}
