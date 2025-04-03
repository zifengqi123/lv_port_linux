#ifndef __INPUT_UI_H_
#define __INPUT_UI_H_

#include "lvgl/lvgl.h"
#include "config_gui.h"

extern "C" {

typedef struct ui_input
{
    lv_obj_t* parent;
    lv_obj_t* obj;
    lv_obj_t* title;
    lv_obj_t* input;

    int width;
    int hight;

    int x_start;
    int y_start;

}ui_input_t;

void input_ui_init(lv_obj_t *parent);
void input_ui_del();

void input_ui_show(char * title, char* msg);

}




#endif
