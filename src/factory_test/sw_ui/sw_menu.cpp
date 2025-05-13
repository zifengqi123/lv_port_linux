#include "sw_menu.h"
#include <stdio.h>

static ui_menu_t _menu_ui;
static SW_Language sw_lang = LANG_DEFAULT;
static pthread_t fun_thread_;
static pthread_mutex_t _menu_mutex;

void* func_callback(void* arg)
{
    _menu_ui.items[_menu_ui.select_item].func();
}

static void event_cb_key(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);

    lv_obj_t * obj = lv_event_get_target_obj(e);
    sw_lang = get_curr_language();

    if(key == KEY_MENU) {
        if(sw_lang == LANG_ZH) {
            sw_lang = LANG_EN;
        }
        else if(sw_lang == LANG_EN){
            sw_lang = LANG_AR;
        }
        else {
            sw_lang = LANG_ZH;
        }
        set_language(sw_lang);
        sw_menu_ui_show();
    }
    else if(key >= KEY_1 && key <= KEY_6) {
        int selcet = (key - 0x30) - 1;
        if(selcet + ITEMS_PAGE_CNT * _menu_ui.cur_page < _menu_ui.item_cnt) {
            sw_menu_ui_set_select(selcet);

            if(_menu_ui.items[_menu_ui.select_item].str_def != STR_test_tp) {
                sw_notice_ui_init(_menu_ui.parent);
            }
            
            pthread_create(&fun_thread_, NULL, &func_callback, NULL);
            
            LV_LOG_USER("_menu_ui.items call func..");
        }
    }
    else if(key == LV_KEY_UP) {
        if(_menu_ui.cur_page > 0) {
            _menu_ui.cur_page--;
            sw_menu_ui_show();
        }
    }
    else if(key == LV_KEY_DOWN) {
        if(_menu_ui.cur_page < _menu_ui.max_page - 1) {
            _menu_ui.cur_page++;
            sw_menu_ui_show();
        }
    }
    else if(key == LV_KEY_ESC) {
        LV_LOG_USER("key LV_KEY_ESC. to del.");
        if(_menu_ui.items[_menu_ui.select_item].str_def != STR_test_tp) {
            sw_notice_ui_del();
            sw_menu_ui_show();
        }
    }
    
}

void sw_menu_ui_init(lv_obj_t *parent, menu_item_t * items, int cnt)
{
    if(_menu_ui.obj != NULL) {
        sw_menu_ui_del();
    }

    pthread_mutex_init(&_menu_mutex, NULL);
    pthread_mutex_lock(&_menu_mutex);

    _menu_ui.parent = parent;
    _menu_ui.item_cnt = cnt;
    _menu_ui.items = items;

    if(cnt % ITEMS_PAGE_CNT == 0) {
        _menu_ui.max_page = cnt / ITEMS_PAGE_CNT;
    }
    else {
        _menu_ui.max_page = cnt / ITEMS_PAGE_CNT + 1;
    }
    

    _menu_ui.x_start = 0;
    _menu_ui.y_start = STATUS_VIEW_HIGHT;
    _menu_ui.width = MENU_VIEW_WIDTH;
    _menu_ui.hight = MENU_VIEW_HEIGHT;

    _menu_ui.obj = lv_obj_create(_menu_ui.parent);
    lv_obj_set_size(_menu_ui.obj, _menu_ui.width, _menu_ui.hight);
    lv_obj_set_pos(_menu_ui.obj, _menu_ui.x_start, _menu_ui.y_start);

    lv_obj_set_style_radius(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(_menu_ui.obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(_menu_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(_menu_ui.obj, lv_color_hex(MENU_ITEM_UNSELECT_BG_COLOR), LV_PART_MAIN|LV_STATE_DEFAULT);


    for (int i = 0; i < ITEMS_PAGE_CNT; i++)
    {
        _menu_ui.item_lines[i] = lv_obj_create(_menu_ui.obj);
        lv_obj_set_size(_menu_ui.item_lines[i], _menu_ui.width, MENU_ITEM_TEXT_HEIGHT);
        lv_obj_set_pos(_menu_ui.item_lines[i], _menu_ui.x_start, i*MENU_ITEM_TEXT_HEIGHT);
        lv_obj_set_scrollbar_mode(_menu_ui.item_lines[i], LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_style_radius(_menu_ui.item_lines[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(_menu_ui.item_lines[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);

        _menu_ui.item_text[i] = lv_label_create(_menu_ui.item_lines[i]);
        lv_obj_set_size(_menu_ui.item_text[i], _menu_ui.width - MENU_ITEM_TEXT_SIZE, MENU_ITEM_TEXT_SIZE);
        lv_obj_align(_menu_ui.item_text[i], LV_ALIGN_CENTER, 0, 0);

        lv_obj_set_style_base_dir(_menu_ui.item_text[i], LV_BASE_DIR_AUTO, 0);
        lv_obj_add_style(_menu_ui.item_text[i], get_sw_style_bysize(SW_FONT_24), 0);
        lv_obj_set_scrollbar_mode(_menu_ui.item_text[i], LV_SCROLLBAR_MODE_OFF);

    }

    _menu_ui.label_up = lv_label_create(_menu_ui.obj);
    lv_obj_set_size(_menu_ui.label_up, MENU_ITEM_TEXT_SIZE, MENU_ITEM_TEXT_SIZE);
    lv_label_set_text(_menu_ui.label_up, LV_SYMBOL_UP);

    _menu_ui.label_down = lv_label_create(_menu_ui.obj);
    lv_obj_set_size(_menu_ui.label_down, MENU_ITEM_TEXT_SIZE, MENU_ITEM_TEXT_SIZE);
    lv_label_set_text(_menu_ui.label_down, LV_SYMBOL_DOWN);

    if(get_curr_language() == LANG_AR) {
        lv_obj_align(_menu_ui.label_up, LV_ALIGN_TOP_LEFT, 10, 0);
        lv_obj_align(_menu_ui.label_down, LV_ALIGN_BOTTOM_LEFT, 10, 0);
    }
    else {
        lv_obj_align(_menu_ui.label_up, LV_ALIGN_TOP_RIGHT, -10, 0);
        lv_obj_align(_menu_ui.label_down, LV_ALIGN_BOTTOM_RIGHT, -10, 0);
    }

    _menu_ui.main_g = lv_group_create();
    lv_group_add_obj(_menu_ui.main_g, _menu_ui.obj);
    lv_indev_set_group(lv_port_get_keypad_indev(), _menu_ui.main_g);
    lv_obj_add_event_cb(_menu_ui.obj, event_cb_key, LV_EVENT_KEY, NULL);

    _menu_ui.loop = true;
    pthread_mutex_unlock(&_menu_mutex);

    sw_menu_ui_show();

    // while (_menu_ui.loop)
    // {
    //     lv_timer_handler();
    //     usleep(5 * 1000);
    // }
}

void sw_menu_ui_del()
{
    _menu_ui.loop = false;
    sw_menu_ui_hide();

    for (int i = 0; i < ITEMS_PAGE_CNT; i++)
    {
        if(_menu_ui.item_lines[i]) lv_obj_del(_menu_ui.item_lines[i]);
        if(_menu_ui.item_text[i]) lv_obj_del(_menu_ui.item_text[i]);

    }

    if(_menu_ui.label_up) lv_obj_del(_menu_ui.label_up);
    if(_menu_ui.label_down) lv_obj_del(_menu_ui.label_down);

    if(_menu_ui.obj) {
        lv_obj_del(_menu_ui.obj);
        _menu_ui.obj = NULL;
    }

}


void sw_menu_ui_show_pageflag(bool has_up, bool has_down)
{
    if (has_up)
    {
        lv_obj_clear_flag(_menu_ui.label_up, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_obj_add_flag(_menu_ui.label_up, LV_OBJ_FLAG_HIDDEN);
    }

    if (has_down)
    {
        lv_obj_clear_flag(_menu_ui.label_down, LV_OBJ_FLAG_HIDDEN);
    }
    else {
        lv_obj_add_flag(_menu_ui.label_down, LV_OBJ_FLAG_HIDDEN);
    }
}

void sw_menu_ui_show()
{
    char tmp[64] = {0};
    for (size_t i = 0; i < ITEMS_PAGE_CNT; i++)
    {
        if(ITEMS_PAGE_CNT*_menu_ui.cur_page + i < _menu_ui.item_cnt) {

            sprintf(tmp, "%d. %s", i+1, get_sw_strings_bydefine(_menu_ui.items[ITEMS_PAGE_CNT*_menu_ui.cur_page + i].str_def));

            pthread_mutex_lock(&_menu_mutex);
            lv_label_set_text(_menu_ui.item_text[i], tmp);
            pthread_mutex_unlock(&_menu_mutex);

            lv_obj_clear_flag(_menu_ui.item_lines[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(_menu_ui.item_text[i], LV_OBJ_FLAG_HIDDEN);
        

            if (ITEMS_PAGE_CNT*_menu_ui.cur_page + i == _menu_ui.select_item)
            {
                lv_obj_set_style_bg_color(_menu_ui.item_lines[i], lv_color_hex(MENU_ITEM_SELECT_BG_COLOR), LV_PART_MAIN|LV_STATE_DEFAULT);
            }
            else {
                lv_obj_set_style_bg_color(_menu_ui.item_lines[i], lv_color_hex(MENU_ITEM_UNSELECT_BG_COLOR), LV_PART_MAIN|LV_STATE_DEFAULT);
            }
        }
        else {
            lv_obj_add_flag(_menu_ui.item_lines[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(_menu_ui.item_text[i], LV_OBJ_FLAG_HIDDEN);
        }

    }

    bool has_up = false;
    bool has_down = false;
    if (_menu_ui.cur_page > 0)
    {
        has_up = true;
    }
    
    if(_menu_ui.cur_page < _menu_ui.max_page - 1){
        has_down = true;
    }
    sw_menu_ui_show_pageflag(has_up, has_down);
    
}

void sw_menu_ui_hide()
{
    for (int i = 0; i < ITEMS_PAGE_CNT; i++)
    {
        lv_obj_add_flag(_menu_ui.item_lines[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(_menu_ui.item_text[i], LV_OBJ_FLAG_HIDDEN);
    }
    lv_obj_add_flag(_menu_ui.label_up, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(_menu_ui.label_down, LV_OBJ_FLAG_HIDDEN);
}

void sw_menu_ui_set_select(int idex)
{
    _menu_ui.select_item = ITEMS_PAGE_CNT * _menu_ui.cur_page + idex;
}
