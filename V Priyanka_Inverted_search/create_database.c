#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
/*function to validate the command line arguments*/
int read_and_validate(int argc, char *argv[], File_t **head)
{
    if (argc < 2)
    {
        return FAILURE;
    }

    for (int i = 1; i < argc; i++) 
    {
        char *ptr = strstr(argv[i], ".");  //checking file has . or not
        if (ptr == NULL)
        {
            printf("INFO: %s is an invalid file\n", argv[i]);
            continue;
        }

        if (strcmp(ptr, ".txt") != 0) //checking file has .txt extension or not
        {
            printf("ERROR: %s does not contain .txt extension\n", argv[i]);
            continue;
        }
        /*Opening the file for checking file is empty or not*/
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("ERROR: Failed to open %s file\n", argv[i]);
            continue;
        }   
        /*Making the file pointer to point to end of the file*/
        fseek(fptr, 0, SEEK_END);

        /*Calculating the length of the file*/
        int len = ftell(fptr);
        fclose(fptr); 

        /*checking whether the file is empty or not*/ 
        if (len == 0)
        {
            printf("INFO: %s file is empty\n", argv[i]);
            continue;
        }
        /*Creating new node*/
        File_t *new = malloc(sizeof(File_t));
        if (new == NULL)
        {
            printf("ERROR: Failed to create new node\n");
            continue;
        }
        /*Copying the file name*/
        strcpy(new->file, argv[i]);
        new->link = NULL;

        if (*head == NULL)
        {
            *head = new;
        }
        else
        {
            File_t *temp = *head;
            File_t *prev=NULL;
            int duplicate=0;
            /*checking whether the file name already present in the list*/
            while (temp)
            {
                if(strcmp(temp->file,argv[i])==0)
                {
                    printf("INFO: %s file is duplicate file\n",argv[i]);
                    duplicate=1;
                }
                prev=temp;
                temp = temp->link;
            }
            if(duplicate)
            {
                continue;
            }
            prev->link = new;
        }

        printf("INFO: %s file added to the list\n", argv[i]);
    }

    return SUCCESS;
}
/*Function to find the index of the file*/
int find_index(char *word)
{
    char ch = word[0];
    if (ch >= 'A' && ch <= 'Z') /*checking whether the character is uppercase or not*/
    {
        return ch - 'A';
    }
    else if (ch >= 'a' && ch <= 'z') /*checking whether the character is lowercase or not*/
    {
        return ch - 'a';
    }
    else if (!isalnum(ch) && !isspace(ch)) /*checking whether the character is special character or not*/
    {
        return 26;
    }
    else if (ch >= '0' && ch <= '9')
    {
        return 27;
    }
}

/*Function to create database*/
int create_database(Main_node *arr[28], File_t **head)
{
    if(*head==NULL)  //checking whether list is empty or not
    {
        return LIST_EMPTY;
    }
    File_t *temp = *head;
    
    /*Printing the file names*/
    while (temp)
    {
        printf("%s->", temp->file);
        temp = temp->link;
    }
    printf("NULL\n");
    
    File_t *temp_list = *head;
    while (temp_list) //traversing till last node of list of file names
    {
        FILE *fptr = fopen(temp_list->file, "r");  //opening file
        if (fptr == NULL)
        {
            printf("ERROR:Failed to open %s file\n", temp_list->file);
            return FAILURE;
        }
        char word[50];
        while (fscanf(fptr, "%s", word) != EOF)  //getting each word from file till end of the file
        {
            int index = find_index(word);  //finding the index of tne file

            if (arr[index] == NULL)  //checking whether array is empty or not
            {
                /*Creating main node and adding the data and linking it to the array*/
                Main_node *new_main = malloc(sizeof(Main_node));
                if (new_main == NULL)
                {
                    printf("ERROR:Failed to create new node for main node\n");
                    return FAILURE;
                }
                new_main->file_count = 1;
                strcpy(new_main->word, word);
                new_main->mlink = NULL;

               /*Creating sub node and adding data and linking it to the main node*/
                Sub_node *new_sub = malloc(sizeof(Sub_node));
                if (new_sub == NULL)
                {
                    printf("ERROR:Failed to create new node for sub node\n");
                    return FAILURE;
                }
                new_sub->wor_count = 1;
                strcpy(new_sub->file_name, temp_list->file);
                new_sub->sublink = NULL;
                new_main->slink = new_sub;  

                arr[index] = new_main;
            }
            else
            {
                
                Main_node *temp_main = arr[index];
                int word_present = 0;
                /*checking whether the word is already present or not*/
                while (temp_main)
                {
                    if (strcmp(temp_main->word, word) == 0)
                    {
                        word_present = 1;
                        break;
                    }
                    temp_main = temp_main->mlink;
                }
                if (word_present)  //if word present checking whether it is same file or not
                {
                    Sub_node *temp_sub = temp_main->slink;
                    int file_present = 0;
                    while (temp_sub)
                    {
                        if (strcmp(temp_sub->file_name, temp_list->file) == 0)
                        {
                           
                            temp_sub->wor_count++;
                            file_present = 1;
                            break;
                        }
                        temp_sub = temp_sub->sublink;
                    }
                    if (!file_present)  //if it is not same file means adding filename with subnode
                    {
                        
                        Sub_node *new_sub = malloc(sizeof(Sub_node));
                        if (new_sub == NULL)
                        {
                            printf("ERROR:Failed to create new node for sub node\n");
                            return FAILURE;
                        }
                        new_sub->wor_count = 1;
                        strcpy(new_sub->file_name, temp_list->file);
                        new_sub->sublink = temp_main->slink;
                        temp_main->slink = new_sub;
                        temp_main->file_count++;  //incrementing the file count
                    }
                }
                else   //if word is not present creating main node and sub node and linking it to the array
                {
                    
                    Main_node *new_main = malloc(sizeof(Main_node));
                    if (new_main == NULL)
                    {
                        printf("ERROR:Failed to create new node for main node\n");
                        return FAILURE;
                    }
                    new_main->file_count = 1;
                    strcpy(new_main->word, word);
                    new_main->mlink = arr[index];    
                    Sub_node *new_sub = malloc(sizeof(Sub_node));
                    if (new_sub == NULL)
                    {
                        printf("Failed to create new node for sub node\n");
                        return FAILURE;
                    }
                    new_sub->wor_count = 1;
                    strcpy(new_sub->file_name, temp_list->file);
                    new_sub->sublink = NULL;
                    new_main->slink = new_sub;
                    arr[index] = new_main;
                }
            }
        }
        fclose(fptr);  
        temp_list = temp_list->link;  
    }
    return SUCCESS;
}

