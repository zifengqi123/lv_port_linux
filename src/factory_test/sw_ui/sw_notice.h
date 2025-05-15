#pragma once

#include "lvgl/lvgl.h"
#include "language/language_def.h"
#include "smartwin_devices.h"
#include "lv_port_indev.h"
#include "sw_define.h"


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

    lv_group_t * main_g;
    bool is_del;
    bool is_end;

}ui_notice_t;


void sw_notice_ui_init(lv_obj_t *parent);
void sw_notice_ui_del();

void sw_notice_ui_show(const char* msg);
void sw_notice_ui_end();

bool sw_notice_is_del();


}
