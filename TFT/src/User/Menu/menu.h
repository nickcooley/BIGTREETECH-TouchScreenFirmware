#ifndef _MENU_H_
#define _MENU_H_

#include "stdint.h"
#include "stdbool.h"
#include "GUI.h"

#define IDLE_TOUCH	0xFFFF

#define ITEM_PER_PAGE       8
#define LISTITEM_PER_PAGE   5
#define LIVEICON_LINES      3

#define CENTER_Y          ((exhibitRect.y1 - exhibitRect.y0)/2 + exhibitRect.y0)
#define CENTER_X          ((exhibitRect.x1 - exhibitRect.x0 - BYTE_WIDTH)/2 + exhibitRect.x0)
#define LISTITEM_WIDTH    (LCD_WIDTH-(3*START_X)-LIST_ICON_WIDTH)
#define LISTITEM_HEIGHT   ((LCD_HEIGHT-ICON_START_Y-START_X)/5)
#define LISTICON_SPACE_Y  ((LCD_HEIGHT-ICON_START_Y-START_X-(3*LIST_ICON_HEIGHT))/ 2)

#define TOAST_MSG_COUNT       3
#define TOAST_X_PAD           START_X
#define TOAST_Y_PAD           3

#define TOAST_MSG_LENGTH      35
#define TOAST_DISPLAY_LENGTH  TOAST_MSG_LENGTH

typedef enum
{
  KEY_ICON_0 = 0,
  KEY_ICON_1,
  KEY_ICON_2,
  KEY_ICON_3,
  KEY_ICON_4,
  KEY_ICON_5,
  KEY_ICON_6,
  KEY_ICON_7,
  KEY_LABEL_0,
  KEY_LABEL_1,
  KEY_LABEL_2,
  KEY_LABEL_3,
  KEY_LABEL_4,
  KEY_LABEL_5,
  KEY_LABEL_6,
  KEY_LABEL_7,
  KEY_IDLE = IDLE_TOUCH,
}KEY_VALUES;

typedef enum
{
  MENU_TYPE_ICON,
  MENU_TYPE_LISTVIEW,
  MENU_TYPE_DIALOG
} MENU_TYPE;

typedef union
{
  uint32_t index;    // language index, address = textSelect(index);
  void *address;
}LABEL;

typedef struct
{
  uint16_t icon;
  LABEL label;
}ITEM;

typedef struct
{
  LABEL title;
  ITEM  items[ITEM_PER_PAGE];
}MENUITEMS;


typedef enum
{
  STATUS_IDLE = 0,
  STATUS_BUSY,
  STATUS_UNCONNECT,
  STATUS_NORMAL
}SYS_STATUS;

typedef struct
{
  GUI_RECT rect;
  uint32_t time;
  uint8_t  status;
  int16_t inf;
}REMINDER;

typedef enum
{
  LIST_LABEL = 0,
  LIST_TOGGLE,
  LIST_RADIO,
  LIST_MOREBUTTON,
  LIST_CUSTOMVALUE,
}LISTITEM_TYPE;

typedef struct
{
  uint16_t icon;
  LISTITEM_TYPE itemType;
  LABEL titlelabel;
  LABEL valueLabel;
}LISTITEM;

typedef struct
{
  LABEL title;
  //uint16_t titleIconChar;
  LISTITEM  items[ITEM_PER_PAGE];
}LISTITEMS;

typedef struct
{
  uint8_t *       text;
  GUI_POINT       pos; // relative to icon top left corner
  uint8_t         h_align; //left, right or center of pos point
  uint8_t         v_align; //left, right or center of pos point
  uint16_t        fn_color;
  uint16_t        bk_color;
  GUI_TEXT_MODE   text_mode;
}LIVE_DATA;

 typedef struct
{
 uint8_t   enabled[LIVEICON_LINES];
 LIVE_DATA lines[LIVEICON_LINES];
}LIVE_INFO;

typedef struct
{
  DIALOG_TYPE style;
  uint8_t     isNew;
  char        text[TOAST_MSG_LENGTH];
}TOAST;


void showLiveInfo(uint8_t index, const LIVE_INFO * liveicon, const ITEM * item);

extern const GUI_RECT exhibitRect;
extern const GUI_RECT rect_of_key[ITEM_PER_PAGE*2];

void setMenuType(MENU_TYPE type);
MENU_TYPE getMenuType(void);

void addToast(DIALOG_TYPE style, char * text);
bool toastRunning(void);

void reminderSetUnConnected(void);
void reminderMessage(int16_t inf, SYS_STATUS status);
void volumeReminderMessage(int16_t inf, SYS_STATUS status);

void busyIndicator(SYS_STATUS status);

void GUI_RestoreColorDefault(void);
uint8_t *labelGetAddress(const LABEL *label);
void menuDrawItem (const ITEM * menuItem, uint8_t positon);
void menuDrawIconOnly(const ITEM *item, uint8_t positon);
void menuDrawListItem(const LISTITEM *item, uint8_t positon);
void menuRefreshListPage(void);
void menuDrawTitle(const uint8_t *content); //(const MENUITEMS * menuItems);
void menuReDrawCurTitle(void);
void menuDrawPage (const MENUITEMS * menuItems);
void menuDrawListPage(const LISTITEMS *listItems);
void itemDrawIconPress(uint8_t positon, uint8_t is_press);
KEY_VALUES menuKeyGetValue(void);
GUI_POINT getIconStartPoint(int index);

void loopBackEnd(void);
void loopFrontEnd(void);
void loopProcess (void);

#endif
