#ifndef SW_STATUS_UI_H_
#define SW_STATUS_UI_H_


#include "lvgl/lvgl.h"
#include "time.h"
#include <stdio.h>
#include <stdint.h>
#include <functional>
#include <unistd.h>
#include <pthread.h>
#include "language/language_def.h"

#ifndef STATUS_VIEW_WIDTH
#define STATUS_VIEW_WIDTH    320
#endif

#ifndef STATUS_BAR_HIGHT
#define STATUS_BAR_HIGHT     20
#endif

#ifndef STATUS_BAR_BG_COLOR
#define STATUS_BAR_BG_COLOR  0x0000FF
#endif

#ifndef STATUS_VIEW_HIGHT
#define STATUS_VIEW_HIGHT       (24)
#endif

typedef struct status_bar
{
    lv_obj_t* parent;
    lv_obj_t* obj;
}status_bar_t;

typedef struct battery_bar
{
    lv_obj_t* parent;
    lv_obj_t* outline;
    lv_obj_t* battflag;
    lv_obj_t* pad;
    lv_obj_t* label;
    lv_obj_t* text;
    lv_obj_t* charge;

    int width;
    int hight;

    int x;
    int y;
}battery_bar_t;

typedef struct print_bar
{
    lv_obj_t* parent;
    lv_obj_t* label_0;
    lv_obj_t* label_1;
    lv_obj_t* label_2;
    lv_obj_t* text;

    int width;
    int hight;

    int x;
    int y;
}print_bar_t;

typedef struct signal_bar
{
    lv_obj_t* parent;
    lv_obj_t* label_0;
    lv_obj_t* label_1;
    lv_obj_t* label_2;
    lv_obj_t* label_3;
    lv_obj_t* label_4;
    lv_obj_t* lable_txt;

    int width;
    int hight;

    int x;
    int y;
}signal_bar_t;

typedef struct time_bar
{
    lv_obj_t* parent;
    lv_obj_t* obj;
    lv_obj_t* label;

    int width;
    int hight;

    int x;
    int y;
}time_bar_t;

typedef struct wifi_bar
{
    lv_obj_t* parent;
    lv_obj_t* obj;
    lv_obj_t* label;

    int width;
    int hight;

    int x;
    int y;
}wifi_bar_t;


typedef struct status_info
{
    float battery_per;
    bool is_battery_charge;
    bool is_print_err;
    int signal_level;
    char* signal_type;
    bool has_wifi;
    bool is_wifi_connect;
    time_t time_stamp;
}status_info_t;

typedef void (*fun_getinfo_callback)(status_info_t * status_info);

void status_ui_init(lv_obj_t *parent, fun_getinfo_callback callback);
void status_ui_show();
void status_ui_hide();

void status_ui_del();


#endif
