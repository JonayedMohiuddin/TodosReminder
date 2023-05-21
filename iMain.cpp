/*
#############################################
# BUET CSE 102 SESSIONAL iGraphics PROJECT  #
# ----------------------------------------- #
# PROJECT    : TODOS REMINDER               #
# AUTHOR     : JONAYED MOHIUDDIN            #
# STUDENT ID : 2105060                      #
# SCOPE      : ADD TASK                     #
#            : REMOVE TASK                  #
#            : TASK DETAIL                  #
#            : SEE TASK ADD TIME            #
#            : SET TASK DEADLINE            #
#            : SET TASK AS FAVOURITE        #
#            : SET TASK AS DONE             #
#            : SAVE TASKS DATA IN FILE      #
#            : ALARM                        #
# SPECIAL FEATURES                          #
#            : INPUT WITH (MOVABLE) CURSOR  #
#            : WINDOW SLIDER                #
#            : HOVERABLE BUTTONS            #
#############################################
*/
#include "iGraphics.h"

/// AUTOSAVE MODE
int isAutoSavingOn = FALSE;

/// IMAGE DATA
char taskBackgroundImage[4][40] = {"assets/task_bg0.bmp", "assets/task_bg1.bmp", "assets/task_bg2.bmp", "assets/task_bg3.bmp"};
int  isAddButtonHovering = FALSE;
char addButtonImage[2][40] = {"assets/add_button.bmp", "assets/add_button_hover.bmp"};

int isRemoveButtonHovering = FALSE;
char removeButtonImage[2][40] = {"assets/remove_button.bmp", "assets/remove_button_hover.bmp"};

int isFavouriteButtonHovering = FALSE;
char favouriteButtonImage[2][40] = {"assets/favourite_button.bmp", "assets/favourite_button_hover.bmp"};
char favouriteButtonClickedImage[2][60] = {"assets/favourite_button_clicked.bmp", "assets/favourite_button_clicked_hover.bmp"};

int isDetailButtonHovering = FALSE;
char detailButtonImage[2][40] = {"assets/detail_button.bmp", "assets/detail_button_hover.bmp"};

int isTickButtonHovering = FALSE;
char tickButtonImage[2][40] = {"assets/tick_button.bmp","assets/tick_button_hover.bmp"};
char tickButtonClickedImage[2][60] = {"assets/tick_button_clicked.bmp","assets/tick_button_clicked_hover.bmp"};

int isSliderHovering = FALSE;
char sliderImage[2][40] = {"assets/slider.bmp","assets/slider_hover.bmp"};

int isMinimizeButtonHovering = FALSE;
char minimizeButtonImage[2][60] = {"assets/minimize_button.bmp","assets/minimize_button_hover.bmp"};

int isChangeButtonHovering = FALSE;
int isDoneButtonHovering = FALSE;

int sliderState = 0; /// 0 normal; 1 hover; 2 clicked;

/// MOUSE HOVER CO ORDINATES
int hx, hy;

/// WINDOW MODES
enum WINDOW_MODES
{
    SPLASH_SCREEN = 101,
    HOME = 110,
    TASK_DETAIL = 111,
    CHANGE_TIME_WINDOW = 112,
};
WINDOW_MODES currentWindow = HOME;

/// SLIDER DEFINITIONS
typedef struct
{
    int handleX;
    int handleY;
    int handleW;
    int handleH;

    int backgroundX;
    int backgroundY;
    int backgroundW;
    int backgroundH;

    int pageSize; // The (height) size of a page of the window;

    int sliderScrollableRangeTotal;
    int windowScrollableRangeMinimum;
    int windowScrollableRangeMaximum;

    float currentRelativePosition; // position of scrollbar as a fraction less than 1. (like percentage)
    float *control; // the y pos of the window the scrollbar is controlling

    char handleImage[15];
    char backgroundImage[15];
} Slider;

Slider taskMenuSlider;     // SLIDER FOR TASK MENU
Slider detailWindowSlider; // SLIDER FOR DETAIL WINDOW

/// FUNCTION DEFINITIONS
void recalculateSlider(Slider *slider);
void saveTasks();
void loadTasks();
void initTimeChangeWindow();
void moveSliderToBottom(Slider *slider);


/// ==================================================================================================
/// ================================ START CONSTANTS =================================================
/// ==================================================================================================

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

#define TASK_TITLE_CHAR_COUNT 37
#define TASK_TITLE_X 50
#define TASK_TITLE_Y 50

#define TASK_TITLE_INPUT_BOX_X 45
#define TASK_TITLE_INPUT_BOX_Y 40
#define TASK_TITLE_INPUT_BOX_W 340
#define TASK_TITLE_INPUT_BOX_H 30

#define TASK_DETAIL_CHAR_COUNT 585

#define TASK_MINI_DETAIL_CHAR_COUNT 40
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

#define TASK_DETAIL_BUTTON_X 400
#define TASK_DETAIL_BUTTON_Y 6
#define TASK_DETAIL_BUTTON_W 56
#define TASK_DETAIL_BUTTON_H 25
#define TASK_DETAIL_BUTTON_TEXT_X 6
#define TASK_DETAIL_BUTTON_TEXT_Y 8

#define TASK_FAV_BUTTON_X 390
#define TASK_FAV_BUTTON_Y 42
#define TASK_FAV_BUTTON_W 32
#define TASK_FAV_BUTTON_H 32
#define TASK_FAV_BUTTON_TEXT_X 5
#define TASK_FAV_BUTTON_TEXT_Y 8

//#define TASK_FAV_BUTTON_CLICK_X 392
//#define TASK_FAV_BUTTON_CLICK_Y 57
//#define TASK_FAV_BUTTON_CLICK_R 12

#define TASK_REMOVE_BUTTON_X 430
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
#define SLIDER_HANDLE_COLOR_R 170
#define SLIDER_HANDLE_COLOR_G 170
#define SLIDER_HANDLE_COLOR_B 170
#define SLIDER_HANDLE_HOVER_COLOR_R 130
#define SLIDER_HANDLE_HOVER_COLOR_G 130
#define SLIDER_HANDLE_HOVER_COLOR_B 130
#define SLIDER_HANDLE_CLICKED_COLOR_R 100
#define SLIDER_HANDLE_CLICKED_COLOR_G 100
#define SLIDER_HANDLE_CLICKED_COLOR_B 100

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

/// ==================================================================================================
/// ================================ START TIME ======================================================
/// ==================================================================================================

typedef struct tm Time;

double timeDifference(Time a, Time b)
{
    time_t t1 = mktime(&a);
    time_t t2 = mktime(&b);

    return difftime(t1, t2);
}

double timeDifferenceWithCurrentTime(Time a)
{
    time_t t1 = mktime(&a);

    time_t rawtime;
    time(&rawtime);

    return difftime(t1, rawtime);
}

void printCurrentTime()
{
    time_t rawtime;
    Time *timeinfo;
    time(&rawtime);

    timeinfo = localtime(&rawtime);
    printf ("Current local time and date: %s\n", asctime(timeinfo));
}

void printTime(Time *timeinfo)
{
    printf ("Current local time and date: %s\n", asctime(timeinfo));
}

/// THERE IS A LINE FEED CHARECTER AT LAST OF THE STRING RETURNED BY THE asctime(struct tm)
/// ONLY FOR HISTORICAL REASON AND BACKWARD COMPATIBILITY
void timeToString(Time time, char *str)
{
    strcpy(str, asctime(&time));
    str[strlen(str)-1] = '\0'; // EAT THE LINE FEED
}

void getCurrentTimeString(char *str)
{
    time_t rawtime;
    Time *timeinfo;
    time(&rawtime);

    timeinfo = localtime(&rawtime);

    strcpy(str, asctime(timeinfo));
    str[strlen(str)-1] = '\0'; // EAT THE LINE FEED
}

/// ==================================================================================================
/// ================================ START MISC CODES ================================================
/// ==================================================================================================

// DRAWS A BOLD LINE
void drawWidthLine(int x1, int y1, int x2, int y2, int widthFromCenter)
{
    for(int i = -1*widthFromCenter; i <= widthFromCenter; i++)
    {
        iLine(x1 + i, y1, x2 + i, y2);
    }
}

/// CHECKS IF A POINT IS INSIDE A RECTANGLE. USED FOR RECTANGULAR BUTTON.
int isRectangleClicked(int pointX, int pointY, int x, int y, int w, int h)
{
    if(pointX >= x && pointX <= (x+w) && pointY >= y && pointY <= (y+h))
    {
        return TRUE;
    }

    return FALSE;
}

/// CHECKS IF A POINT IS INSIDE A CIRCLE. USED FOR CIRCULAR BUTTON.
int isCircleClicked(int pointX, int pointY, int x, int y, int r)
{
    if((pointX - x)*(pointX - x) + (pointY - y)*(pointY - y) <= r*r)
    {
        return TRUE;
    }

    return FALSE;
}


/// ==================================================================================================
/// ================================ START TEXT INPUT ================================================
/// ==================================================================================================

int isCursorDisplayed = 1;
int currentCursorPosition = 0;

int textBoxPosX = 0, textBoxPosY = 0;
int charWidth = 0;

int isEditMode = FALSE;
char* editString;
int lengthOfEditString;
int maxLengthOfEditString;

int isMultiline = FALSE;

void (*callbackFunctionPointer)(void);

void doNothing()
{

}

void blinkingCursor(void)
{
    if(isCursorDisplayed)
    {
        isCursorDisplayed =  FALSE;
    }
    else
    {
        isCursorDisplayed = TRUE;
    }
}

void moveCursor(unsigned char key)
{
    if(key == GLUT_KEY_LEFT)
    {
        if(currentCursorPosition > 0)
        {
            currentCursorPosition--;
        }
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        if(currentCursorPosition < lengthOfEditString)
        {
            currentCursorPosition++;
        }
    }
}

void pushLeft(char *str, int fromIndex, int *length)
{
    for (int i = fromIndex; i < *length; i++)
    {
        str[i] = str[i + 1];
    }

    str[*length] = '\0';
    (*length)--;
}

void pushRight(char *str, int fromIndex, int *length)
{
    for (int i = *length; i > fromIndex; i--)
    {
        str[i] = str[i - 1];
    }

    (*length)++;
    str[*length] = '\0';
}

void initEditMode(char* textToEdit, int textBoxX, int textBoxY, int charecterWidth, int maxLength)
{
    textBoxPosX = textBoxX;
    textBoxPosY = textBoxY;

    isEditMode = TRUE;
    editString = textToEdit;
    lengthOfEditString = strlen(editString);

    maxLengthOfEditString = maxLength;

    charWidth = charecterWidth;

    if(strcmp(editString, "CLICK TO ADD TEXT") == 0)
    {
        strcpy(editString, "");
        lengthOfEditString = strlen(editString);
    }

    currentCursorPosition = lengthOfEditString;

    printf("EDIT MODE INITIATED (%s)\n", editString);

    callbackFunctionPointer = nullptr;
}

/// CALLS MAIN INIT EDIT MODE
/// PLACES THE CURSOR INITIALLY AT THE POSITION OF THE MOUSE
void initEditMode(char* textToEdit, int textBoxX, int textBoxY, int charecterWidth, int maxLength, int mx, int my)
{
    initEditMode(textToEdit, textBoxX, textBoxY, charecterWidth, maxLength);
    currentCursorPosition = (mx - textBoxX) / charecterWidth;

    if(currentCursorPosition > lengthOfEditString)
    {
        currentCursorPosition = lengthOfEditString;
    }
}

/// CALLBACK FUNCTION IS CALLED AFTER THE INPUT IS DONE
/// CAN BE USED TO VALIDATE THE INPUT OR OTHER THINGS
void initEditMode(char* textToEdit, int textBoxX, int textBoxY, int charecterWidth, int maxLength, int mx, int my, void (*callbackFunction)(void))
{
    isMultiline = FALSE;

    initEditMode(textToEdit, textBoxX, textBoxY, charecterWidth, maxLength);
    currentCursorPosition = (mx - textBoxX) / charecterWidth;

    if(currentCursorPosition > lengthOfEditString)
    {
        currentCursorPosition = lengthOfEditString;
    }

    callbackFunctionPointer = callbackFunction;
}

int charectersPerLine;
int lineDistance;

void initMultiLineEditMode(char* textToEdit, int textBoxX, int textBoxY, int charecterWidth, int maxLength, int charPerLine, int lineDistances, int mx, int my)
{
    textBoxPosX = textBoxX;
    textBoxPosY = textBoxY;

    charectersPerLine = charPerLine - 1;
    lineDistance = lineDistances;

    isEditMode = TRUE;
    editString = textToEdit;
    lengthOfEditString = strlen(editString);

    maxLengthOfEditString = maxLength;

    charWidth = charecterWidth;

    if(strcmp(editString, "CLICK TO ADD TEXT") == 0)
    {
        strcpy(editString, "");
        lengthOfEditString = strlen(editString);
    }

    currentCursorPosition = lengthOfEditString;

    printf("EDIT MODE INITIATED (%s)\n", editString);

    isMultiline = TRUE;
}

void endEditMode()
{
    if(editString != NULL)
    {
        printf("EDIT MODE ENDED     (%s)\n\n", editString);

        if(strlen(editString) == 0)
        {
            strcpy(editString, "CLICK TO ADD TEXT");
        }
    }

    isEditMode = FALSE;
    editString = nullptr;
    charWidth = 0;

    if(callbackFunctionPointer)
    {
        (*callbackFunctionPointer)();
        callbackFunctionPointer = nullptr;
    }

    isMultiline = FALSE;
}

int lineNumber = -1;
int inLineXPosition = -1;

void drawCursor()
{
    if(isMultiline && isCursorDisplayed && isEditMode)
    {
        iSetColor(255, 255, 255);
        lineNumber = floor(strlen(editString)/charectersPerLine);
        inLineXPosition = strlen(editString) % charectersPerLine;

        iFilledRectangle(textBoxPosX + inLineXPosition*charWidth, textBoxPosY - lineNumber*lineDistance, CURSOR_WIDTH, CURSOR_HEIGHT);
    }
    else if(isEditMode && isCursorDisplayed)
    {
        iSetColor(255, 255, 255);
        iFilledRectangle(textBoxPosX + currentCursorPosition*charWidth, textBoxPosY, CURSOR_WIDTH, CURSOR_HEIGHT);
    }
}

void writeOnTextBox(unsigned char key)
{
    if(isEditMode)
    {
        if(key == '\r')
        {
            endEditMode();
        }
        /// BACKSPACE BUTTON. CLEARS CHARECTER BEFORE CURSOR
        else if(key == '\b')
        {
            if(lengthOfEditString > 0 && currentCursorPosition > 0)
            {
                pushLeft(editString, currentCursorPosition-1, &lengthOfEditString);
                currentCursorPosition--;
            }
        }
        /// DELETE BUTTON. CLEARS CHARECTER AFTER CURSOR.
        else if(key == 127)
        {
            if(currentCursorPosition < lengthOfEditString)
            {
                pushLeft(editString, currentCursorPosition, &lengthOfEditString);
            }
        }
        else
        {
            //printf("%d\n", (int)key);
            if(lengthOfEditString < maxLengthOfEditString)
            {
                if(currentCursorPosition < lengthOfEditString)
                {
                    pushRight(editString, currentCursorPosition, &lengthOfEditString);
                    editString[currentCursorPosition] = key;
                }
                else
                {
                    editString[currentCursorPosition] = key;
                    editString[currentCursorPosition + 1] = '\0'; // APPEND A NULL AFTER THE CURRENTLY APPENDED CHARECTER. TO AVOID GARBAGE VALUES.
                    lengthOfEditString++; // INCREASE THE LOGICAL SIZE
                }

                currentCursorPosition++;
            }
        }
    }
}

/// ==================================================================================================
/// ================================ START TASKS =====================================================
/// ==================================================================================================

/// TASK MENU X AND Y. MOVES WITH SLIDER FOR SLIDING EFFECT.
float taskWindowX = 0;
float taskWindowY = 0;
int taskWindowWidth  = WINDOW_WIDTH;
int taskWindowHeight = WINDOW_HEIGHT; // UPDATED WITH SLIDER

/// TASKS STRUCTURE ===========
typedef struct
{
    int id; // UNIQUE ID

    int isFavourite;
    int isDone;
    int isDue;

    char title[TASK_TITLE_CHAR_COUNT + 5];
    char miniDetail[TASK_MINI_DETAIL_CHAR_COUNT + 5];
    char detail[TASK_DETAIL_CHAR_COUNT + 5];

    Time taskAddTime;
    Time deadline; // deadline = setTime + totalTime

    int bg;
} Task;

int currentTaskCount = 0; // Starts from 0.
int uniqueTaskId = 1; // Increases only, to ensure uniqueness. Starts from 1. ID GETS ASSIGNED THROUGH THIS VARIABLE.

Task tasks[TASK_MAX_COUNT]; // ARRAY OF TASKS.

Task temporary = {-1, FALSE, FALSE, FALSE, "NO TITLE", "", "", NULL}; // USED FOR INPUT (AND FOR CALCULATIONS SOMETIMES)

int totalComplete = 0;

/// METHOD DEFINITIONS
void initDetailWindow(Task *task);

/// ============================


/// SORT => 1 - ASCENDING; 2 -> DESCENDING;

enum SORT_STYLE
{
    ASCENDING = 1,
    DESCENDING = 2
};

int compareTimes(Time a, Time b, SORT_STYLE sortStyle)
{
    double diffSecs = timeDifference(a, b);

    //printf("Difference in seconds %lf", diffSecs);
    if(diffSecs < 0) // a is less than b or in other words a is before b
    {
        if(sortStyle == ASCENDING)
        {
            return -1;
        }
        else if(sortStyle == DESCENDING)
        {
            return 1;
        }
    }
    else
    {
        if(sortStyle == ASCENDING)
        {
            return 1;
        }
        else if(sortStyle == DESCENDING)
        {
            return -1;
        }
    }

    return -1;
}

SORT_STYLE selectedSortStyle = ASCENDING;

/// PRIORITY LIST [DUE FAVOURITE] > [DUE] > [FAVOURITE] > [NORMAL TASK] > [DONE FAVOURTIE] > [DONE]
/// WEIGHT LIST         3             2          1              0                 -1           -2
/// WEIGHT DISTRIBUTION [DUE] = [2], [FAVOURITE] = [1], DONE = [-2]
int taskComparator(const void *a, const void *b)
{
    Task *taskA = (Task*)a;
    Task *taskB = (Task*)b;

    int taskAPriorityWeight = taskA->isDue*2 + taskA->isFavourite*1 + taskA->isDone * (-2);
    int taskBPriorityWeight = taskB->isDue*2 + taskB->isFavourite*1 + taskB->isDone * (-2);

    if(taskAPriorityWeight == taskBPriorityWeight) /// BOTH SAME PRIORITY, COMPARE USING TIME
    {
        return compareTimes((taskA->taskAddTime), (taskB->taskAddTime), selectedSortStyle);
    }
    else if(taskAPriorityWeight > taskBPriorityWeight)
    {
        return -1; /// DONT SWAP, A SHOULD STAY BEFORE B
    }
    else /// taskA < taskB
    {
        return 1; /// SWAP
    }
}

/// DEPRECATED
// taskA goes after  taskB if taskA is done
// taskA goes before taskB if taskA is favourite
int taskComparatorOld(const void *a, const void *b)
{
    Task *taskA = (Task*)a;
    Task *taskB = (Task*)b;

    /// PRIORITIZE THE DONE ONE TO GO AT LAST
    if((Task*)taskA -> isDone) // TASK A IS DONE
    {
        if((Task*)taskB -> isDone) // TASK B IS ALSO DONE
        {
            /// AS BOTH ARE DONE, PRIORITIZE THE FAVOURITE ONE TO COME AT FIRST
            if((Task*)taskA -> isFavourite) // TASK A IS DONE AND FAVOURITE
            {
                if((Task*)taskB -> isFavourite) // TASK B IS ALSO DONE AND FAVOURITE
                {
                    /// AS BOTH ARE DONE AND FAVOURITE,, PRIORITIZE TIME
                    return compareTimes((taskA->taskAddTime), (taskB->taskAddTime), selectedSortStyle);
                }
                else // TASK B IS DONE BUT NOT FAVOURITE SO NO NEED TO SWAP B SHOULD BE AT LAST
                {
                    return -1;
                }
            }
            else // TASK A IS DONE BUT NOT FAVOURITE
            {
                if((Task*)taskB -> isFavourite) // TASK B IS DONE
                {
                    return 1; // SWAP A AND B SO THAT B GOES FIRST. BECAUSE B IS FAVOURITE A IS NOT.
                }
                else // TASK B IS ALSO DONE AND NOT FAVOURITE SO PRIORITIZE TIME
                {
                    /// COMPARE USING TIME
                    return compareTimes((taskA->taskAddTime), (taskB->taskAddTime), selectedSortStyle);
                }
            }
        }
        else // TASK A IS DONE BUT B IS NOT. SO SWAP SO THAT A GOES AFTER B.
        {
            return 1;
        }
    }
    else // TASK A IS NOT DONE
    {
        if((Task*)taskB -> isDone) // TASK A IS NOT DONE BUT B IS DONE. SO NO NEED TO SWAP B SHOULD BE AFTER A AS IT IS.
        {
            return -1;
        }
        else // TASK B IS ALSO NOT DONE
        {
            if((Task*)taskA -> isFavourite) // TASK A AND B BOTH ARE NOT DONE. BUT A IS FAVOURITE
            {
                if((Task*)taskB -> isFavourite) // B IS ALSO FAVOURITE. PRIORITIZE TIME.
                {
                    /// COMPARE USING TIME
                    return compareTimes((taskA->taskAddTime), (taskB->taskAddTime), selectedSortStyle);
                }
                else // A IS FAVOURITE BUT B IS NOT FAVOURITE. SO NO NEED TO SWAP BECAUSE A SHOULD BE BEFORE B.
                {
                    return -1;
                }
            }
            else // A IS NOT FAVOURITE
            {
                if((Task*)taskB -> isFavourite) // BUT B IS FAVOURITE. SO SWAP BECAUSE B SHOULD COME BEFORE A.
                {
                    return 1;
                }
                else // A AND B BOTH ARE NOT FAVOURITE. SO PRIORITIZE TIME.
                {
                    /// COMPARE USING TIME
                    return compareTimes((taskA->taskAddTime), (taskB->taskAddTime), selectedSortStyle);
                }
            }
        }
    }
}

void sortTasks()
{
    qsort(&tasks[0], currentTaskCount, sizeof(Task), taskComparator);
}

/// ADD TASK TO THE TASK LIST
void addTask(char* title, char* detail)
{
    if(currentTaskCount >= TASK_MAX_COUNT)
    {
        printf("TASK LIMIT REACHED REMOVE SOME TASKS FIRST!\n");
        return;
    }
    /// TITLE AND DETAIL
    strcpy(temporary.title, title);
    strcpy(temporary.detail, detail);
    // MAKE A MINIMIZED VERSION OF THE DETAIL TO BE DISPLAYED IN THE TASK
    strncpy(temporary.miniDetail, detail, TASK_MINI_DETAIL_CHAR_COUNT); // COPY SOME PARTS
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT]   = '.'; // ADD TAILING "..."
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+1] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+2] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+3] = '\0'; // TERMINATE MINI DETAIL

    /// SET TIME
    time_t rawtime;
    Time *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    temporary.taskAddTime = *timeinfo;
    // DEBUG
    printTime(&temporary.taskAddTime);

    /// DEADLINE : SET AFTER ONE DAY OF TASK ADD TIME
    // SO BASICALLY ANY TASK HAS ONE DAY DEADLINE
    // WHICH CAN BE CHANGED LATER
    /// 30 SEC FOR DEBUG PURPOSE CURRENTLY
    time_t deadlineTimeInSeconds = mktime(timeinfo);
    //DEBUG
    //printf("before %d\n", deadlineTimeInSeconds);
    deadlineTimeInSeconds += DEFAULT_DEADLINE_TIME_GAP_IN_SECONDS;
    timeinfo = localtime (&deadlineTimeInSeconds);
    temporary.deadline = *timeinfo;

    temporary.isDone = FALSE;
    temporary.isFavourite = FALSE;

    temporary.id = uniqueTaskId;
    uniqueTaskId++;

    tasks[currentTaskCount] = temporary;
    currentTaskCount++;

    temporary.bg = rand()%4;

    sortTasks();
    recalculateSlider(&taskMenuSlider);
    ///moveSliderToBottom(&taskMenuSlider);

    /// NEW TASK ADDED SAVE ALL TASKS
    saveTasks();
}

/// ADD TASK (NO ARGUMENT). CALLS ITSELF WITH THE ARGUMENTS FILLED WITH EMPTY DEFAULT DATA.
void addTask()
{
    //addTask("CLICK TO ADD TEXT", "MINI DETAIL CLICK DETAIL BUTTON TO SEE FULL DETAIL. ARE YOU SEEING THIS FULL DETAIL NOW WITH SET TIME AND DEAD LINE??");
    //addTask("CLICK TO ADD TEXT", "ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ");
    //addTask("CLICK TO ADD TEXT", "hi starting ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI ABCDEFGHI hi terminating ");
    addTask("CLICK TO ADD TEXT", "CLICK TO ADD TEXT");
}

// REMOVE THE TASK IF THE ID MATCHES THE PASSED ID.
// PUSHBACK ALL THE IDS INTO THE GAP
// DECREASE THE TASK COUNT (VIRTUAL SIZE)
// [1][2][3][4][5] --> remove(3) --> [1][2]...[4][5] --> [1][2][4][5]
void removeTask(int id)
{
    int pushBask = FALSE;
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            pushBask = TRUE; // THREAT ELIMINATED, NOW PUSH BACK!!

            /// if this is done decrement done count
            if(tasks[i].isDone)
            {
                totalComplete--;
            }
        }

        if(pushBask)
        {
            if(i < (currentTaskCount - 1))
            {
                tasks[i] = tasks[i+1];
            }
        }
    }

    currentTaskCount--;

    sortTasks();
    recalculateSlider(&taskMenuSlider);

    saveTasks();
}

void setTaskTitle(int id, char* title)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            strcpy(tasks[i].title, title);
            break;
        }
    }

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

void updateTaskMiniDetail(Task *task)
{
    strncpy(task->miniDetail, task->detail, TASK_MINI_DETAIL_CHAR_COUNT);
    task->miniDetail[TASK_MINI_DETAIL_CHAR_COUNT]   = '.';
    task->miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+1] = '.';
    task->miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+2] = '.';
    task->miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+3] = '\0';
}

void setTaskDetail(int id, char* detail)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            // SET DETAIL
            strcpy(tasks[i].detail, detail);
            // SET MINI DETAIL
            strncpy(tasks[i].miniDetail, detail, TASK_MINI_DETAIL_CHAR_COUNT);
            temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT]   = '.';
            temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+1] = '.';
            temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+2] = '.';
            temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+3] = '\0';
            break;
        }
    }

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

void setTaskAsDone(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isDone = TRUE;
            tasks[i].isDue  = FALSE;
            break;
        }
    }
    sortTasks();
    totalComplete++;

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

void setTaskAsNotDone(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isDone = FALSE;

            if((timeDifferenceWithCurrentTime(tasks[i].deadline) < 0))
            {
                tasks[i].isDue = TRUE;
            }

            break;
        }
    }
    sortTasks();
    totalComplete--;

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

void setTaskAsFavourite(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isFavourite = TRUE;
            break;
        }
    }
    sortTasks();

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

void setTaskAsNotFavourite(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isFavourite = FALSE;
            break;
        }
    }
    sortTasks();

    if(!isAutoSavingOn)
    {
        saveTasks();
    }
}

// IS ANY BUTTON ON THE TASK CLICKED ??
// TAKE ACTION ACCORDINGLY
// BUTTONS : [ADD] [TICK] [DETAIL] [FAVOURITE] [REMOVE] [TITLE_EDIT_INPUTBOX]
void checkTaskWindowClicks(int mx, int my)
{
    // JUST ENDS THE EDIT MODE IF MOUSE CLICK IS REGISTERED.
    // IT WILL GET INITIATED IF CLICKED ON THE TEXT BOX IT WAS PREVIOUSLY EDITING.
    // WHY? TO STOP EDITING IF USER CLICKS ELSEWHERE.
    endEditMode();

    Task currentTask;
    int currentTaskX;
    int currentTaskY;

    // CHECK TASK ADD BUTTON
    if(isCircleClicked(mx, my, TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R))
    {
        printf("ADD BUTTON CLICKED. (COUNT : %d)\n", currentTaskCount+1);
        addTask();
        PlaySound("assets/click.wav", NULL, SND_ASYNC);
        return ;
    }

    // CHECK FOR EACH TASK SEPARATELY
    for(int i = 0; i < currentTaskCount; i++)
    {
        currentTaskX = taskWindowX + TASK_PADDING_LEFT;
        currentTaskY = taskWindowY + WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_PADDING_UP);

        currentTask = tasks[i];

        if((currentTaskY) < 0)
        {
            break;
        }

        /// TICK BUTTON
        if(isCircleClicked(mx, my, currentTaskX + TASK_TICK_BUTTON_X, currentTaskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R))
        {
            printf("TICK BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
            if(currentTask.isDone)
            {
                setTaskAsNotDone(currentTask.id);
            }
            else
            {
                setTaskAsDone(currentTask.id);
            }
            PlaySound("assets/click.wav", NULL, SND_ASYNC);
        }

        /// DETAIL BUTTON
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H))
        {
            printf("DETAIL BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
            //printTime(&currentTask.taskAddTime);
            initDetailWindow(&tasks[i]);
            PlaySound("assets/click.wav", NULL, SND_ASYNC);
        }

        /// REMOVE BUTTON
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_W, TASK_REMOVE_BUTTON_H))
        {
            printf("REMOVE TASK BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
            removeTask(currentTask.id);
            PlaySound("assets/click.wav", NULL, SND_ASYNC);
        }

        /// FAVOURITE BUTTON
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, TASK_FAV_BUTTON_W, TASK_FAV_BUTTON_H))
        {
            printf("FAVOURITE BUTTON CLICKED. TASK ID : %d\n %d", currentTask.id);
            if(currentTask.isFavourite)
            {
                setTaskAsNotFavourite(currentTask.id);
            }
            else
            {
                setTaskAsFavourite(currentTask.id);
            }
            PlaySound("assets/click.wav", NULL, SND_ASYNC);
        }

        /// TITLE INPUT BOX. IF PRESSED INSIDE THIS BOX TITLE EDIT IS TRIGGERED.
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_TITLE_INPUT_BOX_X, currentTaskY + TASK_TITLE_INPUT_BOX_Y, TASK_TITLE_INPUT_BOX_W, TASK_TITLE_INPUT_BOX_H))
        {
            printf("TITLE INPUT BOX CLICKED. TASK ID : %d\n", currentTask.id);
            initEditMode(tasks[i].title, currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, 9, TASK_TITLE_CHAR_COUNT, mx, my, saveTasks);
        }

        /// MINI DETAIL CLICK BOX. OPENS THE DETAIL WINDOW
        /// CURRENTLY TURNED OFF
        /*
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_MINI_DETAIL_X - 5, currentTaskY + TASK_MINI_DETAIL_Y - 10, 410, 25))
        {
            initDetailWindow(&tasks[i]);
            initMultiLineEditMode(tasks[i].detail, DETAIL_WINDOW_X + 20, DETAIL_WINDOW_Y + 260, 8, TASK_DETAIL_CHAR_COUNT, mx, my);
        }
        */
    }
}

void drawAddButton()
{
    iSetColor(67,212, 144);
    iFilledCircle(TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R, 50);

    iSetColor(255,255, 255);
    iLine(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_X + TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y);
    iLine(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y - 1, TASK_ADD_BUTTON_X + TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y - 1);
    iLine(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y - 2, TASK_ADD_BUTTON_X + TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y - 2);
    iLine(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y + 1, TASK_ADD_BUTTON_X + TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y + 1);
    iLine(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y + 2, TASK_ADD_BUTTON_X + TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_Y + 2);

    iLine(TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y + TASK_ADD_BUTTON_R*0.6);
    iLine(TASK_ADD_BUTTON_X - 1, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_X - 1, TASK_ADD_BUTTON_Y + TASK_ADD_BUTTON_R*0.6);
    iLine(TASK_ADD_BUTTON_X - 2, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_X - 2, TASK_ADD_BUTTON_Y + TASK_ADD_BUTTON_R*0.6);
    iLine(TASK_ADD_BUTTON_X + 1, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_X + 1, TASK_ADD_BUTTON_Y + TASK_ADD_BUTTON_R*0.6);
    iLine(TASK_ADD_BUTTON_X + 2, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R*0.6, TASK_ADD_BUTTON_X + 2, TASK_ADD_BUTTON_Y + TASK_ADD_BUTTON_R*0.6);

    iSetColor(255, 255, 255);
}

void drawRemoveButton(int taskX, int taskY)
{
    int x = taskX + TASK_REMOVE_BUTTON_X;
    int y = taskY + TASK_REMOVE_BUTTON_Y;

    iSetColor(255, 0, 0);
    drawWidthLine(x, y, x + TASK_REMOVE_BUTTON_W, y + TASK_REMOVE_BUTTON_H, 2);
    drawWidthLine(x, y + TASK_REMOVE_BUTTON_H, x + TASK_REMOVE_BUTTON_W, y, 2);
    iSetColor(255, 255, 255);
}

void drawTaskDoneTick(int taskX, int taskY)
{
    iSetColor(TASK_TICK_BUTTON_COMPLETE_R, TASK_TICK_BUTTON_COMPLETE_G, TASK_TICK_BUTTON_COMPLETE_B);
    iFilledCircle(taskX + TASK_TICK_BUTTON_X, taskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R, 20);
    iSetColor(255, 255, 255);
    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X + TASK_TICK_BUTTON_R*0.7, taskY + TASK_TICK_BUTTON_Y + TASK_TICK_BUTTON_R*0.7);
    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5 + 1, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X + TASK_TICK_BUTTON_R*0.7 + 1, taskY + TASK_TICK_BUTTON_Y + TASK_TICK_BUTTON_R*0.7);
    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5 + 2, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X + TASK_TICK_BUTTON_R*0.7 + 2, taskY + TASK_TICK_BUTTON_Y + TASK_TICK_BUTTON_R*0.7);

    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R, taskY + TASK_TICK_BUTTON_Y);
    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5 + 1, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R + 1, taskY + TASK_TICK_BUTTON_Y);
    iLine(taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R*0.5 + 2, taskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R*0.5, taskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R + 2, taskY + TASK_TICK_BUTTON_Y);
}

int taskIdHovering = -1;

void drawTaskWindowHoverButtons()
{
    if(currentWindow == HOME)
    {
        taskIdHovering = -1;
        isAddButtonHovering = FALSE;
        isRemoveButtonHovering = FALSE;
        isFavouriteButtonHovering = FALSE;
        isDetailButtonHovering = FALSE;
        isTickButtonHovering = FALSE;

        Task currentTask;
        int currentTaskX;
        int currentTaskY;

        /// CHECK TASK ADD BUTTON
        if(isCircleClicked(hx, hy, TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R))
        {
            isAddButtonHovering = TRUE;
        }

        /// CHECK SLIDER
        if(sliderState != 2)
        {
            sliderState = 0;

            if(isRectangleClicked(hx, hy, taskMenuSlider.handleX, taskMenuSlider.handleY, taskMenuSlider.handleW, taskMenuSlider.handleH))
            {
                sliderState = 1;
            }
        }

        // CHECK FOR EACH TASK SEPARATELY
        for(int i = 0; i < currentTaskCount; i++)
        {
            currentTaskX = taskWindowX + TASK_PADDING_LEFT;
            currentTaskY = taskWindowY + WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_PADDING_UP);

            currentTask = tasks[i];

            /// TICK BUTTON
            if(isCircleClicked(hx, hy, currentTaskX + TASK_TICK_BUTTON_X, currentTaskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R))
            {
                isTickButtonHovering = TRUE;
                taskIdHovering = i;
                break;
            }

            /// DETAIL BUTTON
            if(isRectangleClicked(hx, hy, currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H))
            {
                isDetailButtonHovering = TRUE;
                taskIdHovering = i;
                break;
            }


            /// REMOVE BUTTON
            if(isRectangleClicked(hx, hy, currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_W, TASK_REMOVE_BUTTON_H))
            {
                isRemoveButtonHovering = TRUE;
                taskIdHovering = i;
                break;
            }

            /// FAVOURITE BUTTON
            if(isRectangleClicked(hx, hy, currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, TASK_FAV_BUTTON_W, TASK_FAV_BUTTON_H))
            {
                isFavouriteButtonHovering = TRUE;
                taskIdHovering = i;
                break;
            }

            /*

            /// TITLE INPUT BOX. IF PRESSED INSIDE THIS BOX TITLE EDIT IS TRIGGERED.
            else if(isRectangleClicked(mx, my, currentTaskX + TASK_TITLE_INPUT_BOX_X, currentTaskY + TASK_TITLE_INPUT_BOX_Y, TASK_TITLE_INPUT_BOX_W, TASK_TITLE_INPUT_BOX_H))
            {
                printf("TITLE INPUT BOX CLICKED. TASK ID : %d\n", currentTask.id);
                initEditMode(tasks[i].title, currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, 9, TASK_TITLE_CHAR_COUNT, mx, my);
            }

            /// MINI DETAIL CLICK BOX. OPENS THE DETAIL WINDOW
            else if(isRectangleClicked(mx, my, currentTaskX + TASK_MINI_DETAIL_X - 5, currentTaskY + TASK_MINI_DETAIL_Y - 10, 410, 25))
            {
                initDetailWindow(&tasks[i]);
                initMultiLineEditMode(tasks[i].detail, DETAIL_WINDOW_X + 20, DETAIL_WINDOW_Y + 260, 8, TASK_DETAIL_CHAR_COUNT, mx, my);
            }
            */
        }
    }
    else if(currentWindow == TASK_DETAIL)
    {
        isMinimizeButtonHovering = FALSE;
        isChangeButtonHovering = FALSE;

        if(isRectangleClicked(hx, hy, DETAIL_REMOVE_BUTTON_X, DETAIL_REMOVE_BUTTON_Y,DETAIL_REMOVE_BUTTON_W, DETAIL_REMOVE_BUTTON_H))
        {
            isMinimizeButtonHovering = TRUE;
        }

        if(isRectangleClicked(hx, hy, DETAIL_WINDOW_X + DETAIL_WINDOW_W - 68, DETAIL_WINDOW_Y + 378, 60, 30))
        {
            isChangeButtonHovering = TRUE;
        }
    }
    else if(currentWindow == CHANGE_TIME_WINDOW)
    {
        isDoneButtonHovering = FALSE;

        if(isRectangleClicked(hx, hy, TIME_CHANGE_WINDOW_TOP_BAR_X + 160, TIME_CHANGE_WINDOW_Y + 30, 100, 50))
        {
            isDoneButtonHovering = TRUE;
        }
    }
}

void drawTaskWindow()
{
    double currentTaskX, currentTaskY; // X AND Y OF THE TASK CURRENTLY ITERATING

    drawTaskWindowHoverButtons();

    // SHOW ADD TASK MESSAGE IF THERE IS NO TASK
    if(currentTaskCount == 0)
    {
        iSetColor(200, 200, 200);
        iText(20, WINDOW_HEIGHT - 40, "Add new task using the ADD TASK button below.", GLUT_BITMAP_HELVETICA_18);
        iText(TASK_ADD_BUTTON_X - 145, TASK_ADD_BUTTON_Y - 9, "ADD TASK", GLUT_BITMAP_HELVETICA_18);
    }

    // DRAW EACH TASK SEPARATELY
    for(int i = 0; i < currentTaskCount; i++)
    {
        // CALCULATE TASK BODY X AND Y CO-ORDINATE
        currentTaskX = taskWindowX + TASK_PADDING_LEFT;
        currentTaskY = taskWindowY + WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_PADDING_UP);

        /// NO NEED TO DRAW TASKS THAT ARE NOT IN SCREEN. STOPs WASTE OF RESOURCES.
        // (+100) or (-100) JUST FOR SAFETY. [[ update :: minimum y = (0) ]]
        if((currentTaskY - 100) > WINDOW_HEIGHT)
        {
            continue;
        }

        //if((currentTaskY + TASK_HEIGHT + 100) < 0)
        if((currentTaskY) < 0)
        {
            break;
        }

        /// TASK BODY (BACKGROUND ACTUALLY)
        if(tasks[i].isDue) /// TASK DUE DRAW RED BORDER
        {
            iSetColor(255, 0, 0);
            iFilledRectangle(currentTaskX - 5, currentTaskY - 5, TASK_WIDTH + 10, TASK_HEIGHT + 10);
        }
        iSetColor(TASK_COLOR_R, TASK_COLOR_G, TASK_COLOR_B);
        iShowBMP2(currentTaskX, currentTaskY, taskBackgroundImage[tasks[i].bg], IGNORE_YELLOW_COLOR);
        //iFilledRectangle(currentTaskX, currentTaskY, TASK_WIDTH, TASK_HEIGHT);

        /// TICK BUTTON
        if(tasks[i].isDone)
        {
            if(taskIdHovering == i)
            {
                iShowBMP2(currentTaskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R, currentTaskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R, tickButtonClickedImage[isTickButtonHovering], IGNORE_YELLOW_COLOR);
            }
            else
            {
                iShowBMP2(currentTaskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R, currentTaskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R, tickButtonClickedImage[0], IGNORE_YELLOW_COLOR);
            }

            //drawTaskDoneTick(currentTaskX, currentTaskY);
        }
        else
        {
            if(taskIdHovering == i)
            {
                iShowBMP2(currentTaskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R, currentTaskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R, tickButtonImage[isTickButtonHovering], IGNORE_YELLOW_COLOR);
            }
            else
            {
                iShowBMP2(currentTaskX + TASK_TICK_BUTTON_X - TASK_TICK_BUTTON_R, currentTaskY + TASK_TICK_BUTTON_Y - TASK_TICK_BUTTON_R, tickButtonImage[0], IGNORE_YELLOW_COLOR);
            }

            //iSetColor(TASK_TICK_BUTTON_UNCOMPLETE_R, TASK_TICK_BUTTON_UNCOMPLETE_G, TASK_TICK_BUTTON_UNCOMPLETE_B);
            //iCircle(currentTaskX + TASK_TICK_BUTTON_X, currentTaskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R, 20);
            //iCircle(currentTaskX + TASK_TICK_BUTTON_X, currentTaskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R - 1, 20);
        }

        /// REMOVE BUTTON
        //iSetColor(255, 255, 255);
        //iRectangle(currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_W, TASK_REMOVE_BUTTON_W);
        //drawRemoveButton(currentTaskX, currentTaskY);

        if(taskIdHovering == i)
        {
            iShowBMP2(currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, removeButtonImage[isRemoveButtonHovering], IGNORE_YELLOW_COLOR);
        }
        else
        {
            iShowBMP2(currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, removeButtonImage[0], IGNORE_YELLOW_COLOR);
        }

        /// FAVOURITE TASK BUTTON
        if(tasks[i].isFavourite)
        {
            iSetColor(255, 255, 255);
            //iFilledRectangle(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, TASK_FAV_BUTTON_W, TASK_FAV_BUTTON_H);
            if(taskIdHovering == i)
            {
                iShowBMP2(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, favouriteButtonClickedImage[isFavouriteButtonHovering],IGNORE_YELLOW_COLOR);
            }
            else
            {
                iShowBMP2(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, favouriteButtonClickedImage[0],IGNORE_YELLOW_COLOR);
            }

            //iSetColor(0, 0, 0);
            //iText(currentTaskX + TASK_FAV_BUTTON_X + TASK_FAV_BUTTON_TEXT_X, currentTaskY + TASK_FAV_BUTTON_Y + TASK_FAV_BUTTON_TEXT_Y, "FAV");
        }
        else
        {
            if(taskIdHovering == i)
            {
                iShowBMP2(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, favouriteButtonImage[isFavouriteButtonHovering],IGNORE_YELLOW_COLOR);
            }
            else
            {
                iShowBMP2(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, favouriteButtonImage[0],IGNORE_YELLOW_COLOR);
            }

            //iSetColor(255, 255, 255);
            //iRectangle(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, TASK_FAV_BUTTON_W, TASK_FAV_BUTTON_H);
            //iText(currentTaskX + TASK_FAV_BUTTON_X + TASK_FAV_BUTTON_TEXT_X, currentTaskY + TASK_FAV_BUTTON_Y + TASK_FAV_BUTTON_TEXT_Y, "FAV");
        }

        /// DETAILS BUTTON
        if(taskIdHovering == i)
        {
            iShowBMP2(currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, detailButtonImage[isDetailButtonHovering], IGNORE_YELLOW_COLOR);
        }
        else
        {
            iShowBMP2(currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, detailButtonImage[0], IGNORE_YELLOW_COLOR);
        }
        //iSetColor(255, 255, 255);
        //iRectangle(currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H);
        //iText(currentTaskX + TASK_DETAIL_BUTTON_X + TASK_DETAIL_BUTTON_TEXT_X, currentTaskY + TASK_DETAIL_BUTTON_Y + TASK_DETAIL_BUTTON_TEXT_Y, "DETAIL", GLUT_BITMAP_HELVETICA_12);

        /// TEXT : TITLE AND MINI DETAILS
        iSetColor(TASK_TEXT_COLOR_R, TASK_TEXT_COLOR_G, TASK_TEXT_COLOR_B);
        /// TITLE
        iText(currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, tasks[i].title, GLUT_BITMAP_9_BY_15); //GLUT_BITMAP_HELVETICA_18);
        // DEBUG : TITLE INPUT TEXT BOX
        //iRectangle(currentTaskX + TASK_TITLE_INPUT_BOX_X, currentTaskY + TASK_TITLE_INPUT_BOX_Y, TASK_TITLE_INPUT_BOX_W, TASK_TITLE_INPUT_BOX_H);

        /// MINI DETAILS (ALSO CLICKABLE TO EXPAND THE DETAIL WINDOW)
        iText(currentTaskX + TASK_MINI_DETAIL_X, currentTaskY + TASK_MINI_DETAIL_Y, tasks[i].miniDetail, GLUT_BITMAP_8_BY_13); //GLUT_BITMAP_HELVETICA_12);
        // DEBUG : MINI DETAIL CLICK BOX
        //iRectangle(currentTaskX + TASK_MINI_DETAIL_X - 5, currentTaskY + TASK_MINI_DETAIL_Y - 10, 410, 25);
    }


    /// DRAW UNDER BAR
    iSetColor(150,150,150);
    iFilledRectangle(0,0, WINDOW_WIDTH, 30);

    /// SHOW TASK COUNT
    iSetColor(0,0,0);
    char temp[10];
    iText(10,10, "Total tasks : ");
    itoa(currentTaskCount, temp, 10);
    iText(120,10, temp);

    iText(200,10, "Due : ");
    itoa(currentTaskCount-totalComplete, temp, 10);
    iText(250,10, temp);

    iText(350,10, "Done : ");
    itoa(totalComplete, temp, 10);
    iText(400,10, temp);



    /// DRAW ADD BUTTON (NOT REPETETIVELY JUST ONCE)
    //drawAddButton();
    iShowBMP2(TASK_ADD_BUTTON_X - TASK_ADD_BUTTON_R, TASK_ADD_BUTTON_Y - TASK_ADD_BUTTON_R, addButtonImage[isAddButtonHovering], IGNORE_YELLOW_COLOR);
}

/// SLIDER FOR THE TASK WINDOW
double initTaskWindowSlider()
{
    taskMenuSlider.handleX = WINDOW_WIDTH  - SLIDER_HANDLE_W;
    taskMenuSlider.handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
    taskMenuSlider.handleW = SLIDER_HANDLE_W;
    taskMenuSlider.handleH = SLIDER_HANDLE_H;

    taskMenuSlider.backgroundX = WINDOW_WIDTH - SLIDER_HANDLE_W;
    taskMenuSlider.backgroundY = 0;
    taskMenuSlider.backgroundW = SLIDER_HANDLE_W;
    taskMenuSlider.backgroundH = WINDOW_HEIGHT;

    taskMenuSlider.pageSize = WINDOW_HEIGHT/2;

    taskMenuSlider.windowScrollableRangeMinimum = 0;
    taskMenuSlider.windowScrollableRangeMaximum = WINDOW_HEIGHT - taskMenuSlider.pageSize;

    taskMenuSlider.sliderScrollableRangeTotal = WINDOW_HEIGHT - taskMenuSlider.handleH;

    taskMenuSlider.control = &taskWindowY;

    taskMenuSlider.currentRelativePosition = (float)(WINDOW_HEIGHT - (taskMenuSlider.handleY + taskMenuSlider.handleH)) / (float)taskMenuSlider.sliderScrollableRangeTotal;
}


/// ==================================================================================================
/// ================================ START TASK DETAIL WINDOW ========================================
/// ==================================================================================================

Task *currentTask;

float detailWindowContentY;

void initDetailWindow(Task *task)
{
    currentWindow = TASK_DETAIL;
    currentTask = task;
}

void checkDetailWindowClicks(int mx, int my)
{
    endEditMode();

    /// IF CLICKED OUTSIDE THE DETAIL WINDOW CLOSE THE WINDOW
    if(isRectangleClicked(mx, my, DETAIL_WINDOW_X, DETAIL_WINDOW_Y, DETAIL_WINDOW_W, DETAIL_WINDOW_H))
    {
        /// DETAIL WINDOW CLOSE BUTTON
        if(isRectangleClicked(mx, my, DETAIL_REMOVE_BUTTON_X, DETAIL_REMOVE_BUTTON_Y,DETAIL_REMOVE_BUTTON_W, DETAIL_REMOVE_BUTTON_H))
        {
            currentWindow = HOME;
            updateTaskMiniDetail(currentTask);
            /// UPDATE TASKS
            saveTasks();
        }
        /// TITLE INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 80, DETAIL_WINDOW_Y + 428, DETAIL_WINDOW_W - 90, 30))
        {
            initEditMode(currentTask->title, DETAIL_WINDOW_X + 85, DETAIL_WINDOW_Y + 440, 8, TASK_TITLE_CHAR_COUNT, mx, my);
        }
        /// DETAIL MULTILINE TEXT INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_INPUT_X, DETAIL_INPUT_Y, DETAIL_INPUT_W, DETAIL_INPUT_H))
        {
            initMultiLineEditMode(currentTask->detail, DETAIL_WINDOW_X + 20, DETAIL_WINDOW_Y + 260, 8, TASK_DETAIL_CHAR_COUNT, WORD_PER_LINE, 20, mx, my);
        }
        /// CHANGE DEADLINE
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + DETAIL_WINDOW_W - 68, DETAIL_WINDOW_Y + 378, 60, 30))
        {
            initTimeChangeWindow();
            //currentWindow = CHANGE_TIME_WINDOW;
        }
    }
    else
    {
        currentWindow = HOME;
        updateTaskMiniDetail(currentTask);
        /// UPDATE TASKS
        saveTasks();
    }
}

char multilineStrings[WORD_PER_LINE];

void drawDetailText()
{
    /// line = (word in string) / (word able to fit per line)
    int totalWord = strlen(currentTask->detail);

    int line = ceil( (double) totalWord / (double)WORD_PER_LINE );

    int currentWordCt = 0;

    for(int i = 0; i <= line; i++)
    {
        for(int j = 0; j < WORD_PER_LINE - 1; j++)
        {
            multilineStrings[j] = currentTask->detail[currentWordCt];

            currentWordCt++;

            if(currentWordCt == totalWord)
            {
                multilineStrings[j + 1] = '\0';
                break;
            }
        }
        multilineStrings[WORD_PER_LINE - 1] = '\0';

        iText(DETAIL_WINDOW_X + 20, DETAIL_WINDOW_Y + 260 - (i*20), multilineStrings);

        if(currentWordCt == totalWord)
        {
            break;
        }
    }
}

char temporaryOutputString[50];

void drawDetailWindow()
{
    /// DETAIL WINDOW BG
    iSetColor(150, 150, 150);
    iFilledRectangle(DETAIL_WINDOW_X, DETAIL_WINDOW_Y, DETAIL_WINDOW_W, DETAIL_WINDOW_H);

    /// DETAIL WINDOW TOP BAR
    //iSetColor(100, 100, 100);
    iSetColor(120, 120, 100);
    iFilledRectangle(DETAIL_WINDOW_TOP_BAR_X, DETAIL_WINDOW_TOP_BAR_Y, DETAIL_WINDOW_TOP_BAR_W, DETAIL_WINDOW_TOP_BAR_H);

    /// DETAIL WINDOW CLOSE BUTTON
    // DEBUG
    //iSetColor(0,0,0);
    //iFilledRectangle(DETAIL_REMOVE_BUTTON_X, DETAIL_REMOVE_BUTTON_Y,DETAIL_REMOVE_BUTTON_W, DETAIL_REMOVE_BUTTON_H);
    iShowBMP2(DETAIL_REMOVE_BUTTON_X, DETAIL_REMOVE_BUTTON_Y, minimizeButtonImage[isMinimizeButtonHovering], IGNORE_YELLOW_COLOR);

    /// SHOW SYSTEM TIME
    getCurrentTimeString(temporaryOutputString);

    iSetColor(0,0,0);
    iText(DETAIL_WINDOW_TOP_BAR_X + 10, DETAIL_WINDOW_TOP_BAR_Y + 40, "Current time", GLUT_BITMAP_9_BY_15);
    iSetColor(0, 0, 100);
    iText(DETAIL_WINDOW_TOP_BAR_X + 10, DETAIL_WINDOW_TOP_BAR_Y + 10, temporaryOutputString, GLUT_BITMAP_9_BY_15);

    /// TITLE
    iSetColor(0, 0, 0);
    iText(DETAIL_WINDOW_X + 10, DETAIL_WINDOW_Y + 440, "To Do");
    iRectangle(DETAIL_WINDOW_X + 80, DETAIL_WINDOW_Y + 428, DETAIL_WINDOW_W - 90, 30);
    iText(DETAIL_WINDOW_X + 85, DETAIL_WINDOW_Y + 440, currentTask->title);

    /// DEADLINE
    timeToString(currentTask->deadline, temporaryOutputString);

    iSetColor(0,0,0);
    iText(DETAIL_WINDOW_X + 10, DETAIL_WINDOW_Y + 390, "Deadline");
    //iRectangle(DETAIL_WINDOW_X + 80, DETAIL_WINDOW_Y + 378, DETAIL_WINDOW_W - 85, 30);
    iSetColor(0, 0, 100);
    iText(DETAIL_WINDOW_X + 100, DETAIL_WINDOW_Y + 390, temporaryOutputString, GLUT_BITMAP_9_BY_15);

    /// CHANGE DEADLINE BUTTON
    if(isChangeButtonHovering == FALSE)
    {
        iSetColor(0,0,0);
        iRectangle(DETAIL_WINDOW_X + DETAIL_WINDOW_W - 68, DETAIL_WINDOW_Y + 378, 60, 30);
        iText(DETAIL_WINDOW_X + DETAIL_WINDOW_W - 65, DETAIL_WINDOW_Y + 390, "Change", GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iSetColor(100,100,100);
        iFilledRectangle(DETAIL_WINDOW_X + DETAIL_WINDOW_W - 68, DETAIL_WINDOW_Y + 378, 60, 30);
        iSetColor(0,0,0);
        iRectangle(DETAIL_WINDOW_X + DETAIL_WINDOW_W - 68, DETAIL_WINDOW_Y + 378, 60, 30);
        iSetColor(0,0,0);
        iText(DETAIL_WINDOW_X + DETAIL_WINDOW_W - 65, DETAIL_WINDOW_Y + 390, "Change", GLUT_BITMAP_9_BY_15);
    }

    /// TASK ADD TIME TIME
    timeToString(currentTask->taskAddTime, temporaryOutputString);

    iSetColor(0,0,0);
    iText(DETAIL_WINDOW_X + 10, DETAIL_WINDOW_Y + 340, "Task Added");
    //iRectangle(DETAIL_WINDOW_X + 80, DETAIL_WINDOW_Y + 378, DETAIL_WINDOW_W - 85, 30);
    iSetColor(0, 0, 100);
    iText(DETAIL_WINDOW_X + 100, DETAIL_WINDOW_Y + 340, temporaryOutputString, GLUT_BITMAP_9_BY_15);

    /// DETAIL
    iSetColor(0,0,0);
    iText(DETAIL_WINDOW_X + 10, DETAIL_WINDOW_Y + 290, "Detail");
    //iRectangle(DETAIL_WINDOW_X + 80, DETAIL_WINDOW_Y + 378, DETAIL_WINDOW_W - 85, 30);
    iRectangle(DETAIL_INPUT_X, DETAIL_INPUT_Y, DETAIL_INPUT_W, DETAIL_INPUT_H);
    drawDetailText();
}

/// SLIDER FOR THE TASK ''DETAIL'' WINDOW
void initDetailWindowSlider()
{
    detailWindowSlider.handleX = WINDOW_WIDTH  - SLIDER_HANDLE_W;
    detailWindowSlider.handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
    detailWindowSlider.handleW = SLIDER_HANDLE_W;
    detailWindowSlider.handleH = SLIDER_HANDLE_H;

    detailWindowSlider.backgroundX = WINDOW_WIDTH - SLIDER_HANDLE_W;
    detailWindowSlider.backgroundY = 0;
    detailWindowSlider.backgroundW = SLIDER_HANDLE_W;
    detailWindowSlider.backgroundH = WINDOW_HEIGHT;

    detailWindowSlider.pageSize = WINDOW_HEIGHT/2;

    detailWindowSlider.windowScrollableRangeMinimum = 0;
    detailWindowSlider.windowScrollableRangeMaximum = WINDOW_HEIGHT - taskMenuSlider.pageSize;

    detailWindowSlider.sliderScrollableRangeTotal = WINDOW_HEIGHT - taskMenuSlider.handleH;

    detailWindowSlider.control = &detailWindowContentY;

    detailWindowSlider.currentRelativePosition = (float)(WINDOW_HEIGHT - (taskMenuSlider.handleY + taskMenuSlider.handleH)) / (float)taskMenuSlider.sliderScrollableRangeTotal;
}


/// ==================================================================================================
/// ================================ START TIME CHANGE WINDOW ========================================
/// ==================================================================================================

Time temporaryTime;
#define MAX_DATE_INT_LENGTH 2
#define MAX_MONTH_INT_LENGTH 2
#define MAX_YEAR_INT_LENGTH 4
#define MAX_SECOND_INT_LENGTH 2
#define MAX_MINUTE_INT_LENGTH 2
#define MAX_HOUR_INT_LENGTH 2

char date[10], month[10], year[10];
char second[10], minute[10], hour[10];

char defaultDate[10], defaultMonth[10], defaultYear[10];
char defaultSecond[10], defaultMinute[10], defaultHour[10];

char months[12][2][10] =
{
    {"January",  "31"},
    {"February", "28"},
    {"March",    "31"},
    {"April",    "30"},
    {"May",      "31"},
    {"June",     "30"},
    {"July",     "31"},
    {"August",   "31"},
    {"September","30"},
    {"October",  "31"},
    {"November", "30"},
    {"December", "31"},
};

int  temporaryNumber;
char temporaryString[100];

void initTimeChangeWindow()
{
    currentWindow = CHANGE_TIME_WINDOW;
    temporaryTime = currentTask->deadline;

    sprintf(defaultDate, "%02d", temporaryTime.tm_mday);
    sprintf(defaultMonth, "%02d", temporaryTime.tm_mon+1); /// MONTH COUNT STARTS FROM ZERO. MADE IT START FROM 1.
    sprintf(defaultYear, "%04d", (temporaryTime.tm_year + 1900)); /// YEAR COUNT STARTS FROM 1900. MADE IT START FROM 0.
    sprintf(defaultSecond, "%02d", temporaryTime.tm_sec);
    sprintf(defaultMinute, "%02d", temporaryTime.tm_min);
    sprintf(defaultHour, "%02d", temporaryTime.tm_hour);

    strcpy(date, defaultDate);
    strcpy(month, defaultMonth);
    strcpy(year, defaultYear);
    strcpy(second, defaultSecond);
    strcpy(minute, defaultMinute);
    strcpy(hour, defaultHour);
}

int setNewDeadline()
{
    temporaryTime.tm_mday = atoi(date);
    temporaryTime.tm_mon  = atoi(month) - 1; /// ROLLBACK TO MONTH STARTING FROM 0.
    temporaryTime.tm_year = atoi(year) - 1900; /// ROLLBACK TO MONTH STARTING FROM 1900.
    temporaryTime.tm_sec  = 0;
    temporaryTime.tm_min  = atoi(minute);
    temporaryTime.tm_hour = atoi(hour);

    currentTask->deadline = temporaryTime;

    currentWindow = TASK_DETAIL;

    return 1;
}

void checkDateValidity()
{
    /// YEAR CANT BE LESS THAN CURRENT YEAR
    if(atoi(year) < (currentTask->taskAddTime.tm_year+1900))
    {
        strcpy(year, defaultYear);
    }

    /// YEAR LIMIT 4000
    if(atoi(year) > 4000)
    {
        strcpy(year, defaultYear);
    }

    /// MONTH CANT BE LESS THAN CURRENT MONTH WHEN THE YEAR IS CURRENT YEAR
    /// OTHERWISE NO PROBLEM
    if((atoi(month) < (currentTask->taskAddTime.tm_mon + 1)) && (atoi(year) == (currentTask->taskAddTime.tm_year+1900)))
    {
        strcpy(month, defaultMonth);
    }

    /// MONTH MUST BE IN RANGE [0,11]
    if(atoi(month) < 1 || atoi(month) > 12)
    {
        strcpy(month, defaultMonth);
    }

    if(atoi(date) > atoi(months[atoi(month)-1][1]))
    {
        strcpy(date, months[atoi(month)-1][1]);
    }

    if(atoi(date) < 1)
    {
        strcpy(date, "01");
    }

    //printf("%s\n", months[atoi(month)-1][0]);

    sprintf(date, "%02d", atoi(date));
    sprintf(month, "%02d", atoi(month));
    sprintf(year, "%04d", atoi(year));
}

void checkTimeValidity()
{
    if(atoi(hour) < 0)
    {
        strcpy(hour, defaultHour); // strcpy(hour, "00");
    }
    if(atoi(hour) > 24)
    {
        strcpy(hour, defaultHour); // strcpy(hour, "24");
    }

    if(atoi(minute) < 0)
    {
        strcpy(minute, defaultMinute); // strcpy(minute, "00");
    }
    if(atoi(minute) > 60)
    {
        strcpy(minute, defaultMinute); // strcpy(minute, "60");
    }

    sprintf(hour, "%02d", atoi(hour));
    sprintf(minute, "%02d", atoi(minute));
}

void checkTimeChangeWindowClicks(int mx, int my)
{
    endEditMode();

    /// IF CLICKED OUTSIDE THE TIME CHANGE WINDOW CLOSE THE WINDOW
    if(isRectangleClicked(mx, my, TIME_CHANGE_WINDOW_X, TIME_CHANGE_WINDOW_Y, TIME_CHANGE_WINDOW_W, TIME_CHANGE_WINDOW_H))
    {
        /// DONE BUTTON
        if(isRectangleClicked(mx, my, TIME_CHANGE_WINDOW_TOP_BAR_X + 160, TIME_CHANGE_WINDOW_Y + 30, 100, 50))
        {
            printf("Done!\n");
            if(!setNewDeadline())
            {
                printf("Failed!");
            }
        }
        /// DATE INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 100, DETAIL_WINDOW_Y + 328, 60, 40))
        {
            initEditMode(date, DETAIL_WINDOW_X + 118, DETAIL_WINDOW_Y + 342, 10, MAX_DATE_INT_LENGTH, mx, my, &checkDateValidity);
        }

        /// MONTH INPUT BOX (STARTS FROM 0)
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 180, DETAIL_WINDOW_Y + 328, 60, 40))
        {
            initEditMode(month, DETAIL_WINDOW_X + 197, DETAIL_WINDOW_Y + 342, 10, MAX_MONTH_INT_LENGTH, mx, my, &checkDateValidity);
        }

        /// YEAR INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 260, DETAIL_WINDOW_Y + 328, 60, 40))
        {
            initEditMode(year, DETAIL_WINDOW_X + 270, DETAIL_WINDOW_Y + 342, 10, MAX_YEAR_INT_LENGTH, mx, my, &checkDateValidity);
        }

        /// HOUR INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 100, DETAIL_WINDOW_Y + 188, 60, 40))
        {
            initEditMode(hour, DETAIL_WINDOW_X + 118, DETAIL_WINDOW_Y + 202, 10, MAX_DATE_INT_LENGTH, mx, my, &checkTimeValidity);
        }

        /// MINUTE INPUT BOX
        else if(isRectangleClicked(mx, my, DETAIL_WINDOW_X + 180, DETAIL_WINDOW_Y + 188, 60, 40))
        {
            initEditMode(minute, DETAIL_WINDOW_X + 197, DETAIL_WINDOW_Y + 202, 10, MAX_DATE_INT_LENGTH, mx, my, &checkTimeValidity);
        }
    }
    else
    {
        currentWindow = TASK_DETAIL;
        updateTaskMiniDetail(currentTask);
        /// UPDATE TASKS
        saveTasks();
    }
}

void drawTimeChangeWindow()
{
    /// TIME CHANGE WINDOW BG
    iSetColor(150, 150, 150);
    iFilledRectangle(TIME_CHANGE_WINDOW_X, TIME_CHANGE_WINDOW_Y, TIME_CHANGE_WINDOW_W, TIME_CHANGE_WINDOW_H);

    /// TIME CHANGE WINDOW TOP BAR
    iSetColor(120, 120, 100);
    iFilledRectangle(TIME_CHANGE_WINDOW_TOP_BAR_X, TIME_CHANGE_WINDOW_TOP_BAR_Y, TIME_CHANGE_WINDOW_TOP_BAR_W, TIME_CHANGE_WINDOW_TOP_BAR_H);

    /// WINDOW TITLE
    iSetColor(0,0,120);
    iText(TIME_CHANGE_WINDOW_X + 10, TIME_CHANGE_WINDOW_Y + TIME_CHANGE_WINDOW_H - 30, "Set Task Deadline", GLUT_BITMAP_HELVETICA_18);

    /// TIME CHANGE WINDOW ENTER BUTTON


    /// SHOW SYSTEM TIME
    getCurrentTimeString(temporaryOutputString);

    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_TOP_BAR_X + 170, TIME_CHANGE_WINDOW_TOP_BAR_Y + 30, "Current time", GLUT_BITMAP_9_BY_15);
    iSetColor(0, 0, 100);
    iText(TIME_CHANGE_WINDOW_TOP_BAR_X + 170, TIME_CHANGE_WINDOW_TOP_BAR_Y + 10, temporaryOutputString, GLUT_BITMAP_9_BY_15);

    /// DEADLINE
    timeToString(currentTask->deadline, temporaryOutputString);

    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 20, TIME_CHANGE_WINDOW_Y + 460, "Current Deadline", GLUT_BITMAP_HELVETICA_18);
    //iRectangle(TIME_CHANGE_WINDOW_X + 80, TIME_CHANGE_WINDOW_Y + 378, TIME_CHANGE_WINDOW_W - 85, 30);
    iSetColor(0, 0, 100);
    iText(TIME_CHANGE_WINDOW_X + 20, TIME_CHANGE_WINDOW_Y + 430, temporaryOutputString, GLUT_BITMAP_TIMES_ROMAN_24);

    /// DATE [DAY][MONTH][YEAR]
    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 20, TIME_CHANGE_WINDOW_Y + 340, "Date", GLUT_BITMAP_HELVETICA_18);

    /// == DAY
    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 118, TIME_CHANGE_WINDOW_Y + 342, date, GLUT_BITMAP_HELVETICA_18);
    iRectangle(TIME_CHANGE_WINDOW_X + 100, TIME_CHANGE_WINDOW_Y + 328, 60, 40);
    iText(TIME_CHANGE_WINDOW_X + 116, TIME_CHANGE_WINDOW_Y + 300, "DD", GLUT_BITMAP_HELVETICA_18);

    /// == MONTH
    iSetColor(0,0,0);
    //iText(TIME_CHANGE_WINDOW_X + 10, TIME_CHANGE_WINDOW_Y + 300, "Month", GLUT_BITMAP_HELVETICA_18);
    iText(TIME_CHANGE_WINDOW_X + 197, TIME_CHANGE_WINDOW_Y + 342, month, GLUT_BITMAP_HELVETICA_18);
    iRectangle(TIME_CHANGE_WINDOW_X + 180, TIME_CHANGE_WINDOW_Y + 328, 60, 40);
    iText(TIME_CHANGE_WINDOW_X + 195, TIME_CHANGE_WINDOW_Y + 300, "MM", GLUT_BITMAP_HELVETICA_18);
    iSetColor(0,0,100);
    if(atoi(month)-1 >= 0 && atoi(month)-1 <= 12)
    {
        iText(TIME_CHANGE_WINDOW_X + 175, TIME_CHANGE_WINDOW_Y + 270, months[atoi(month)-1][0], GLUT_BITMAP_HELVETICA_18); /// PRINT MONTH NAME
    }

    /// == YEAR
    iSetColor(0,0,0);
    //iText(TIME_CHANGE_WINDOW_X + 10, TIME_CHANGE_WINDOW_Y + 220, "Year", GLUT_BITMAP_HELVETICA_18);
    iText(TIME_CHANGE_WINDOW_X + 270, TIME_CHANGE_WINDOW_Y + 342, year, GLUT_BITMAP_HELVETICA_18);
    iRectangle(TIME_CHANGE_WINDOW_X + 260, TIME_CHANGE_WINDOW_Y + 328, 60, 40);
    iText(TIME_CHANGE_WINDOW_X + 260, TIME_CHANGE_WINDOW_Y + 300, "YYYY", GLUT_BITMAP_HELVETICA_18);

    /// TIME [HOUR][MINUTE]
    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 20, TIME_CHANGE_WINDOW_Y + 200, "Time", GLUT_BITMAP_HELVETICA_18);
    iText(TIME_CHANGE_WINDOW_X + 20, TIME_CHANGE_WINDOW_Y + 130, "(24 Hour Format)", GLUT_BITMAP_8_BY_13);

    /// == HOUR
    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 118, TIME_CHANGE_WINDOW_Y + 202, hour, GLUT_BITMAP_HELVETICA_18);
    iRectangle(TIME_CHANGE_WINDOW_X + 100, TIME_CHANGE_WINDOW_Y + 188, 60, 40);
    iText(TIME_CHANGE_WINDOW_X + 110, TIME_CHANGE_WINDOW_Y + 158, "Hour", GLUT_BITMAP_HELVETICA_18);

    /// == MINUTE
    iSetColor(0,0,0);
    iText(TIME_CHANGE_WINDOW_X + 197, TIME_CHANGE_WINDOW_Y + 202, minute, GLUT_BITMAP_HELVETICA_18);
    iRectangle(TIME_CHANGE_WINDOW_X + 180, TIME_CHANGE_WINDOW_Y + 188, 60, 40);
    iText(TIME_CHANGE_WINDOW_X + 185, TIME_CHANGE_WINDOW_Y + 158, "Minute", GLUT_BITMAP_HELVETICA_18);
    iSetColor(0,0,100);

    /// 12 HOUR FORMAT DISPLAY
    /// FUTURE IMPLEMANTATION

    /// DONE BUTTON
    if(isDoneButtonHovering == FALSE)
    {
        iSetColor(0,0,0);
        iRectangle(TIME_CHANGE_WINDOW_TOP_BAR_X + 160, TIME_CHANGE_WINDOW_Y + 30, 100, 50);
        iSetColor(0,0,0);
        iText(TIME_CHANGE_WINDOW_TOP_BAR_X + 182, TIME_CHANGE_WINDOW_Y + 50, "DONE", GLUT_BITMAP_HELVETICA_18);
    }
    else
    {
        iSetColor(100,100,100);
        iFilledRectangle(TIME_CHANGE_WINDOW_TOP_BAR_X + 160, TIME_CHANGE_WINDOW_Y + 30, 100, 50);
        iSetColor(0,0,0);
        iRectangle(TIME_CHANGE_WINDOW_TOP_BAR_X + 160, TIME_CHANGE_WINDOW_Y + 30, 100, 50);
        iSetColor(0,0,0);
        iText(TIME_CHANGE_WINDOW_TOP_BAR_X + 182, TIME_CHANGE_WINDOW_Y + 50, "DONE", GLUT_BITMAP_HELVETICA_18);

    }
}

/// ==================================================================================================
/// ================================ START FILE MANAGER ==============================================
/// ==================================================================================================

FILE *file;

/* TASKS SAVING FORMAT

[INT]    TASK COUNT
[STRING] EMPTY LINE

{

[INT]    SAVE INDEX
[STRING] TITLE
[STRING] DETAIL
[STRING] IS DONE
[STRING] IS FAVOURITE
[TIME_T] SET TIME (IN SECONDS)
[TIME_T] DEADLINE TIME (IN SECONDS)
[STRING] EMPTY NEW LINE

} X TASK COUNT (TIMES)
*/

void saveTasks()
{
    printf("Saving all tasks in file \"database/tasks.txt\".\n");

    file = fopen("database/tasks.txt", "w");
    if(file == NULL)
    {
        printf("FAILED FOR UNKNOWN REASON !!");
        return;
    }

    char temporaryBuffer[100];

    itoa(currentTaskCount, temporaryBuffer, 10);
    fputs(temporaryBuffer, file);
    fputs("\n\n", file);

    for(int i = 0; i < currentTaskCount; i++)
    {
        sprintf(temporaryBuffer, "Task index : %d", i+1);
        fputs(temporaryBuffer, file);
        fputs("\n", file);

        fputs(tasks[i].title, file);
        fputs("\n", file);

        fputs(tasks[i].detail, file);
        fputs("\n", file);

        if(tasks[i].isDone == 1)
        {
            fputs("TRUE", file);
        }
        else
        {
            fputs("FALSE", file);
        }
        fputs("\n", file);

        if(tasks[i].isFavourite == 1)
        {
            fputs("TRUE", file);
        }
        else
        {
            fputs("FALSE", file);
        }
        fputs("\n", file);

        itoa((int)mktime(&tasks[i].taskAddTime), temporaryBuffer, 10);
        fputs(temporaryBuffer, file);
        fputs("\n", file);

        itoa((int)mktime(&tasks[i].deadline), temporaryBuffer, 10);
        fputs(temporaryBuffer, file);
        fputs("\n", file);

        fputs("\n", file);
    }

    fclose(file);

    printf("Successfully saved.\n");
}

void removeTrailingNewLinesFromInput(char str[])
{
    if(str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }
}

void loadTasks()
{
    printf("Loading tasks from file \"database/tasks.txt\".\n");

    file = fopen("database/tasks.txt", "r");
    if(file == NULL)
    {
        return;
    }

    char inputBuffer[1000];
    Time *temporaryTimeinfo;
    time_t temporaryTime;

    uniqueTaskId = 0; /// RESET UNIQUE TASK ID

    if(fgets(inputBuffer, 1000, file))
    {
        //currentTaskCount = atoi(inputBuffer);
        currentTaskCount = atoi(inputBuffer);
        printf("Task count %d\n", currentTaskCount);

        fgets(inputBuffer, 1000, file); /// EAT EMPTY NEW LINE

        totalComplete = 0;

        for(int i = 0; i < currentTaskCount; i++)
        {

            /// TASK SAVING INDEX
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            tasks[i].id = uniqueTaskId;
            uniqueTaskId++;

            /// TASK TITLE
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            strcpy(tasks[i].title, inputBuffer);

            /// TASK DETAIL
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            strcpy(tasks[i].detail, inputBuffer);
            updateTaskMiniDetail(&tasks[i]);

            /// TASK IS DONE
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            if(strcmp(inputBuffer, "TRUE") == 0)
            {
                tasks[i].isDone = TRUE;
                totalComplete++;
            }
            else if(strcmp(inputBuffer, "FALSE") == 0)
            {
                tasks[i].isDone = FALSE;
            }
            else
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }

            /// TASK IS FAVOURITE
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            if(strcmp(inputBuffer, "TRUE") == 0)
            {
                tasks[i].isFavourite = TRUE;
            }
            else if(strcmp(inputBuffer, "FALSE") == 0)
            {
                tasks[i].isFavourite = FALSE;
            }
            else
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }

            /// TASK SET TIME
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            else if(atoi(inputBuffer) < 0)
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }

            removeTrailingNewLinesFromInput(inputBuffer);
            temporaryTime = (time_t)atoi(inputBuffer);
            temporaryTimeinfo = localtime(&temporaryTime);
            tasks[i].taskAddTime = *temporaryTimeinfo;

            /// TASK DEADLINE
            if(!fgets(inputBuffer, 1000, file))
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            else if(atoi(inputBuffer) < 0)
            {
                printf("ERROR WHILE READING FROM FILE!!\n");
                printf("COULDN'T LOAD ALL TASKS. (TASK LOST : %d)  :(\n", currentTaskCount - i);
                currentTaskCount = i;
                break;
            }
            removeTrailingNewLinesFromInput(inputBuffer);
            temporaryTime = (time_t)atoi(inputBuffer);
            temporaryTimeinfo = localtime(&temporaryTime);
            tasks[i].deadline = *temporaryTimeinfo;

            /// EMPTY NEW LINE (IGNORE)
            fgets(inputBuffer, 1000, file);


            /// NOT FROM FILE :: RANDOM BACKGROUND IMAGE SELECT
            tasks[i].bg = rand()%4;

            /// NOT FROM FILE :: CALCULATING IF DUE
            if(!tasks[i].isDone && (timeDifferenceWithCurrentTime(tasks[i].deadline) < 0))
            {
                tasks[i].isDue = TRUE;
            }
        }
    }

    /// RECALCULATE SLIDER FOR TASKS WINDOW
    recalculateSlider(&taskMenuSlider);

    fclose(file);
}

/// ==================================================================================================
/// ================================ START SLIDER ====================================================
/// ==================================================================================================

/*
void updateWindow(Slider *slider)
{
    slider->currentRelativePosition = (float)(WINDOW_HEIGHT - (slider->handleY + slider->handleH)) / (float)slider->sliderScrollableRangeTotal;
    //printf("Slider %f\n", taskMenuSlider.currentRelativePosition);

    *slider->control = slider->windowScrollableRangeMaximum * slider->currentRelativePosition - slider->windowScrollableRangeMinimum;
}
*/

void updateWindow(Slider *slider)
{
    slider->currentRelativePosition = (float)(WINDOW_HEIGHT - (slider->handleY + slider->handleH)) / (float)slider->sliderScrollableRangeTotal;
    *slider->control = slider->windowScrollableRangeMaximum * slider->currentRelativePosition - slider->windowScrollableRangeMinimum;
}

void recalculateSlider(Slider *slider)
{
    slider->windowScrollableRangeMaximum = currentTaskCount * (TASK_HEIGHT + TASK_PADDING_UP) - slider->pageSize;
    updateWindow(slider);
}

/// MOVE SLIDER BY THE DEVIATION OF THE Y CORD OF MOUSE
// INITIALISED TO -1, TO IDENTIFY THE FIRST CLICK.
int previousMx = -1;
int previousMy = -1;

float sliderDeviation;

void moveSlider(int mx, int my, Slider *slider)
{
    sliderState = 0;

    if(previousMx == -1 && previousMy == -1)
    {
        if(isRectangleClicked(mx, my, slider->handleX, slider->handleY, slider->handleW, slider->handleH))
        {
            sliderState = 2; /// CLICKED

            previousMx = mx;
            previousMy = my;
            printf("SLIDER MOVED.\n");
            sliderDeviation = 0;
        }
    }
    else
    {
        sliderState = 2; /// CLICKED

        slider->handleY += my - previousMy;

        if(slider->handleY <= 0)
        {
            slider->handleY = 0;
        }
        else if((slider->handleY + slider->handleH) >= WINDOW_HEIGHT)
        {
            slider->handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        previousMx = mx;
        previousMy = my;

        updateWindow(slider);
    }
}

// (IF MOUSE CLICK RELEASED) RESET THE PREVIOUS MOUSE CO ORDINATES TO -1
void sliderMovingStopped()
{
    sliderState = 0;

    previousMx = -1;
    previousMy = -1;
}

void moveSliderToBottom(Slider *slider)
{
    if(currentTaskCount >= 8)
    {
        slider->handleY = 0;
        updateWindow(slider);
    }
}

void sliderArrowKeyControl(char key, Slider *slider)
{
    if(key == GLUT_KEY_UP)
    {
        slider->handleY += (slider->sliderScrollableRangeTotal)/20;

        if(slider->handleY <= 0)
        {
            slider->handleY = 0;
        }
        else if((slider->handleY + slider->handleH) >= WINDOW_HEIGHT)
        {
            slider->handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow(slider);
    }
    else if(key == GLUT_KEY_DOWN)
    {
        slider->handleY -= (slider->sliderScrollableRangeTotal)/20;

        if(slider->handleY <= 0)
        {
            slider->handleY = 0;
        }
        else if((slider->handleY + slider->handleH) >= WINDOW_HEIGHT)
        {
            slider->handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow(slider);
    }
}

void sliderBackgroundClickControl(int mx, int my, Slider *slider)
{
    if(isRectangleClicked(mx, my, slider->backgroundX, slider->backgroundY, slider->handleX, slider->handleY))
    {
        slider->handleY -= (slider->sliderScrollableRangeTotal)/10;

        if(slider->handleY <= 0)
        {
            slider->handleY = 0;
        }
        else if((slider->handleY + slider->handleH) >= WINDOW_HEIGHT)
        {
            slider->handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow(slider);
    }
    else if(isRectangleClicked(mx, my, slider->handleX, slider->handleY + slider->handleH, slider->handleW, WINDOW_HEIGHT-(slider->handleY + slider->handleH)))
    {
        slider->handleY += (slider->sliderScrollableRangeTotal)/10;

        if(slider->handleY <= 0)
        {
            slider->handleY = 0;
        }
        else if((slider->handleY + slider->handleH) >= WINDOW_HEIGHT)
        {
            slider->handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow(slider);
    }
}

// DRAWS THE SLIDER BACKGROUND AND HANDLE
void drawSlider(Slider *slider)
{
    // SLIDER BG
    iSetColor(SLIDER_BG_COLOR_R, SLIDER_BG_COLOR_G, SLIDER_BG_COLOR_B);
    iFilledRectangle(slider->backgroundX, slider->backgroundY, slider->backgroundW, slider->backgroundH);

    // SLIDER HANDLE
    if(sliderState == 0) /// NORMAL
    {
        iSetColor(SLIDER_HANDLE_COLOR_R, SLIDER_HANDLE_COLOR_G, SLIDER_HANDLE_COLOR_B);
        iFilledRectangle(slider->handleX, slider->handleY, slider->handleW, slider->handleH);
    }
    else if(sliderState == 1) /// HOVER
    {
        iSetColor(SLIDER_HANDLE_HOVER_COLOR_R, SLIDER_HANDLE_HOVER_COLOR_G, SLIDER_HANDLE_HOVER_COLOR_B);
        iFilledRectangle(slider->handleX, slider->handleY, slider->handleW, slider->handleH);
    }
    else /// CLICKED
    {
        iSetColor(SLIDER_HANDLE_CLICKED_COLOR_R, SLIDER_HANDLE_CLICKED_COLOR_G, SLIDER_HANDLE_CLICKED_COLOR_B);
        iFilledRectangle(slider->handleX, slider->handleY, slider->handleW, slider->handleH);
    }
}

/// ==================================================================================================
/// ================================ START BACKGROUND ================================================
/// ==================================================================================================

float redX = 0;
float redY = 0;
double redRotation = 0;

// BACKGROUND OF THE WHOLE APP
void drawBackground()
{
    //iSetColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
    //iFilledRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    iShowBMP(0, 0, "assets/bg.bmp");

    redX += 1;
    redY += 0.5;

    if(redX >= WINDOW_WIDTH + 500)
    {
        redX = -500;
    }
    if(redY >= WINDOW_HEIGHT + 500)
    {
        redY = -500;
    }

    redRotation += 10;
}

/// ==================================================================================================
/// ============================ START MAIN APP LOOP =================================================
/// ==================================================================================================

/// AUTOSAVE ALL TASKS ON A COSNTANT SECONDS INRERVAL
// IT GETS MANUALLY SAVED WHEN
// ADDING NEW TASK, REMOVING TASK, CLOSING DETAIL WINDOW
void autoSave()
{
    printf("Autosaving...\n");
    saveTasks();
}

int isAlarmOn = FALSE;

void checkAlarms()
{
    isAlarmOn = FALSE;

    for(int i = 0; i < currentTaskCount; i++)
    {
        //printf("Difference %lf\n", timeDifferenceWithCurrentTime(tasks[i].deadline));

        if(tasks[i].isDone != TRUE)
        {
            if((timeDifferenceWithCurrentTime(tasks[i].deadline) < ALARM_BEEP_INTERVAL) && (timeDifferenceWithCurrentTime(tasks[i].deadline) > -1 * ALARM_BEEP_INTERVAL))
            {
                tasks[i].isDue = TRUE;

                printf("BEEP!\n");
                printf("BEEP!\n");
                printf("BEEP!\n");
                printf("BEEP!\n");
                printf("BEEP!\n");

                if(!isAlarmOn)
                {
                    PlaySound("assets/alarm.wav", NULL, SND_ASYNC);
                    isAlarmOn = TRUE;
                }
            }
        }
    }

    if(isAlarmOn == TRUE)
    {
        sortTasks();
    }
}

int main(void)
{
    srand(time(0));

    if(isAutoSavingOn)
    {
        iSetTimer(AUTO_SAVE_INTERVAL_SECONDS * 1000, autoSave);
    }

    iSetTimer(ALARM_CHECK_INTERVAL_SECONDS * 1000, checkAlarms);
    iSetTimer(CURSOR_BLINK_TIME, blinkingCursor);
    ///iSetTimer(5000, printCurrentTime);

    initTaskWindowSlider();

    enum WINDOW_MODES CURRENT_WINDOW;
    CURRENT_WINDOW = HOME;
    /*
    addTask();
    addTask();
    addTask();
    addTask();
    addTask();
    setTaskAsDone(1);
    setTaskAsDone(4);
    setTaskAsNotDone(1);
    setTaskTitle(1, "1 Just testing!!");
    setTaskTitle(2, "2 Just testing!!");
    setTaskTitle(3, "3 Just testing!!");
    setTaskTitle(4, "4 Just testing!!");
    setTaskDetail(3, "Hola amigo this is the detail of task id 3. By now this project doesnt have any interactivity. But it will soon inshallah.");
    removeTask(4);
    addTask();
    setTaskTitle(5, "5 Just testing!!");
    setTaskDetail(5, "NO DETAIL");
    setTaskAsDone(5);
    */

    loadTasks();

    //printf("CURRENT WINDOW CODE : %d", CURRENT_WINDOW);

    iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    return 0;
}

void iMouseMove(int mx, int my)
{
    moveSlider(mx, my, &taskMenuSlider);
}

void iMousePassiveMove(int mx, int my)
{
    hx = mx;
    hy = my;
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(currentWindow == HOME)
        {
            checkTaskWindowClicks(mx, my);
            sliderBackgroundClickControl(mx, my, &taskMenuSlider);
        }
        else if(currentWindow == TASK_DETAIL) /// THOUGH THIS IS A OVERLAY WINDOW. INPUT IS HANDLED SEPARATELY FOR HOME AND THIS OVERLAY.
        {
            checkDetailWindowClicks(mx, my);
        }
        else if(currentWindow == CHANGE_TIME_WINDOW)
        {
            checkTimeChangeWindowClicks(mx, my);
        }
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        sliderMovingStopped();
    }
}

void iKeyboard(unsigned char key)
{
    writeOnTextBox(key);
}

void iSpecialKeyboard(unsigned char key)
{
    moveCursor(key);
    sliderArrowKeyControl(key, &taskMenuSlider);
}

void iUpdate()
{

}

void iDraw()
{
    iUpdate();
    iClear();

    // DRAWING
    if(currentWindow == HOME || currentWindow == TASK_DETAIL || currentWindow == CHANGE_TIME_WINDOW)
    {
        drawBackground();
        drawTaskWindow();
        drawSlider(&taskMenuSlider);

        if(currentWindow == TASK_DETAIL || currentWindow == CHANGE_TIME_WINDOW) /// THIS IS A OVERLAY WINDOW OVER TASK WINDOW
        {
            drawDetailWindow();

            if(currentWindow == CHANGE_TIME_WINDOW) /// THIS IS A OVERLAY WINDOW OVER TASK DETAIL WINDOW
            {
                drawTimeChangeWindow();
            }
        }

        drawCursor();
    }
}
