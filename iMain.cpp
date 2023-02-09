#include "iGraphics.h"
#include "constants.h"
#include "file_handler.c"

// WINDOW MODES FOR VARIOUS WINDOWS
enum WINDOW_MODES
{
    SPLASH_SCREEN = 101,

    HOME = 110,
    TASK_DETAIL = 111,

    SETTINGS = 121,
    TUTORIAL = 122,
    PROJECT_DETAILS = 123,
    RESIZE_WINDOW = 124,
    COLOR_PICKER = 125,
};

// METHODS DEFINITIONS

void initEditMode(char* textToEdit, int textBoxX, int textBoxY, int charecterWidth, int maxLength);
void endEditMode();

// ==================================================================================================
// ================================ START TIME ======================================================
// ==================================================================================================

typedef struct
{
    int day;
    int month;
    int year;
} Date;

typedef struct
{
    Date date;
    int hour;
    int minute;
} Time;

Time calculateDeadline(Time start, Time interval)
{
    Time deadline;
    // MIGHT IMPLEMENT A ALGORITHM LATER
    return deadline;
}

// ==================================================================================================
// ================================== END TIME ======================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START CLICK CHECKER =============================================
// ==================================================================================================

// CHECKS IF A POINT IS INSIDE A RECTANGLE. USED FOR RECTANGULAR BUTTON.
int isRectangleClicked(int pointX, int pointY, int x, int y, int w, int h)
{
    if(pointX >= x && pointX <= (x+w) && pointY >= y && pointY <= (y+h))
    {
        return TRUE;
    }

    return FALSE;
}

// CHECKS IF A POINT IS INSIDE A CIRCLE. USED FOR CIRCULAR BUTTON.
int isCircleClicked(int pointX, int pointY, int x, int y, int r)
{
    if((pointX - x)*(pointX - x) + (pointY - y)*(pointY - y) <= r*r)
    {
        return TRUE;
    }

    return FALSE;
}

// ==================================================================================================
// ================================== END CLICK CHECKER =============================================
// ==================================================================================================

// ==================================================================================================
// ================================ START TASKS =====================================================
// ==================================================================================================

// TASK MENU X AND Y. MOVES WITH SLIDER FOR SLIDING EFFECT.
float taskMenuX = 0;
float taskMenuY = 0;

typedef struct
{
    int id; // UNIQUE ID

    char title[TASK_TITLE_CHAR_COUNT + 5];
    char miniDetail[TASK_MINI_DETAIL_CHAR_COUNT + 5];
    char detail[TASK_DETAIL_CHAR_COUNT + 5];

    int isFavourite;
    int isDone;

    Time setTime;
    Time totalTime;
    Time deadline; // deadline = setTime + totalTime
} Task;

int currentTaskCount = 0; // Starts from 0.
int uniqueTaskId = 1; // Only goes up to ensure uniqueness. Starts from 1.

Task tasks[TASK_MAX_COUNT]; // ARRAY OF TASKS.

Task temporary = {-1, "NO TITLE", "", "", FALSE, FALSE, NULL, NULL, NULL}; // USED FOR INPUT (AND FOR CALCULATIONS SOMETIMES)

// ADD TASK TO THE TASK LIST
void addTask(char* title, char* detail, Time deadLine)
{
    if(currentTaskCount >= TASK_MAX_COUNT)
    {
        printf("TASK LIMIT REACHED REMOVE SOME TASKS FIRST!\n");
        return;
    }

    strcpy(temporary.title, title);
    strcpy(temporary.detail, detail);
    // MAKE A MINIMIZED VERSION OF THE DETAIL TO BE DISPLAYED IN THE TASK
    strncpy(temporary.miniDetail, detail, TASK_MINI_DETAIL_CHAR_COUNT); // COPY SOME PARTS
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT]   = '.'; // ADD TAILING "..."
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+1] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+2] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+3] = '\0'; // TERMINATE MINI DETAIL

    temporary.deadline = deadLine;

    Time setTime;
    setTime.hour = 12;
    setTime.minute = 15;

    temporary.isDone = FALSE;
    temporary.setTime = setTime;

    temporary.id = uniqueTaskId;
    uniqueTaskId++;

    tasks[currentTaskCount] = temporary;
    currentTaskCount++;
}

// ADD TASK (NO ARGUMENT). CALLS ITSELF WITH THE ARGUMENTS FILLED WITH EMPTY DATA.
void addTask()
{
    Time deadline;
    deadline.hour = 12;
    deadline.minute = 15;

    addTask("NO TITLE", "MINI DETAIL CLICK DETAIL BUTTON TO SEE FULL DETAIL. ARE YOU SEEING THIS FULL DETAIL NOW WITH SET TIME AND DEAD LINE??", deadline);
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
}

void setTaskAsDone(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isDone = TRUE;
            break;
        }
    }
}

void setTaskAsNotDone(int id)
{
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            tasks[i].isDone = FALSE;
            break;
        }
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
}

// REMOVE THE TASK IF THE ID MATCHES THE PASSED ID.
// PUSHBACK ALL THE IDS INTO THE GAP
// DECREASE THE TASK COUNT (VIRTUAL SIZE)
// [1][2][3][4][5] --> remove(3) --> [1][2]   [3][4] --> [1][2][4][5]
void removeTask(int id)
{
    int pushBask = FALSE;
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            pushBask = TRUE; // THREAT ELIMINATED, NOW PUSH BACK!!
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
}


// IS ANY BUTTON ON THE TASK CLICKED ??
// TAKE ACTION
// BUTTONS : [ADD] [TICK] [DETAIL] [FAVOURITE] [REMOVE]
void checkTaskClicks(int mx, int my)
{
    // IDEA : JUST END THE EDIT MODE IF MOUSE CLICK IS REGISTERED.
    // DONT PANIC IT WILL GET INITIATED IF CLICKED ON THE TEXT BOX IT WAS PREVIULY EDITING
    // WHY? TO STOP EDITING IF USER CLICKS ELSEWHERE
    endEditMode();

    Task currentTask;
    int currentTaskX;
    int currentTaskY;

    // CHECK TASK ADD BUTTON
    if(isCircleClicked(mx, my, TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R))
    {
        printf("ADD BUTTON CLICKED. (COUNT : %d)\n", currentTaskCount+1);
        addTask();
        return ;
    }

    for(int i = 0; i < currentTaskCount; i++)
    {
        currentTaskX = taskMenuX + TASK_SPACE_SIDE;
        currentTaskY = WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_SPACE_BETWEEN);

        currentTask = tasks[i];

        // TICK BUTTON
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
        }

        // DETAIL BUTTON
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H))
        {
            printf("DETAIL BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
        }

        // REMOVE BUTTON
        else if(isCircleClicked(mx, my, currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_R))
        {
            printf("REMOVE TASK BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
            removeTask(currentTask.id);
        }

        // FAVOURITE BUTTON
        else if(isCircleClicked(mx, my, currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_ADD_BUTTON_Y, TASK_FAV_BUTTON_R))
        {
            printf("FAVOURITE BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
        }

        // TITLE INPUT BOX. IF PRESSED INSIDE THIS BOX TITLE EDIT IS TRIGGERED.
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_TITLE_INPUT_BOX_X, currentTaskY + TASK_TITLE_INPUT_BOX_Y, TASK_TITLE_INPUT_BOX_W, TASK_TITLE_INPUT_BOX_H))
        {
            printf("TITLE INPUT BOX CLICKED.\n");
            initEditMode(tasks[i].title, currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, 9, TASK_TITLE_CHAR_COUNT);
        }
    }
}

void updateTask()
{

}

void drawTasks()
{
    double currentTaskX, currentTaskY; // X AND Y OF THE TASK CURRENTLY ITERATING

    // SHOW ADD TASK MESSAGE IF THERE IS NO TASK
    if(currentTaskCount == 0)
    {
        iText(20, WINDOW_HEIGHT - 40, "Add new task using the ADD TASK button below.", GLUT_BITMAP_HELVETICA_18);
        iText(TASK_ADD_BUTTON_X - 145, TASK_ADD_BUTTON_Y - 9, "ADD TASK", GLUT_BITMAP_HELVETICA_18);
    }

    for(int i = 0; i < currentTaskCount; i++)
    {
        // CALCULATE TASK BODY X AND Y CO-ORDINATE
        currentTaskX = taskMenuX + TASK_SPACE_SIDE;
        currentTaskY = WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_SPACE_BETWEEN);

        // TASK BODY (BACKGROUND ACTUALLY)
        iSetColor(TASK_COLOR_R, TASK_COLOR_G, TASK_COLOR_B);
        iFilledRectangle(currentTaskX, currentTaskY, TASK_WIDTH, TASK_HEIGHT);

        // TICK BUTTON
        if(tasks[i].isDone)
        {
            iSetColor(TASK_TICK_BUTTON_COMPLETE_R, TASK_TICK_BUTTON_COMPLETE_G, TASK_TICK_BUTTON_COMPLETE_B);
        }
        else
        {
            iSetColor(TASK_TICK_BUTTON_UNCOMPLETE_R, TASK_TICK_BUTTON_UNCOMPLETE_G, TASK_TICK_BUTTON_UNCOMPLETE_B);
        }

        iFilledCircle(currentTaskX + TASK_TICK_BUTTON_X, currentTaskY + TASK_TICK_BUTTON_Y, TASK_TICK_BUTTON_R, 30);

        // REMOVE BUTTON
        iSetColor(255, 255, 255);
        iFilledCircle(currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_R, 30);

        // FAVOURITE TASK BUTTON
        iFilledCircle(currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_FAV_BUTTON_Y, TASK_FAV_BUTTON_R, 30);

        // MINI DETAILS BUTTON
        iFilledRectangle(currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H);

        // TEXT : TITLE AND MINI DETAILS
        iSetColor(TASK_TEXT_COLOR_R, TASK_TEXT_COLOR_G, TASK_TEXT_COLOR_B);
        // TITLE
        iText(currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, tasks[i].title, GLUT_BITMAP_9_BY_15); //GLUT_BITMAP_HELVETICA_18);
        // DEBUG : TITLE INPUT TEXT BOX
        // iRectangle(currentTaskX + TASK_TITLE_INPUT_BOX_X, currentTaskY + TASK_TITLE_INPUT_BOX_Y, TASK_TITLE_INPUT_BOX_W, TASK_TITLE_INPUT_BOX_H);

        // MINI DETAILS
        iText(currentTaskX + TASK_MINI_DETAIL_X, currentTaskY + TASK_MINI_DETAIL_Y, tasks[i].miniDetail, GLUT_BITMAP_8_BY_13); //GLUT_BITMAP_HELVETICA_12);
    }

    // DRAW ADD BUTTON (NOT REPETETIVELY JUST ONCE)
    iSetColor(255, 255, 255);
    iFilledCircle(TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R, 50);
}

// ==================================================================================================
// ================================== END TASKS =====================================================
// ==================================================================================================


// ==================================================================================================
// ================================ START TEXT INPUT ================================================
// ==================================================================================================

int isCursorDisplayed = 1;
int currentCursorPosition = 0;

int textBoxPosX = 0, textBoxPosY = 0;
int charWidth = 0;

int isEditMode = FALSE;
char* editString;
int lengthOfEditString;
int maxLengthOfEditString;

void blinkingCursor(void)
{
    isCursorDisplayed *= -1;
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

void drawCursor()
{
    if(isEditMode && isCursorDisplayed == 1)
    {
        iSetColor(255, 255, 255);
        iFilledRectangle(textBoxPosX + currentCursorPosition*charWidth, textBoxPosY, CURSOR_WIDTH, CURSOR_HEIGHT);
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

    currentCursorPosition = lengthOfEditString;

    printf("EDIT MODE INITIATED (%s)\n", editString);
}

void endEditMode()
{
    if(editString != NULL)
    {
        printf("EDIT MODE ENDED (%s)\n", editString);
    }

    isEditMode = FALSE;
    editString = nullptr;
    charWidth = 0;
}

void writeOnTextBox(unsigned char key)
{
    if(isEditMode)
    {
        if(key == '\r')
        {
            endEditMode();
        }
        else if(key == '\b')
        {
            if(lengthOfEditString > 0)
            {
                pushLeft(editString, currentCursorPosition-1, &lengthOfEditString);
                currentCursorPosition--;
            }
        }
        else
        {
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
                    lengthOfEditString++;
                }
                currentCursorPosition++;
            }
        }
    }
}

// ==================================================================================================
// ================================ END TEXT INPUT ==================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START SLIDER ====================================================
// ==================================================================================================

double sliderHandleX = SLIDER_HANDLE_X; // NOT INTERESETED
double sliderHandleY = WINDOW_HEIGHT - SLIDER_HANDLE_H; // MY MAIN POINT OF FOCUS

// INITIALISED TO -1, TO IDENTIFY THE FIRST CLICK.
int previousMx = -1;
int previousMy = -1;

int totalPageCount = 1; // Perpage 7 tasks

// MOVE SLIDER BY THE DEVIATION OF THE Y CORD OF MOUSE
void moveSlider(int mx, int my)
{
    if(previousMx == -1 && previousMy == -1)
    {
        if(isRectangleClicked(mx, my, sliderHandleX, sliderHandleY, SLIDER_HANDLE_W, SLIDER_HANDLE_H))
        {
            previousMx = mx;
            previousMy = my;
            printf("SLIDER MOVED.\n");
        }
    }
    else
    {
        sliderHandleY += my - previousMy;

        if(sliderHandleY <= 0)
        {
            sliderHandleY = 0;
        }
        else if((sliderHandleY + SLIDER_HANDLE_H) >= WINDOW_HEIGHT)
        {
            sliderHandleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        previousMx = mx;
        previousMy = my;
    }
}

// (IF MOUSE CLICK RELEASED) RESET THE PREVIOUS MOUSE CO ORDINATES TO -1
void sliderMovingStopped()
{
    previousMx = -1;
    previousMy = -1;
}

// IF TASK IS ADDED SLIDER BECOMES SMALLER AND
// IT DEVIATES THE PAGE A LITTLE
void recalculateSlider()
{

}

// DRAWS THE SLIDER BACKGROUND AND HANDLE
void drawSlider()
{
    // SLIDER BG
    iSetColor(SLIDER_BG_COLOR_R, SLIDER_BG_COLOR_G, SLIDER_BG_COLOR_B);
    iFilledRectangle(SLIDER_BG_X, SLIDER_BG_Y, SLIDER_BG_W, SLIDER_BG_H);

    // SLIDER HANDLE
    iSetColor(SLIDER_HANDLE_COLOR_R, SLIDER_HANDLE_COLOR_G, SLIDER_HANDLE_COLOR_B);
    iFilledRectangle(sliderHandleX, sliderHandleY, SLIDER_HANDLE_W, SLIDER_HANDLE_H);
}

// ==================================================================================================
// ================================ END SLIDER ======================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START BACKGROUND ================================================
// ==================================================================================================

// BACKGROUND OF THE WHOLE APP
void drawBackground()
{
    iSetColor(BACKGROUND_COLOR_R, BACKGROUND_COLOR_G, BACKGROUND_COLOR_B);
    iFilledRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

// ==================================================================================================
// ================================ END BACKGROUND ==================================================
// ==================================================================================================

// ==================================================================================================
// ============================ START MAIN APP LOOP =================================================
// ==================================================================================================

int main()
{
    iSetTimer(CURSOR_BLINK_TIME, blinkingCursor);

    enum WINDOW_MODES CURRENT_WINDOW;
    CURRENT_WINDOW = HOME;
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
    setTaskAsDone(5);

    //printf("CURRENT WINDOW CODE : %d", CURRENT_WINDOW);

    iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    return 0;
}

void iMouseMove(int mx, int my)
{
    moveSlider(mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        checkTaskClicks(mx, my);
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
}

void iUpdate()
{
    updateTask();
}

void iDraw()
{
    iUpdate();
    iClear();

    // DRAWING
    drawBackground;
    drawTasks();
    drawSlider();
    drawCursor();
}

// ==================================================================================================
// ============================= END MAIN APP LOOP =================================================
// ==================================================================================================
