#include "sw_notice.h"

extern "C" {

ui_notice_t _notice_ui;
static pthread_mutex_t _show_mutex;

static lv_timer_t *_update_timer;
static char notice_msg[4096] = {0};

static void update_status_timer_cb(lv_timer_t *timer)
{
    pthread_mutex_lock(&_show_mutex);
    lv_label_set_text(_notice_ui.label, notice_msg);
    pthread_mutex_unlock(&_show_mutex);
}

static void event_cbn_key(lv_event_t * e)
{
    uint32_t key = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("key input: %x", key);

    lv_obj_t * obj = lv_event_get_target_obj(e);

    if(key == LV_KEY_ESC && _notice_ui.is_end) {
        LV_LOG_USER("key LV_KEY_ESC. to del.");

        lv_obj_remove_event(_notice_ui.obj, LV_EVENT_KEY);
        sw_notice_ui_del();
    }
    
}

void sw_notice_ui_init(lv_obj_t *parent)
{
    pthread_mutex_init(&_show_mutex, NULL);
    pthread_mutex_lock(&_show_mutex);

    memset(notice_msg, 0, 4096);

    _notice_ui.parent = parent;
    _notice_ui.x_start = 0;
    _notice_ui.y_start = STATUS_VIEW_HIGHT;
    _notice_ui.width = NOTICE_VIEW_WIDTH;
    _notice_ui.hight = NOTICE_VIEW_HIGHT;

    _notice_ui.is_del = false;
    _notice_ui.is_end = false;

    _notice_ui.obj = lv_obj_create(_notice_ui.parent);
    lv_obj_set_size(_notice_ui.obj, _notice_ui.width, _notice_ui.hight);
    lv_obj_set_pos(_notice_ui.obj, _notice_ui.x_start, _notice_ui.y_start);

    lv_obj_set_style_radius(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(_notice_ui.obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(_notice_ui.obj, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(_notice_ui.obj, lv_color_hex(MENU_ITEM_UNSELECT_BG_COLOR), LV_PART_MAIN|LV_STATE_DEFAULT);


    _notice_ui.label = lv_label_create(_notice_ui.obj);
    lv_obj_set_width(_notice_ui.label, _notice_ui.width - MENU_ITEM_TEXT_SIZE*2);
	lv_label_set_long_mode(_notice_ui.label, LV_LABEL_LONG_WRAP);
    lv_obj_align(_notice_ui.label, LV_ALIGN_CENTER, 0, -12);

    lv_obj_set_style_base_dir(_notice_ui.label, LV_BASE_DIR_AUTO, 0);
    lv_obj_add_style(_notice_ui.label, get_sw_style_bysize(SW_FONT_16), 0);

    pthread_mutex_unlock(&_show_mutex);

    lv_group_add_obj(lv_group_get_default(), _notice_ui.obj);
    lv_obj_add_event_cb(_notice_ui.obj, event_cbn_key, LV_EVENT_KEY, NULL);

    lv_label_set_text(_notice_ui.label, notice_msg);

    _update_timer = lv_timer_create(update_status_timer_cb, 200, NULL);
    lv_timer_ready(_update_timer);

}


void sw_notice_ui_del()
{
    if(_update_timer) lv_timer_del(_update_timer);

    if(!_notice_ui.is_del) {
        if(_notice_ui.label) {
            lv_obj_add_flag(_notice_ui.label, LV_OBJ_FLAG_HIDDEN);
            lv_obj_del(_notice_ui.label);
        }
        if(_notice_ui.obj) {
            lv_obj_add_flag(_notice_ui.obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_del(_notice_ui.obj);
        }
    }
    _notice_ui.is_del = true;

    sw_menu_ui_show();
}

void sw_notice_ui_show(const char* msg)
{
    sprintf(notice_msg + strlen(notice_msg), "%s", msg);
}


bool sw_notice_is_del() 
{
    return _notice_ui.is_del;
}

void sw_notice_ui_end()
{
    _notice_ui.is_end = true;
}

}
