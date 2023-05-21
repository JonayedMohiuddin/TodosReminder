
/// ==================================================================================================
/// ================================ START SLIDER ====================================================
/// ==================================================================================================

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

Slider taskMenuSlider;
Slider detailWindowSlider;

double initSliders(float *control)
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

    taskMenuSlider.control = control;

    taskMenuSlider.currentRelativePosition = (float)(WINDOW_HEIGHT - (taskMenuSlider.handleY + taskMenuSlider.handleH)) / (float)taskMenuSlider.sliderScrollableRangeTotal;
}

//double sliderHandleX = SLIDER_HANDLE_X; // NOT INTERESETED

//double sliderHandleY = WINDOW_HEIGHT - SLIDER_HANDLE_H; // MAIN POINT OF FOCUS
//int sliderTotalY = WINDOW_HEIGHT - SLIDER_HANDLE_H; // TOTAL SPACE FOR THE SLIDER TO MOVE

//int windowHeight = WINDOW_HEIGHT;
//int windowX = 0;

// IF TASK IS ADDED SLIDER BECOMES SMALLER AND
// IT DEVIATES THE PAGE A LITTLE

void updateWindow()
{
    taskMenuSlider.currentRelativePosition = (float)(WINDOW_HEIGHT - (taskMenuSlider.handleY + taskMenuSlider.handleH)) / (float)taskMenuSlider.sliderScrollableRangeTotal;
    printf("Slider %f\n", taskMenuSlider.currentRelativePosition);

    *taskMenuSlider.control = taskMenuSlider.windowScrollableRangeMaximum * taskMenuSlider.currentRelativePosition - taskMenuSlider.windowScrollableRangeMinimum;
}

void recalculateSlider()
{
    taskMenuSlider.windowScrollableRangeMaximum = currentTaskCount * (TASK_HEIGHT + TASK_PADDING_UP) - taskMenuSlider.pageSize;
    //taskMenuSlider.currentRelativePosition = (float)(WINDOW_HEIGHT - (taskMenuSlider.handleY + taskMenuSlider.handleH)) / (float)taskMenuSlider.sliderScrollableRangeTotal;
    //taskMenuSlider.handleY = slider
    updateWindow();
}


/// MOVE SLIDER BY THE DEVIATION OF THE Y CORD OF MOUSE
// INITIALISED TO -1, TO IDENTIFY THE FIRST CLICK.
int previousMx = -1;
int previousMy = -1;

float sliderDeviation;

void moveSlider(int mx, int my)
{
    if(previousMx == -1 && previousMy == -1)
    {
        if(isRectangleClicked(mx, my, taskMenuSlider.handleX, taskMenuSlider.handleY, taskMenuSlider.handleW, taskMenuSlider.handleH))
        {
            previousMx = mx;
            previousMy = my;
            printf("SLIDER MOVED.\n");
            sliderDeviation = 0;
        }
    }
    else
    {
        taskMenuSlider.handleY += my - previousMy;

        if(taskMenuSlider.handleY <= 0)
        {
            taskMenuSlider.handleY = 0;
        }
        else if((taskMenuSlider.handleY + taskMenuSlider.handleH) >= WINDOW_HEIGHT)
        {
            taskMenuSlider.handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        previousMx = mx;
        previousMy = my;

        updateWindow();
    }
}

// (IF MOUSE CLICK RELEASED) RESET THE PREVIOUS MOUSE CO ORDINATES TO -1
void sliderMovingStopped()
{
    previousMx = -1;
    previousMy = -1;
}

void sliderBackgroundClickControl(int mx, int my)
{
    if(isRectangleClicked(mx, my, taskMenuSlider.backgroundX, taskMenuSlider.backgroundY, taskMenuSlider.handleX, taskMenuSlider.handleY))
    {
        taskMenuSlider.handleY -= (taskMenuSlider.sliderScrollableRangeTotal)/10;

        if(taskMenuSlider.handleY <= 0)
        {
            taskMenuSlider.handleY = 0;
        }
        else if((taskMenuSlider.handleY + taskMenuSlider.handleH) >= WINDOW_HEIGHT)
        {
            taskMenuSlider.handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow();
    }
    else if(isRectangleClicked(mx, my, taskMenuSlider.handleX, taskMenuSlider.handleY + taskMenuSlider.handleH, taskMenuSlider.handleW, WINDOW_HEIGHT-(taskMenuSlider.handleY + taskMenuSlider.handleH)))
    {
        taskMenuSlider.handleY += (taskMenuSlider.sliderScrollableRangeTotal)/10;

        if(taskMenuSlider.handleY <= 0)
        {
            taskMenuSlider.handleY = 0;
        }
        else if((taskMenuSlider.handleY + taskMenuSlider.handleH) >= WINDOW_HEIGHT)
        {
            taskMenuSlider.handleY = WINDOW_HEIGHT - SLIDER_HANDLE_H;
        }

        updateWindow();
    }
}

// DRAWS THE SLIDER BACKGROUND AND HANDLE
void drawSlider(Slider *slider)
{
    // SLIDER BG
    iSetColor(SLIDER_BG_COLOR_R, SLIDER_BG_COLOR_G, SLIDER_BG_COLOR_B);
    iFilledRectangle(taskMenuSlider.backgroundX, taskMenuSlider.backgroundY, taskMenuSlider.backgroundW, taskMenuSlider.backgroundH);

    // SLIDER HANDLE
    iSetColor(SLIDER_HANDLE_COLOR_R, SLIDER_HANDLE_COLOR_G, SLIDER_HANDLE_COLOR_B);
    iFilledRectangle(taskMenuSlider.handleX, taskMenuSlider.handleY, taskMenuSlider.handleW, taskMenuSlider.handleH);
}
