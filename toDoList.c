// simple implementation of a todo list in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defined data type for priority of tasks
typedef enum priority {HIGH, MEDIUM, LOW} priority;

// structure for the task
typedef struct task {
    char description[100];
    priority priority;
    struct task* next;
} task;


task* head;

// declare total for count of all tasks (active and completed)
int totalTasks = 0;

// declare a variable to store number of tasks completed by user
int completed;

// declare counters for all tasks according to their priorities
int lowPr, medPr, highPr;

// declare heads for priority lists
task* lowHead;
task* medHead;
task* highHead;


// function prototype
int taskCount(void);
void printDashes(int length);
void printHyphens(int length);
task* createTask(char *descr, priority p);
void addTask(char* descr, priority p);
void addTaskToPriority(task** listHead, char* descr, priority p);
void removeTaskFromPriority(priority p, char* description);
void removeTask(void);

// prints asterisks for better readability of the console output
void printDashes(int length)
{
    printf("\n");
    for(int i = 0; i <= length; i++)
    {
        printf("* ");
    }
    printf("\n\n");
}

// prints hyphens for better readability of the console output
void printHyphens(int length)
{
    for(int i = 0; i <= length; i++)
    {
        printf("-");
    }
    printf("\n");
}

// return a task with a description pointing to NULL
task* createTask(char *descr, priority p)
{
    task* newTask = (task*) malloc(sizeof(task));
    strcpy(newTask->description, descr);
    newTask->priority = p;
    newTask->next = NULL;
    return newTask;
}

// adds tasks to the list
void addTask(char* descr, priority p)
{
    task* newTask = createTask(descr, p);

    totalTasks++;
    // add task to the priority linked list as well
    if (p == 0) addTaskToPriority(&highHead, descr, p);
    else if (p == 1) addTaskToPriority(&medHead, descr, p);
    else addTaskToPriority(&lowHead, descr, p);

    if (head == NULL)
    {
        head = newTask;
    }
    else
    {
        task* traverse = head;
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newTask;
    }
    printf("INFO : added task \"%s\" with priority %d to current tasks\n", descr, p);
    printDashes(20);
    return;
}

void addTaskToPriority(task** listHead, char* descr, priority p)
{
    task* newTask = createTask(descr, p);

    if (*listHead == NULL)
    {
        *listHead = newTask;
    }
    else
    {
        task* traverse = *listHead;
        while(traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = newTask;
    }
    return;
}


// when removing elements from the task list, we would have to remove them from the priority lists as well
// this function removes elements from the priority lists
// here we will remove the task from list by matching the description given from the remove function
// with the descriptions of tasks in our priority lists
void removeTaskFromPriority(priority p, char* description)
{
    task* traverse;
    task* prev = NULL;
    
    char key[100];
    strcpy(key, description);

    if (p == 0) traverse = highHead;
    if (p == 1) traverse = medHead;
    if (p == 2) traverse = lowHead;

    while (traverse != NULL && strcmp(traverse->description, key) == 0)
    {
        task* temp = traverse;
        traverse = traverse->next;
        if (p == 0) highHead = traverse;
        else if (p == 1) medHead = traverse;
        else if (p == 2) lowHead = traverse;
        free(temp);
    }

    while (traverse != NULL)
    {
        if (strcmp(traverse->description, key) == 0)
        {
            prev->next = traverse->next;
            task* temp = traverse;
            traverse = traverse->next;
            free(temp);
        }
        else
        {
            prev = traverse;
            traverse = traverse->next;
        }
    }
}

// remove task by index value
void removeTask(void)
{
    if (head == NULL)
    {
        printf("ERROR : no tasks in list\ncreate some tasks first to complete them!\n");
        return;   
    }
    int index;
    printf("enter the task number to be removed : ");
    scanf("%d", &index);

    char taskDescription[100];

    while (index > taskCount() || index < 1)
    {
        printf("ERROR : invalid index vaue, please try again\nenter the task number to be removed : ");
        scanf("%d", &index);
    }

    if (index == 1)
    {
        task* temp = head;
        head = head->next;
        strcpy(taskDescription, temp->description);
        removeTaskFromPriority(temp->priority, temp->description);
        free(temp);
    }
    else if(taskCount() == 1)
    {
        task* temp = head;
        head = NULL;
        strcpy(taskDescription, temp->description);
        removeTaskFromPriority(temp->priority, temp->description);
        free(temp);
    }
    else
    {
        index -= 1;
        task* traverse = head;
        int length = 0;
        while (length < index - 1)
        {
            traverse = traverse->next;
            length++;
        }

        task* temp = traverse->next;
        traverse->next = temp->next;

        strcpy(taskDescription, temp->description);

        removeTaskFromPriority(temp->priority, temp->description);
        free(temp);
    }
    completed++;
    printf("INFO : removed task %d (%s) from the list\n", index + 1, taskDescription);
    printDashes(20);
    return;
}

// returns total number of currently active tasks
int taskCount(void)
{
    int length = 0;
    task* traverse = head;
    while (traverse != NULL)
    {
        traverse = traverse->next;
        length++;
    }
    return length;
}

// counts the task wrt their priority values (assigns values to the global variables for each priority)
void taskCountByPriority(void)
{
    lowPr = 0;
    medPr = 0;
    highPr = 0;

    task* traverse = head;
    while(traverse != NULL)
    {
        if (traverse->priority == 0) highPr++;
        if (traverse->priority == 1) medPr++;
        if (traverse->priority == 2) lowPr++;

        traverse = traverse->next;
    }
}

// display the tasks in a tabular format
void displayTasks(void)
{
    if (head == NULL)
    {
        printf("ERROR : empty task list - create some tasks first\n");
        return;
    }

    printDashes(20);
    printf(" * * * \tCURRENT TASKS\t * * *\n");
    printf("#\t|\tDESCRIPTION\t|\tPRIORITY\n");
    printHyphens(55);
    task* traverse = head;
    int i = 1;
    while (traverse != NULL)
    {
        printf("%3d\t|\t%-15s\t|\t%d\n", i, traverse->description, traverse->priority);
        traverse = traverse->next;
        i++;
    }
    printf("\n\n");
    printf("current active tasks : %d\n", taskCount());
    printf("total tasks : %d\n\n", totalTasks);
    printDashes(20);
}

void displayWithHead(task** listHead)
{
    task* traverse = *listHead;
    printDashes(20);
    printf("* * * \tTASKS FROM PRIORITY %d\t * * *\n", traverse->priority);
    printf("#\t|\tDESCRIPTION\t|\tPRIORITY\n");
    printHyphens(55);
    int i = 1;

    while (traverse != NULL)
    {
        printf("%3d\t|\t%-15s\t|\t%d\n", i, traverse->description, traverse->priority);
        traverse = traverse->next;
        i++;
    }
    printf("\n\n");
    printDashes(20);
}

// show all tasks grouped by their priority level in tabular format
void showSeparateLists(void)
{
    if (lowHead == NULL && medHead == NULL && highHead == NULL)
    {
        printf("INFO : NO TASKS IN LIST - CREATE SOME TASKS FIRST\n");
        return;
    }

    if (lowHead != NULL) displayWithHead(&lowHead);
    else printf("INFO : NO TASKS WITH PRIORITY 2\n");

    if (medHead != NULL) displayWithHead(&medHead);
    else printf("INFO : NO TASKS WITH PRIORITY 1\n");

    if (highHead!= NULL) displayWithHead(&highHead);
    else printf("INFO : NO TASKS WITH PRIORITY 0\n");
    return;
}

// stats for fun
void showStats(void)
{
    printDashes(50);
    printf("\tTASK LIST STATS:\n");
    printf("*\t*\t*\t*\t*\n");
    printf("total tasks created : \t%d\n", totalTasks);
    printf("current active tasks :\t%d\n", taskCount());
    printf("completed tasks : \t%d\n\n", totalTasks - taskCount());
    
    printHyphens(20);

    printf("priority wise analysis of tasks\n");
    
    // returns updated figures
    taskCountByPriority();
    printf("low :\t%d\n", lowPr);
    printf("med :\t%d\n", medPr);
    printf("high :\t%d\n\n", highPr);

    printf("you have completed %0.2f %% of your tasks\n\n", (float) ((totalTasks - taskCount()) / ((float) (totalTasks))) * 100);

    printDashes(50);
}

// function to traverse the head and save tasks in a file to load later
void saveTaskToFile(const char* fileName)
{
    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("ERROR : can't open file for writing\n");
        return;
    }

    task* traverse = head;
    while (traverse != NULL)
    {
        fprintf(file, "%s, %d\n", traverse->description, traverse->priority);
        traverse = traverse->next;
    }
    fclose(file);
}

void loadTasksFromFile(const char* fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("ERROR : no previous tasks found\n");
        return;
    }

    char descr[100];
    int prio;
    while(fscanf(file," %[^,], %d", descr, &prio) == 2)
    {
        addTask(descr, (priority) prio);
    }
    fclose(file);
    return;
}

// main menu function for user input
void menu(void)
{
    printf("TO DO LIST\n\n");
    printf("***\tMAIN MENU\t***\n");
    printf("select an option : \n");
    printf("1 : create a task\n");
    printf("2 : remove a task\n");
    printf("3 : see current tasks\n");
    printf("4 : sort tasks by priority\n");
    printf("5 : see tasks of a single priority level\n");
    printf("6 : see your stats\n");
    printf("7 : exit\n");
    printf("enter your response : ");
}

int main()
{
    head = NULL;

    // declare all priority heads to be null as well
    lowHead = NULL; medHead = NULL; highHead = NULL;

    char fileChoice;
    printf("Do you want to load previously added tasks?\n(y/n) : ");
    scanf(" %c", &fileChoice);

    if (fileChoice == 'y' || fileChoice == 'Y')
    {
        loadTasksFromFile("tasks.txt");
        printf("INFO : loaded %d tasks\n", taskCount());
        printHyphens(30);
    }
    else
    {
        printf("INFO : starting from a blank to do list\n");
    }

    while (1)
    {
        int quit = 0;
        menu();
        int choice;
        scanf("%d", &choice);

        getchar();

        while(choice > 7 || choice < 1)
        {
            printf("ERROR : invalid option, please try again\n");
            menu();
            scanf("%d", &choice);
        }

        switch (choice)
        {
        case 1:
            char d[100];
            priority p;
            printf("enter task description : ");
            fgets(d, sizeof(d), stdin);
            d[strcspn(d, "\n")] = '\0';
            printf("enter task priority : (0 - HIGH, 1 - MEDIUM, 2 - LOW): ");
            scanf("%d", &p);
            getchar();
            addTask(d, p);
            break;

        case 2:
            removeTask();
            break;

        case 3:
            displayTasks();
            break;

        // view by priority
        case 4:
            showSeparateLists();
            break;

        // view single priority level
        case 5:
            int pr;
            printf("enter priority level to view tasks for : ");
            scanf("%d", &pr);

            while(pr > 2 || pr < 0)
            {
                printf("INFO - invalid input, please try again\n");
                printf("enter priority level : ");
                scanf("%d", &pr);
            }

            if (pr == 0 && highHead != NULL) displayWithHead(&highHead);
            else printf("INFO - NO TASKS IN LIST - ADD SOME TASKS FIRST\n"); break;

            if (pr == 1 && medHead != NULL) displayWithHead(&medHead);
            else printf("INFO - NO TASKS IN LIST - ADD SOME TASKS FIRST\n"); break;
            
            if (pr == 2 && lowHead != NULL) displayWithHead(&lowHead);
            else printf("INFO - NO TASKS IN LIST - ADD SOME TASKS FIRST\n"); break;

            break;

        // view stats
        case 6:
            showStats();
            break;

        // quit
        case 7:
            quit = 1;
            printf("INFO : saving tasks\n");
            saveTaskToFile("tasks.txt");
            printf("INFO : exiting program\n");
            break;
        
        default:
            break;
        }
        
        if (quit == 1)
        break;
    }
    return 0;
}