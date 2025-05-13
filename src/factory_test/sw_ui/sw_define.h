#ifndef __SW_DEFINE_H___
#define __SW_DEFINE_H___


#ifndef STATUS_VIEW_HIGHT
#define STATUS_VIEW_HIGHT       (24)
#endif

#ifndef MENU_VIEW_WIDTH
#define MENU_VIEW_WIDTH         (320)
#endif

#ifndef MENU_VIEW_HEIGHT
#define MENU_VIEW_HEIGHT        (240 - STATUS_VIEW_HIGHT)
#endif

#ifndef MENU_ITEM_TEXT_WIDTH
#define MENU_ITEM_TEXT_WIDTH    (MENU_VIEW_WIDTH - 10)
#endif

#ifndef MENU_ITEM_TEXT_HEIGHT
#define MENU_ITEM_TEXT_HEIGHT   (36)
#endif

#ifndef MENU_ITEM_SELECT_BG_COLOR
#define MENU_ITEM_SELECT_BG_COLOR       0x00A0FF
#endif

#ifndef MENU_ITEM_UNSELECT_BG_COLOR
#define MENU_ITEM_UNSELECT_BG_COLOR     0xFFFFFF
#endif

#ifndef MENU_ITEM_TEXT_COLOR
#define MENU_ITEM_TEXT_COLOR            0x000000
#endif

#ifndef MENU_ITEM_TEXT_SIZE
#define MENU_ITEM_TEXT_SIZE             24
#endif

#ifndef NOTICE_VIEW_WIDTH
#define NOTICE_VIEW_WIDTH       (320)
#endif

#ifndef NOTICE_VIEW_HIGHT
#define NOTICE_VIEW_HIGHT       (240 - STATUS_VIEW_HIGHT)
#endif

#endif