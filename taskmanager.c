#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 300
int ID = 1;

struct Task 
{
    int ID;
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    struct task *next;    
};

struct Task *add_task (struct Task *list);
struct Task *delete_task (struct Task *list);
struct Task *update_task (struct Task *list);
struct Task *clear_list (struct Task *list, char input[]);
void print_list (struct Task *list);
void readline(char string[], int n);

int main() 
{
    char input;

    struct Task *task_list = NULL;
    printf("Travis's Task Manager\n\n");
    printf("Operations list:\nA - Add task\nD - Delete task\nU - Update task\nC - Clear task list\nP - Print task list\nQ - Quit\n\n");
    for (;;) 
    {

        printf("Enter operation code: ");
        scanf("%c", &input);


        while(getchar() != '\n');


        if ((input >= 'A') && (input <= 'Z')) 
        { 
			input = input - 'A' + 'a';
        }
    
        switch (input) 
        {
        case ('a'):
            task_list = add_task(task_list);
            break;

        case('d'):
            task_list = delete_task(task_list);
            break;

        case('u'):
            task_list = update_task(task_list);
            break;

        case('p'):
            print_list(task_list);
            break;     

        case('c'):
            task_list = clear_list(task_list, input);
            break;

        case('q'):
            clear_list(task_list, input);
            printf("Goodbye.");
            return 0;

        default:
            printf("Illegal input.");
        }
        printf("\n");

    }
}

struct Task *add_task (struct Task *list) //COMPLETE
{
    struct Task *new_task = malloc(sizeof(struct Task));

    printf("Enter task name: ");
    readline(new_task->name, MAX_NAME_LEN);
    printf("Enter task description: ");
    readline(new_task->description, MAX_DESC_LEN);
    new_task->ID = ID;
    new_task->next = NULL;

    struct Task *current = list;
    struct Task *head = list;

    if (current != NULL)
    {

        for (current = list; current->next != NULL;current = current->next);
        current->next = new_task;
        ID++;
        return head;
    }
    else
    {
        current = new_task;
        ID++;
        return current;
    }


}

struct Task *delete_task (struct Task *list) //COMPLETE
{
    int ID_delete;
    char s_delete[3];
    struct Task *head = list;
    struct Task *current = list;
    struct Task *prev = NULL;


    if(current != NULL)
    {
        printf("Enter Task ID: ");
        readline(s_delete, 3);
        ID_delete = atoi(s_delete);

        for (current = list, prev = NULL; current->ID != ID_delete && current->next != NULL; prev = current, current = current->next); //iterates through the entire list, stopping if a task matching the requested ID exists.

        if (current->ID == ID_delete)
        {
            if (head == current)
            { 
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("task %d Deleted. \nNew list now contains the following: \n", ID_delete);
            print_list(head);
        }

        else
        {
            printf("Task not found.");
        }

        return head;
    }
    
    else
    {
        printf("There are no tasks to be deleted.");
        return NULL;
    }

}

struct Task *update_task (struct Task *list) //COMPLETE

{
    int ID_Update;
    char s_Update[3];
    char new_name[MAX_NAME_LEN];
    char new_desc[MAX_DESC_LEN];


    struct Task *current = list;
    struct Task *head = list;
    if (current != NULL)
    {

        printf("Enter Task ID: ");
        readline(s_Update, 3);
        ID_Update = atoi(s_Update);
        for (current = list; current->ID != ID_Update && current->next != NULL; current = current->next); //iterates until it reaches the end of the list or finds the matching task
        
        if ( current->ID == ID_Update)
        {
            printf("Enter new task name:");
            readline(new_name, MAX_NAME_LEN);
            strcpy(current->name, new_name);
            printf("Enter new task description: ");
            readline(new_desc, MAX_DESC_LEN);
            strcpy(current->description, new_desc);
            
        }
        else
        {
            printf("Task not found.");
        }
        return head;
    }
    else
    {
        printf("There are no tasks to update.");
        return NULL;
    }
}

struct Task *clear_list(struct Task *list, char input[]) //COMPLETE
{

    if (list != NULL)
    {
        struct Task *current = list;
        struct Task *next_node = current->next;


            free(current);
            while (next_node != NULL)
            {
                current = next_node;
                next_node = next_node->next;
                free(current);
            }
        

        printf("All tasks have been cleared. ");
    }
    else
    {
        if (input == 'q')
        {
            return NULL;
        }
        printf("The list is empty. ");
    }
    return NULL;
}

void print_list(struct Task *list) //COMPLETE, WIP OPTIONAL DESIGN FEATURES
{ //FEATURE: print it as a table that includes task ID, Task Name, Task Description

    struct Task *current = list;

    if (current != NULL)
    {
        printf("ID\tName\n");
        for(current = list; current != NULL; current = current->next)
        {
            printf("%d\t%s\t%s\n", current->ID, current->name, current->description);
        }
    }
    
    else
    {
        printf("There are no tasks.");
    }


}

void readline(char string[], int n) //COMPLETE
{
    int ch, i = 0;
    while(isspace(ch = getchar())); 

    string[i++] = ch;
    while((ch=getchar()) != '\n')
    {
        if (i < n)
        {
            string[i++] = ch;
        }
    }
    string[i] = '\0';
}
