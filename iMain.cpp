#include "iGraphics.h"
#include "constants.h"

double mouseHoverX, mouseHoverY;

// ==================================================================================================
// ================================ START FILE ======================================================
// ==================================================================================================

void loadTasks()
{

}

void saveTasks()
{

}

// ==================================================================================================
// ================================== END FILE ======================================================
// ==================================================================================================

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

void updateTask()
{

}

void drawTasks()
{
    double currentTaskX, currentTaskY;
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
}

// ==================================================================================================
// ================================== END TASKS =====================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START SLIDER ====================================================
// ==================================================================================================

void slide()
{

}

void drawSlider()
{
    // SLIDER BG
    iSetColor(SLIDER_BG_COLOR_R, SLIDER_BG_COLOR_G, SLIDER_BG_COLOR_B);
    iFilledRectangle(WINDOW_WIDTH - 20, 0, 10, WINDOW_HEIGHT);

    // HANDLE
    iSetColor(SLIDER_HANDLE_COLOR_R, SLIDER_HANDLE_COLOR_G, SLIDER_HANDLE_COLOR_B);
    iFilledRectangle(WINDOW_WIDTH - 20, 200, 10, 100);

}

// ==================================================================================================
// ================================ END SLIDER ======================================================
// ==================================================================================================

// ==================================================================================================
// ================================ START ADD BUTTON ================================================
// ==================================================================================================

void drawAddButton()
{
    iSetColor(255, 255, 255);
    iFilledCircle(WINDOW_WIDTH - 50, 50, 30, 50);
}

// ==================================================================================================
// ================================ END ADD BUTTON ==================================================
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

    iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    return 0;
}

void iMouseMove(int mx, int my)
{
    mouseHoverX = mx;
    mouseHoverY = my;
}

void iMouse(int button, int state, int mx, int my)
{

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
    drawAddButton();
    drawSlider();
}

// ==================================================================================================
// ============================= END MAIN APP LOOP =================================================
// ==================================================================================================
