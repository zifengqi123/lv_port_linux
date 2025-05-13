#ifndef __SW_MENU_H__
#define __SW_MENU_H__


#include "lvgl/lvgl.h"
#include "language/language_def.h"
#include "smartwin_devices.h"
#include "lv_port_indev.h"
#include "sw_define.h"
#include "sw_notice.h"

extern "C" {


typedef void (*menu_item_callback)();

#define ITEMS_PAGE_CNT  6

typedef struct menu_item
{
    SW_STR_define str_def;
    menu_item_callback func;
}menu_item_t;

typedef struct ui_menu
{
    lv_obj_t* parent;
    lv_obj_t* obj;

    lv_obj_t* label_up;
    lv_obj_t* label_down;

    lv_obj_t* item_lines[ITEMS_PAGE_CNT];
    lv_obj_t* item_text[ITEMS_PAGE_CNT];

    int width;
    int hight;

    int x_start;
    int y_start;

    menu_item_t *items;
    int item_cnt;
    int cur_page;
    int max_page;
    int select_item;

    lv_group_t * main_g;
    bool loop;

}ui_menu_t;


void sw_menu_ui_init(lv_obj_t *parent, menu_item_t * items, int cnt);
void sw_menu_ui_del();

void sw_menu_ui_show();
void sw_menu_ui_hide();

void sw_menu_ui_show_pageflag(bool has_up, bool has_down);
void sw_menu_ui_set_select(int idex);



}


#endif