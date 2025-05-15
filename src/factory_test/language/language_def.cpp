#include "language_def.h"


static SW_Language current_language = LANG_DEFAULT;
static SW_Language font_language = LANG_DEFAULT;
static lv_font_t *sw_font[SW_FONT_MAX] = {NULL};
static lv_style_t sw_style[SW_FONT_MAX];


lv_font_t * load_freetype_font(uint32_t size) 
{
    lv_font_t* font = NULL;
    font_language = current_language;

    //TODO add more
    if (font_language == LANG_ZH) {
        font = lv_freetype_font_create("/user_data/sw_demo/simsun.ttf",
            LV_FREETYPE_FONT_RENDER_MODE_BITMAP, size, LV_FREETYPE_FONT_STYLE_NORMAL);
    }
    else if (font_language == LANG_AR) {  
        font = lv_freetype_font_create("/user_data/sw_demo/arial.ttf",
            LV_FREETYPE_FONT_RENDER_MODE_BITMAP, size, LV_FREETYPE_FONT_STYLE_NORMAL);
    } else {
        font = lv_freetype_font_create("/user_data/sw_demo/arial.ttf",
            LV_FREETYPE_FONT_RENDER_MODE_BITMAP, size, LV_FREETYPE_FONT_STYLE_NORMAL);
    }

    if (!font) {
        LV_LOG_ERROR("freetype font create failed.");
    }

    LV_LOG_WARN("get_freetype_font lv_freetype_font_create %d. size: %d\n", font_language, size);
    return font;
}


void set_language(SW_Language lang) {
    if (lang >= 0 && lang < LANG_MAX) {
        current_language = lang;

        if(sw_font[SW_FONT_12]) {
            lv_freetype_font_delete(sw_font[SW_FONT_12]);
        }
        if(sw_font[SW_FONT_16]) {
            lv_freetype_font_delete(sw_font[SW_FONT_16]);
        }
        if(sw_font[SW_FONT_20]) {
            lv_freetype_font_delete(sw_font[SW_FONT_20]);
        }
        if(sw_font[SW_FONT_24]) {
            lv_freetype_font_delete(sw_font[SW_FONT_24]);
        }
        
        sw_font[SW_FONT_12] = load_freetype_font(12);
        sw_font[SW_FONT_16] = load_freetype_font(16);
        sw_font[SW_FONT_20] = load_freetype_font(20);
        sw_font[SW_FONT_24] = load_freetype_font(24);

        lv_style_init(&sw_style[SW_FONT_12]);
        lv_style_set_text_font(&sw_style[SW_FONT_12], sw_font[SW_FONT_12]);

        lv_style_init(&sw_style[SW_FONT_16]);
        lv_style_set_text_font(&sw_style[SW_FONT_16], sw_font[SW_FONT_16]);

        lv_style_init(&sw_style[SW_FONT_20]);
        lv_style_set_text_font(&sw_style[SW_FONT_20], sw_font[SW_FONT_20]);

        lv_style_init(&sw_style[SW_FONT_24]);
        lv_style_set_text_font(&sw_style[SW_FONT_24], sw_font[SW_FONT_24]);
    }
}

SW_Language get_curr_language()
{
    return current_language;
}

lv_font_t* get_sw_font_bysize(SW_FONT_SIZE size) 
{
    if (size >= 0 && size < SW_FONT_MAX) {
        return sw_font[size];
    }
    return NULL;
}

lv_style_t* get_sw_style_bysize(SW_FONT_SIZE size) 
{
    if (size >= 0 && size < SW_FONT_MAX) {
        return &sw_style[size];
    }
    return NULL;
}

const char * get_sw_strings_bydefine(SW_STR_define def) 
{
    if (def >= 0 && def < STR_MAX) {
        return SW_STRINGS[def][current_language];
    }
    return "str not define";
}