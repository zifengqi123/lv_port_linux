#ifndef __language_def__sw_
#define __language_def__sw_

#include "lvgl/lvgl.h"

typedef enum {
    LANG_ZH,
    LANG_EN,
    LANG_AR,
    LANG_MAX
} SW_Language;

typedef enum {
    SW_FONT_12,
    SW_FONT_16,
    SW_FONT_20,
    SW_FONT_24,
    SW_FONT_MAX
    
} SW_FONT_SIZE;

typedef enum {
    STR_test_version = 0,
    STR_test_beep,
    STR_test_keyboard,
    STR_test_mag_card,
    STR_test_ic,
    STR_test_rf,
    STR_test_mifare_card,
    STR_test_search_card,
    STR_test_scan,
    STR_test_printer,
    STR_test_keypad,
    STR_test_tp,

    STR_MAX
} SW_STR_define;
//...

#define LANG_DEFAULT LANG_EN

static const char *SW_STRINGS[][LANG_MAX] = {
    {"版本测试",        "test_version",          " اختبار الإصدار "},           // 0
    {"蜂鸣器测试",      "test_beep",            " اختبار الجرس "},              // 1   
    {"按键测试",        "test_keyboard",        " مفتاح اختبار "},
    {"磁卡测试",        "test_mag_card",        " اختبار البطاقة الممغنطة "},
    {"IC卡测试",        "test_ic",              " جيم بطاقة اختبار "},
    {"非接卡测试",      "test_rf",              " عدم التقاط بطاقة اختبار "},
    {"存储卡测试",      "test_mifare_card",     " بطاقة الذاكرة اختبار "},
    {"寻卡测试",        "test_search_card",     " البحث عن بطاقة اختبار "},
    {"扫码测试",        "test_scan",            " مسح رمز اختبار "},
    {"打印机测试",      "test_printer",         " اختبار الطابعة "},
    {"密码键盘测试",    "test_keypad",          " كلمة السر لوحة المفاتيح اختبار "},
    {"触屏测试",        "test_tp",              " اختبار اللمس "},


    {"", "", ""}        //MAX
};



void set_language(SW_Language lang);
SW_Language get_curr_language();

lv_font_t* get_sw_font_bysize(SW_FONT_SIZE size);
lv_style_t* get_sw_style_bysize(SW_FONT_SIZE size);

const char * get_sw_strings_bydefine(SW_STR_define def);


#endif
