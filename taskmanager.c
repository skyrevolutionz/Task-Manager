#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 300
int ID = 1; //Global ID variable for task ID incrementation upon adding task

struct Task //Defines Task structure for linked list
{
    int ID;
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    struct task *next;    
};

//Prototype definitions
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

        input = tolower(input); //Handles uppercase letters

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
            clear_list(task_list, input); //Frees all memory before program close to avoid memory leak
            printf("Goodbye.");
            return 0;

        default:
            printf("Illegal input.");
        }
        printf("\n");

    }
}

struct Task *add_task (struct Task *list) //Adds tasks to the list
{
    struct Task *new_task = malloc(sizeof(struct Task)); //Create node to store in the list

    printf("Enter task name: ");
    readline(new_task->name, MAX_NAME_LEN); //Assigns user input into the node's variables
    printf("Enter task description: ");
    readline(new_task->description, MAX_DESC_LEN);
    new_task->ID = ID;
    new_task->next = NULL; //Ensuring all values of node are defined

    struct Task *current = list;
    struct Task *head = list;

    if (current != NULL) 
    {

        for (current = list; current->next != NULL;current = current->next); //Increments to the end of the list, adds the node, then returns the address of the first node
        current->next = new_task;
        ID++;
        return head;
    }
    else //If the list is empty, the node is appended to the beginning of the list
    {
        current = new_task;
        ID++;
        return current;
    }


}

struct Task *delete_task (struct Task *list) //Deletes a given task if its unique ID exists
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
        ID_delete = atoi(s_delete); //To avoid crashes during assignment, had to ATOI
        for (current = list, prev = NULL; current->ID != ID_delete && current->next != NULL; prev = current, current = current->next); //iterates through the list, stopping upon ID match or EOL

        if (current->ID == ID_delete) 
        {
            if (head == current) //If the ID matches the first node in the list, ensure there is a pointer referencing the next point in memory (whether it is another node or NULL) before freeing memory
            { 
                head = current->next;
            }
            else //If the ID matches an element that is not the first, link previous and next node, free current node's memory
            {
                prev->next = current->next; 
            }

            free(current);
            printf("task %d Deleted. \nNew list now contains the following: \n", ID_delete);
            print_list(head);
        }

        else //Handles ID not found in list
        {
            printf("Task not found.");
        }

        return head; 
    }
    
    else //Handles deleting tasks when list is empty
    {
        printf("There are no tasks to be deleted.");
        return NULL;
    }

}

struct Task *update_task (struct Task *list) //Updates a given task if its unique ID exists

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
        ID_Update = atoi(s_Update); //To avoid crashes during assignment, had to ATOI
        
        for (current = list; current->ID != ID_Update && current->next != NULL; current = current->next); //Iterates until it reaches the end of the list or finds the matching task
        
        if ( current->ID == ID_Update) //Assigns updated task name and description to the ID-matched node 
        {
            printf("Enter new task name:");
            readline(new_name, MAX_NAME_LEN);
            strcpy(current->name, new_name); 
            printf("Enter new task description: ");
            readline(new_desc, MAX_DESC_LEN);
            strcpy(current->description, new_desc);
            
        }
        else //Handles ID not being found in list
        {
            printf("Task not found.");
        }
        return head;
    }
    else //Handles updating tasks when list is empty
    {
        printf("There are no tasks to update.");
        return NULL;
    }
}

struct Task *clear_list(struct Task *list, char input[]) //Clears the list
{

    if (list != NULL)
    {
        struct Task *current = list;
        struct Task *next_node = current->next;


            free(current);
            while (next_node != NULL) //handles list being bigger than one node.
            {
                current = next_node;
                next_node = next_node->next;
                free(current);
            }
        

        printf("All tasks have been cleared. ");
    }

    else //Handles clearing an empty list
    {
        if (input == 'q') //Handles "The list is empty." being printed if quitting the program with an empty list
        {
            return NULL;
        }
        printf("The list is empty. ");
    }
    return NULL;
}

void print_list(struct Task *list) //Iterates over the list, printing every task's information
{ 

    struct Task *current = list;

    if (current != NULL)
    {
        printf("ID\tNAME\n");
        for(current = list; current != NULL; current = current->next) 
        {
            printf("%d\t%s\t%s\n", current->ID, current->name, current->description);
        }
    }
    
    else //Handles printing an empty list
    {
        printf("There are no tasks.");
    }


}

void readline(char string[], int n) //Handles prior input buffer issues 
{
    int ch, i = 0;
    while(isspace(ch = getchar()));  //Skips all possible whitespace until first non-whitespace character is met

    string[i++] = ch; 
    while((ch=getchar()) != '\n') //Assigns all characters excluding newline character to string array
    {
        if (i < n)
        {
            string[i++] = ch;
        }
    }
    string[i] = '\0'; //Closes string by null terminating
}
