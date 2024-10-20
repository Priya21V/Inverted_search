/*
Name        : V Priyanka
Date        : 25/09/2024
Description : Inverted Search Project
*/
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
    File_t *head = NULL;
    Main_node *arr[28] = {NULL};
    read_and_validate(argc, argv, &head); // function call for validating command line arguments
    if (head == NULL)                     // checking whether valid files are passed in the command line arguments
    {
        printf("Usage : ./a.out <.txt file> [.txt file] [.txt file]\n");
        return FAILURE;
    }
    File_t *temp = head;
    printf("\n");
    while (temp)
    {
        printf("%s->", temp->file); // printing the validated file names
        temp = temp->link;
    }
    printf("NULL\n");
    int choice;
    int create = 0;
    int update = 0;
    while (1)
    {
        printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\n");
        printf("Enter the option: ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if (create == 0)
            {
                int res = create_database(arr, &head);  //function call to create database
                if (res == SUCCESS)
                {
                    printf("INFO : Created Database Successfully\n");
                    create = 1;
                }
                else if (res == LIST_EMPTY)
                {
                    printf("INFO : Database created already\n");
                }
            }
            else
            {
                printf("INFO : Database created already\n");
            }
            break;
        case 2:
            display_database(arr);  //function call to display database
            break;
        case 3:
            search_database(arr);   //function call to search database
            break;
        case 4:
            if (save_database(arr) == SUCCESS)  //function call to save database
            {
                printf("INFO : Database saved to file successfully\n");
            }
            else
            {
                printf("ERROR : Error in saving file\n");
            }
            break;
        case 5:
            if (create == 0 && update == 0)   //checking whether the data base is already upadted or created
            {
                if (update_database(arr, &head) == SUCCESS)  //function call to update database
                {
                    printf("INFO : Database updated to file successfully\n");
                    update = 1;
                }
                else
                {
                    printf("Error in Updating database\n");
                }
            }
            else
            {
                printf("INFO : Database already created\n");
            }
            break;
        case 6:
            printf("INFO : Exiting\n");  
            return 0;
            break;
        default:
            printf("Invalid Choice...!\n");
        }
    }
}