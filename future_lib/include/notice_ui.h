#pragma once

#include "lvgl/lvgl.h"

extern "C" {



typedef struct ui_notice
{
    lv_obj_t* parent;
    lv_obj_t* obj;

    lv_obj_t* label;

    int width;
    int hight;

    int x_start;
    int y_start;

}ui_notice_t;


void notice_ui_init(lv_obj_t *parent);
void notice_ui_del();

void notice_ui_show(const char* msg);


}
