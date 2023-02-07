#include "iGraphics.h"
#include "constants.h"
#include "file_handler.c"

enum WINDOW_MODES {SPLASH_SCREEN=101, SETTINGS=102, HOME=103, TASK_DETAIL=104, TUTORIAL=105};

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

    return deadline;
}

// ==================================================================================================
// ================================== END TIME ======================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START CLICK CHECKER =============================================
// ==================================================================================================

int isRectangleClicked(int pointX, int pointY, int x, int y, int w, int h)
{
    if(pointX >= x && pointX <= (x+w) && pointY >= y && pointY <= (y+h))
    {
        return TRUE;
    }

    return FALSE;
}

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

float taskMenuX = 0;
float taskMenuY = 0;

typedef struct
{
    int position;
    int id;

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
Task tasks[TASK_MAX_COUNT];
Task temporary = {0, -1, "NO TITLE", "", "", FALSE, FALSE, NULL, NULL, NULL};

void addTask(char* title, char* detail, Time deadLine)
{
    strcpy(temporary.title, title);
    strcpy(temporary.detail, detail);
    strncpy(temporary.miniDetail, detail, TASK_MINI_DETAIL_CHAR_COUNT);
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT]   = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+1] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+2] = '.';
    temporary.miniDetail[TASK_MINI_DETAIL_CHAR_COUNT+3] = '\0';

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
            strcpy(tasks[i].detail, detail);
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

void removeTask(int id)
{
    int pushBask = FALSE;
    for(int i = 0; i < currentTaskCount; i++)
    {
        if(tasks[i].id == id)
        {
            pushBask = TRUE;
        }

        if(pushBask)
        {
            if(i < currentTaskCount-1)
            {
                tasks[i] = tasks[i+1];
            }
        }
    }
    currentTaskCount--;
}

void checkTaskClicks(double mx, double my)
{
    Task currentTask;
    int currentTaskX;
    int currentTaskY;

    // CHECK TASK ADD BUTTON
    if(isCircleClicked(mx, my, TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R))
    {
        printf("ADD BUTTON CLICKED\n");
        addTask();
        return ;
    }

    for(int i = 0; i < currentTaskCount; i++)
    {
        currentTaskX = taskMenuX + TASK_SPACE_SIDE;
        currentTaskY = WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_SPACE_BETWEEN);

        currentTask = tasks[i];

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
        else if(isRectangleClicked(mx, my, currentTaskX + TASK_DETAIL_BUTTON_X, currentTaskY + TASK_DETAIL_BUTTON_Y, TASK_DETAIL_BUTTON_W, TASK_DETAIL_BUTTON_H))
        {
            printf("DETAIL BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
        }
        else if(isCircleClicked(mx, my, currentTaskX + TASK_REMOVE_BUTTON_X, currentTaskY + TASK_REMOVE_BUTTON_Y, TASK_REMOVE_BUTTON_R))
        {
            printf("REMOVE TASK BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
            removeTask(currentTask.id);
        }
        else if(isCircleClicked(mx, my, currentTaskX + TASK_FAV_BUTTON_X, currentTaskY + TASK_ADD_BUTTON_Y, TASK_FAV_BUTTON_R))
        {
            printf("FAVOURITE BUTTON CLICKED. TASK ID : %d\n", currentTask.id);
        }
    }
}

void updateTask()
{

}

void drawTasks()
{
    double currentTaskX, currentTaskY;

    if(currentTaskCount == 0)
    {
        iText(20, WINDOW_HEIGHT - 40, "Add new task using the ADD TASK button below.", GLUT_BITMAP_HELVETICA_18);
        iText(TASK_ADD_BUTTON_X - 145, TASK_ADD_BUTTON_Y - 9, "ADD TASK", GLUT_BITMAP_HELVETICA_18);
    }

    for(int i = 0; i < currentTaskCount; i++)
    {
        // TASK BODY X AND Y CO-ORDINATE
        currentTaskX = taskMenuX + TASK_SPACE_SIDE;
        currentTaskY = WINDOW_HEIGHT - ((i+1)*TASK_HEIGHT + (i+1)*TASK_SPACE_BETWEEN);

        // TASK BODY
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
        iText(currentTaskX + TASK_TITLE_X, currentTaskY + TASK_TITLE_Y, tasks[i].title, GLUT_BITMAP_HELVETICA_18);
        // MINI DETAILS
        iText(currentTaskX + TASK_MINI_DETAIL_X, currentTaskY + TASK_MINI_DETAIL_Y, tasks[i].miniDetail, GLUT_BITMAP_HELVETICA_12);
    }

    // DRAW ADD BUTTON (NOT REPETETIVELY JUST ONCE)
    iSetColor(255, 255, 255);
    iFilledCircle(TASK_ADD_BUTTON_X, TASK_ADD_BUTTON_Y, TASK_ADD_BUTTON_R, 50);
}

// ==================================================================================================
// ================================== END TASKS =====================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START SLIDER ====================================================
// ==================================================================================================

double sliderHandleX = SLIDER_HANDLE_X;
double sliderHandleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;

double previousMx = -1;
double previousMy=-1;

int test = -1;

void isSliderHandleClicked(double mx, double my)
{

}

void moveSlider(double mx, double my)
{
    if(previousMx != -1 && previousMy != -1)
    {

    }

    sliderHandleY += test;

    if(sliderHandleY <= 0) test *= -1;
    else if((sliderHandleY + SLIDER_HANDLE_H) >= WINDOW_HEIGHT) test *= -1;
}

void sliderMovingStopped()
{
    previousMx = -1;
    previousMy = -1;
}

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
    enum WINDOW_MODES CURRENT_WINDOW;
    CURRENT_WINDOW = HOME;
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

}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        checkTaskClicks(mx, my);
	}
}

void iKeyboard(unsigned char key)
{
    if (key == 'q')
    {
        exit(0);
    }
}

void iSpecialKeyboard(unsigned char key)
{

}

void update()
{
    updateTask();
}

void iDraw()
{
    update();
    iClear();
    // DRAWING
    drawBackground;
    drawTasks();
    drawSlider();
}

// ==================================================================================================
// ============================= END MAIN APP LOOP =================================================
// ==================================================================================================
