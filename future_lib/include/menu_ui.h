#ifndef MENU_UI_H
#define MENU_UI_H

#include "lvgl/lvgl.h"
#include "config_gui.h"


extern "C" {

#define MENU_ITEMS_CNT  6

typedef struct menu_item
{
    lv_obj_t* item_lines;
    lv_obj_t* item_text;
    char str_text[64];
    bool is_selected;
}menu_item_t;

typedef struct ui_menu
{
    lv_obj_t* parent;
    lv_obj_t* obj;

    menu_item_t items[MENU_ITEMS_CNT];

    lv_obj_t* label_up;
    lv_obj_t* label_down;

    int width;
    int hight;

    int x_start;
    int y_start;

}ui_menu_t;


void menu_ui_init(lv_obj_t *parent);
void menu_ui_del();

void menu_ui_show(char items[6][64], int cnt);
void menu_ui_hide();

void menu_ui_show_pageflag(bool has_up, bool has_down);

void menu_ui_set_select(int idex);



}

#endif
