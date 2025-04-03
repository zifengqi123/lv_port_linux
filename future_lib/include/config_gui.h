#ifndef __CONFIG_GUI_H__
#define __CONFIG_GUI_H__

/**
 * 语言选择
 */
#ifndef LANGUAGE_EN
#define LANGUAGE_EN 0
#endif

#ifndef LANGUAGE_ZH
#define LANGUAGE_ZH 0
#endif

#ifndef LANGUAGE_AL
#define LANGUAGE_AL 1
#endif

/**
 * MENU define
 */
#define STATUS_VIEW_HIGHT       (24)

#define MENU_VIEW_WIDTH         (320)
#define MENU_VIEW_HEIGHT        (240 - STATUS_VIEW_HIGHT)
#define MENU_ITEM_TEXT_WIDTH    (MENU_VIEW_WIDTH - 10)
#define MENU_ITEM_TEXT_HEIGHT   (36)

#define MENU_ITEM_SELECT_BG_COLOR       0x00A0FF
#define MENU_ITEM_UNSELECT_BG_COLOR     0xFFFFFF
#define MENU_ITEM_TEXT_COLOR            0x000000
#define MENU_ITEM_TEXT_SIZE             24


#if LANGUAGE_AL
#define MENU_ITEM_TEXT_FONT   &lv_font_dejavu_16_persian_hebrew
#define MENU_ITEM_TEXT_ALIGN  LV_TEXT_ALIGN_RIGHT
#define MENU_ITEM_TEXT_DIRSTYLE  LV_BASE_DIR_RTL
#elif LANGUAGE_EN
#define MENU_ITEM_TEXT_FONT   &lv_font_montserrat_16
#define MENU_ITEM_TEXT_ALIGN  LV_TEXT_ALIGN_LEFT
#define MENU_ITEM_TEXT_DIRSTYLE  LV_BASE_DIR_LTR
#elif LANGUAGE_ZH
#define MENU_ITEM_TEXT_FONT   &lv_font_montserrat_16
#define MENU_ITEM_TEXT_ALIGN  LV_TEXT_ALIGN_LEFT
#define MENU_ITEM_TEXT_DIRSTYLE  LV_BASE_DIR_LTR
#endif


/**
 * INPUT define
 */
#define INPUT_VIEW_WIDTH        (320)
#define INPUT_VIEW_HIGHT        (240 - STATUS_VIEW_HIGHT)

#define NOTICE_VIEW_WIDTH       (320)
#define NOTICE_VIEW_HIGHT       (240 - STATUS_VIEW_HIGHT)


#endif
