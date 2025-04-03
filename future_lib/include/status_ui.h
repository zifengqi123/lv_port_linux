#pragma once

#include "lvgl/lvgl.h"
#include "time.h"
#include <stdio.h>
#include <stdint.h>
#include <functional>
#include <unistd.h>
#include <string>

using namespace std;

namespace future_gui {

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
    string signal_type;
    bool has_wifi;
    bool is_wifi_connect;
    time_t time_stamp;
}status_info_t;

#define STATUS_VIEW_WIDTH    320
#define STATUS_VIEW_HIGHT    24
#define STATUS_BAR_HIGHT     20

#define STATUS_BAR_BG_COLOR  0x0000FF

class status_ui {

public:
    status_ui(lv_obj_t *parent);
    ~status_ui();

public:

    void battery_bar_addflag();
    void battery_bar_addcharge();
    void battery_bar_init(lv_obj_t *parent, int x, int y, int width, int hight);
    void battery_bar_del();
    // 电量百分比 0.00 ~ 1.00
    void battery_bar_show(float per, bool is_charge);

    void print_bar_init(lv_obj_t *parent, int x, int y, int width, int hight);
    void print_bar_del();
    void print_bar_show(bool is_err);

    void signal_bar_init(lv_obj_t *parent, int x, int y, int width, int hight);
    void signal_bar_del();
    //显示信号等级 0 ~ 5
    void signal_bar_show(int level, const char* signal);

    void timebar_init(lv_obj_t *parent, int x, int y, int width, int hight);
    void timebar_del();
    void timebar_show(time_t time_stamp);

    void wifi_bar_init(lv_obj_t *parent, int x, int y, int width, int hight);
    void wifi_bar_del();

    void wifi_bar_show(bool has_wifi, bool is_connect);

    void update_status();

    void set_update_callback(std::function<void(status_info_t & status_info)> callback);

    float t = 0;

private:

    status_info_t _status_info;

    status_bar_t _status_bar;

    battery_bar_t _battery_bar;
    print_bar_t _print_bar;
    signal_bar_t _signal_bar;
    time_bar_t _time_bar;
    wifi_bar_t _wifi_bar;

    pthread_t _update_thread;
    pthread_mutex_t _update_mutex;
    bool _update_flag = false;

    lv_timer_t *_update_timer;

    std::function<void(status_info_t & status_info)> _update_callback;


};

} // namespace future_gui
