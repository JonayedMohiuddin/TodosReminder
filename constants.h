/// WINDOW
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 720
char* WINDOW_TITLE = "TODOS REMINDER";

// TRUE FALSE
#define TRUE  1
#define FALSE 0

#define PI 3.1416

/// BACKGROUND
#define BACKGROUND_COLOR_R 28
#define BACKGROUND_COLOR_G 28
#define BACKGROUND_COLOR_B 28

/// CURSOR
#define CURSOR_WIDTH 2
#define CURSOR_HEIGHT 12
#define CURSOR_BLINK_TIME 200

/// ADD BUTTON
#define TASK_ADD_BUTTON_X 450
#define TASK_ADD_BUTTON_Y 50
#define TASK_ADD_BUTTON_R 32

/// TASK CONSTANTS
#define TASK_MAX_COUNT 500

#define TASK_HEIGHT 80
#define TASK_WIDTH 465
#define TASK_PADDING_LEFT 10
#define TASK_PADDING_UP 10

#define TASK_TEXT_COLOR_R 255
#define TASK_TEXT_COLOR_G 255
#define TASK_TEXT_COLOR_B 255

#define TASK_TITLE_CHAR_COUNT 26
#define TASK_TITLE_X 50
#define TASK_TITLE_Y 50

#define TASK_TITLE_INPUT_BOX_X 45
#define TASK_TITLE_INPUT_BOX_Y 40
#define TASK_TITLE_INPUT_BOX_W 245
#define TASK_TITLE_INPUT_BOX_H 30

#define TASK_DETAIL_CHAR_COUNT 585

#define TASK_MINI_DETAIL_CHAR_COUNT 47
#define TASK_MINI_DETAIL_X 50
#define TASK_MINI_DETAIL_Y 15

/// TEMPO
#define TASK_TICK_BUTTON_UNCOMPLETE_R 150
#define TASK_TICK_BUTTON_UNCOMPLETE_G 0
#define TASK_TICK_BUTTON_UNCOMPLETE_B 0

#define TASK_TICK_BUTTON_COMPLETE_R 0
#define TASK_TICK_BUTTON_COMPLETE_G 150
#define TASK_TICK_BUTTON_COMPLETE_B 0

#define TASK_TICK_BUTTON_X 25
#define TASK_TICK_BUTTON_Y 40
#define TASK_TICK_BUTTON_R 13

#define TASK_DETAIL_BUTTON_X 298
#define TASK_DETAIL_BUTTON_Y 45
#define TASK_DETAIL_BUTTON_W 56
#define TASK_DETAIL_BUTTON_H 25
#define TASK_DETAIL_BUTTON_TEXT_X 6
#define TASK_DETAIL_BUTTON_TEXT_Y 8

#define TASK_FAV_BUTTON_X 378
#define TASK_FAV_BUTTON_Y 42
#define TASK_FAV_BUTTON_W 32
#define TASK_FAV_BUTTON_H 32
#define TASK_FAV_BUTTON_TEXT_X 5
#define TASK_FAV_BUTTON_TEXT_Y 8

//#define TASK_FAV_BUTTON_CLICK_X 392
//#define TASK_FAV_BUTTON_CLICK_Y 57
//#define TASK_FAV_BUTTON_CLICK_R 12

#define TASK_REMOVE_BUTTON_X 427
#define TASK_REMOVE_BUTTON_Y 45
#define TASK_REMOVE_BUTTON_W 24
#define TASK_REMOVE_BUTTON_H 24

//#define TASK_REMOVE_BUTTON_CLICK_X 430
//#define TASK_REMOVE_BUTTON_CLICK_Y 57
//#define TASK_REMOVE_BUTTON_CLICK_R 12

#define TASK_COLOR_R 42
#define TASK_COLOR_G 42
#define TASK_COLOR_B 42

/// SLIDER CONSTANTS
#define SLIDER_BG_COLOR_R 46
#define SLIDER_BG_COLOR_G 46
#define SLIDER_BG_COLOR_B 46
#define SLIDER_HANDLE_COLOR_R 200
#define SLIDER_HANDLE_COLOR_G 200
#define SLIDER_HANDLE_COLOR_B 200
#define SLIDER_HANDLE_HOVER_COLOR_R 160
#define SLIDER_HANDLE_HOVER_COLOR_G 160
#define SLIDER_HANDLE_HOVER_COLOR_B 160
#define SLIDER_HANDLE_CLICKED_COLOR_R 130
#define SLIDER_HANDLE_CLICKED_COLOR_G 130
#define SLIDER_HANDLE_CLICKED_COLOR_B 130

#define SLIDER_BG_X 485
#define SLIDER_BG_Y 0
#define SLIDER_BG_W 15
#define SLIDER_BG_H WINDOW_HEIGHT

#define SLIDER_HANDLE_X 485
#define SLIDER_HANDLE_Y -1
#define SLIDER_HANDLE_W 15
#define SLIDER_HANDLE_H 100

/// DETAIL WINDOW
#define DETAIL_WINDOW_X 50
#define DETAIL_WINDOW_Y 100
#define DETAIL_WINDOW_W 400
#define DETAIL_WINDOW_H 540

#define DETAIL_WINDOW_TOP_BAR_X DETAIL_WINDOW_X
#define DETAIL_WINDOW_TOP_BAR_Y 580
#define DETAIL_WINDOW_TOP_BAR_W DETAIL_WINDOW_W
#define DETAIL_WINDOW_TOP_BAR_H 60

#define DETAIL_REMOVE_BUTTON_X DETAIL_WINDOW_TOP_BAR_X + DETAIL_WINDOW_TOP_BAR_W - 55
#define DETAIL_REMOVE_BUTTON_Y DETAIL_WINDOW_TOP_BAR_Y + 7
#define DETAIL_REMOVE_BUTTON_W 48
#define DETAIL_REMOVE_BUTTON_H 48

/// DETAIL INPUT MULTILINE TEXTBOX
#define WORD_PER_LINE 46

#define DETAIL_INPUT_X DETAIL_WINDOW_X + 10
#define DETAIL_INPUT_Y DETAIL_WINDOW_Y + 10
#define DETAIL_INPUT_W DETAIL_WINDOW_W - 20
#define DETAIL_INPUT_H 270

/// TIME CHANGE WINDOW
#define TIME_CHANGE_WINDOW_X 50
#define TIME_CHANGE_WINDOW_Y 100
#define TIME_CHANGE_WINDOW_W 400
#define TIME_CHANGE_WINDOW_H 540


#define TIME_CHANGE_WINDOW_TOP_BAR_X TIME_CHANGE_WINDOW_X
#define TIME_CHANGE_WINDOW_TOP_BAR_Y 590
#define TIME_CHANGE_WINDOW_TOP_BAR_W TIME_CHANGE_WINDOW_W
#define TIME_CHANGE_WINDOW_TOP_BAR_H 50

/// DEFAULT DEADLINE TIME GAP /// 24*60*60 ONEDAY DEFAULT
/// 30 SECONDS FOR TEST PURPOSE
#define DEFAULT_DEADLINE_TIME_GAP_IN_SECONDS 86400 /// DEFAULT IS ONE DAY (86400 SECONDS)

/// AUTOSAVE (INCREASE IF FACING LAGS)
#define AUTO_SAVE_INTERVAL_SECONDS 6

/// ALARM CHECK INTERVALS IN SECONDS
#define ALARM_BEEP_INTERVAL 30
#define ALARM_CHECK_INTERVAL_SECONDS 7

/// COLOR IGNORE CODES (CONVERT HEX COLOR CODE OR BGR TO DECIAMAL)
#define IGNORE_YELLOW_COLOR 65535
