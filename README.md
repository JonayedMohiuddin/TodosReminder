# To-Do Reminder with iGraphics Library

This project is a graphical application developed using the **iGraphics** library, designed as a reminder tool for managing daily tasks. Users can add, remove, and manage tasks visually through an intuitive interface.

---

## Features

### Core Functionalities:
- **Add Tasks**: Create new tasks with customizable titles and details.
- **Remove Tasks**: Delete tasks easily.
- **Task Management**:
  - Mark tasks as done or favorite.
  - Set deadlines and view task creation time.
  - Save and load tasks from files for persistence.
- **Task Details**: View or edit detailed descriptions of tasks.
- **Alarms**: Notify users when tasks are overdue.

### Advanced Capabilities:
- **Customizable Input**: Includes movable cursor for text editing.
- **Dynamic Interface**: Features hoverable buttons and a window slider for task navigation.
- **Auto-Save**: Tasks are automatically saved periodically to prevent data loss.

---

## File Structure

### `iMain.cpp`:
- Entry point of the application.
- Implements task management logic and graphical rendering.
- Defines various constants, functions, and UI components.

### `iGraphics.h`:
- Header file for the iGraphics library.
- Provides essential graphics rendering functions like drawing shapes, handling mouse and keyboard events, and displaying images.

---

## How to Run

### Setup Environment:
1. Ensure you have the necessary dependencies to build and run OpenGL-based applications on your system.
2. Install the iGraphics library.

### Compile and Run:
- Use an IDE like Code::Blocks or Visual Studio, or compile directly via a terminal:
  ```sh
  g++ iMain.cpp -o ToDoReminder -lGL -lGLU -lglut
  ./ToDoReminder

### Special Notes
- **Platform**: The project is designed for Windows but can be adapted to other platforms with OpenGL support.
- **Assets**: Ensure the assets/ directory (containing images like buttons and backgrounds) is correctly placed in the same directory as the executable.
- **Customizations**:
  - The task limit and default settings can be adjusted in iMain.cpp.
  - Visual styles can be modified by editing associated assets.
 
