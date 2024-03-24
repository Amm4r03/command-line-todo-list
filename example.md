![banner](assets/demo%20banner.png)

# demo
1. run the executable file
2. the CLI will open up with the main menu visible
3. feel free to try out the various options available
4. when quitting the program, the code saves your tasks in a task file that can be loaded up the next time you run the program once again

## screenshots
In this demo, we will be going through the entire application and try out all the available functionalities in the app
![pic1](assets/screenshots/1.JPG)
on starting the app, you will be asked if you want to load tasks from previous run, since this is our first time running the program, we should go with entering 'n' (you can try running 'y' as well but that will return in an error and the app will proceed with a fresh list only)

next, we will be greeted with the main menu and we'll be prompted to enter our response

![p2](assets/screenshots/2-addTask.JPG)
we can write in a description for the task and assign a priority value to the task

the code will notify that the task has been added to the current tasks list

next, we can view the tasks in our list
![p3](assets/screenshots/3-displayTasks.JPG)

this displays the tasks with an id, along with their priority level specified

lets say you are now done with a certain task, you can then remove it using command number 2 `remove a task`.

![p4](assets/screenshots/4-removeTask.JPG)
this will remove the task from the your current list of active tasks (here's something that you can check : try running display tasks again to see count of active tasks and total tasks)

you can also view tasks according to their priority level, the tasks are printed from priority 2 (LOW) to priority 0 (HIGH)
![p5](assets/screenshots/5-viewTasksByPriority.JPG)

the user can also view tasks for any single priority as well as shown below
![p6](assets/screenshots/6-viewSpecificPriorityTasks.JPG)

the user can also view their stats for tasks completed and the priority-wise task division
![p7](assets/screenshots/7-taskStats.JPG)

before exiting, the program saves the currently active tasks in a `.txt` file which can be loaded later if required by the user
![p8](assets/screenshots/8-exit.JPG)

this is what the program saves in the `.txt` file. The text before the comma delimiter is the task description and the number is the priority level of that task
![p9](assets/screenshots/9-tasksSavedInFile.JPG)

now that we load the program again, we are asked if we want to load previously added tasks, where we now enter `y`
![p10](assets/screenshots/10-loadSavedTasksFromFile.JPG)
this adds the tasks to the current task list in the program which can be used by the user

---