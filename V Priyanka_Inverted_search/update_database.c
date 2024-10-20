#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

/*Function to update data from a file to the database*/
int update_database(Main_node *arr[28],File_t **head)
{
    char back_up_file[50];
    printf("Enter the file name to update the database: ");  //reading file name from the user
    scanf("%s", back_up_file);
    
    /*Validating the file*/
    char *ptr = strstr(back_up_file, ".");
    if (ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("Please provide a .txt file\n");
        return FAILURE;
    }
    FILE *fptr = fopen(back_up_file, "r");
    if (fptr == NULL)
    {
        printf("Failed to open the file: %s\n", back_up_file);
        return FAILURE;
    }
    /*Checking whether it is a valid backup file or not*/
    char c = fgetc(fptr);
    if (c == '#')
    {
        fseek(fptr, -2, SEEK_END);
        if (fgetc(fptr) != '#')
        {
            printf("Please provide a valid backup file to update\n");
            fclose(fptr);
            return FAILURE;
        }
        rewind(fptr);
    }
    else
    {
        printf("Please provide a valid backup file to update\n");
        fclose(fptr);
        return FAILURE;
    }
    /*Redaing sentence from the file and updating it to database*/
    char sentence[100];
    while (fscanf(fptr, "%s", sentence) != EOF)
    {
        char *index = strtok(sentence, "#;");  //getting index from file
        if (index == NULL)
            break;
        int ind = atoi(index);  //converting index from string to integer
        char *word = strtok(NULL, "#;");// getting word from the user
        char *file_count = strtok(NULL, "#;");  //getting file count from the user
        int fc = atoi(file_count);  //converting file count from string to integer
        if (word == NULL || file_count == NULL)
        {
            printf("Invalid sentence format in the file\n");
            fclose(fptr);
            return FAILURE;
        }

        if (arr[ind] == NULL)  //checking arr[index] is null or not
        {
            /*Creating msin node and updating data and linking it to the array*/
            Main_node *new_main = malloc(sizeof(Main_node));
            if (new_main == NULL)
            {
                printf("Failed to create new node for main node\n");
                fclose(fptr);
                return FAILURE;
            }
            new_main->file_count = fc;
            strcpy(new_main->word, word);
            new_main->slink = NULL;
            new_main->mlink = NULL;
            /*creating sub nodes based on the file count times and linking them to the main node*/
            for (int i = 0; i < fc; i++)
            {
                char *file_name = strtok(NULL, "#;");  //getting file name from the file
                char *word_count = strtok(NULL, "#;");  //getting word count from the file
                int wc = atoi(word_count);  //converting word count to integer

                if (file_name == NULL || word_count == NULL)
                {
                    printf("Invalid file name or word count in the file\n");
                    fclose(fptr);
                    return FAILURE;
                }
                //checking the files which are given in the command line arguments are same in the back up file or not
                File_t *temp_head=*head;
                File_t *prev=NULL;
                if(temp_head!=NULL && strcmp(temp_head->file,file_name)==0)
                {
                    *head=temp_head->link;
                    free(temp_head);  //deallocating them if duplicates found
                }
                while(temp_head !=NULL && strcmp(temp_head->file,file_name)!=0)  //traversing till last node or same file name found
                {
                   
                    prev=temp_head;
                    temp_head=temp_head->link;
                }
                if(temp_head!=NULL)
                {
                    prev->link=temp_head->link;
                    free(temp_head); //deallocating them if duplicates found
                }
                /*creating sub node for file names and updating data and linking them to main node*/
                Sub_node *new_sub = malloc(sizeof(Sub_node));
                if (new_sub == NULL)
                {
                    printf("Failed to create new node for sub node\n");
                    fclose(fptr);
                    return FAILURE;
                }
                new_sub->wor_count = wc;
                strcpy(new_sub->file_name, file_name);
                new_sub->sublink = new_main->slink;
                new_main->slink = new_sub;
            }
            arr[ind] = new_main;
        }
        else  //if in the arr[index] nodes already present , new main node and sub node is inserting at first of the list
        {

            Main_node *new_main = malloc(sizeof(Main_node));
            if (new_main == NULL)
            {
                printf("Failed to create new node for main node\n");
                fclose(fptr);
                return FAILURE;
            }
            new_main->file_count = fc;
            strcpy(new_main->word, word);
            new_main->mlink = arr[ind];
            for (int i = 0; i < fc; i++)
            {
                char *file_name = strtok(NULL, "#;");
                char *word_count = strtok(NULL, "#;");
                int wc = atoi(word_count);

                if (file_name == NULL || word_count == NULL)
                {
                    printf("Invalid file name or word count in the file\n");
                    fclose(fptr);
                    return FAILURE;
                }
                File_t *temp_head=*head;
                File_t *prev=NULL;
                if(temp_head!=NULL && strcmp(temp_head->file,file_name)==0)
                {
                    *head=temp_head->link;
                    free(temp_head);
                }
                while(temp_head !=NULL && strcmp(temp_head->file,file_name)!=0)
                {
                   
                    prev=temp_head;
                    temp_head=temp_head->link;
                }
                if(temp_head!=NULL)
                {
                    prev->link=temp_head->link;
                    free(temp_head);
                }
                Sub_node *new_sub = malloc(sizeof(Sub_node));
                if (new_sub == NULL)
                {
                    printf("Failed to create new node for sub node\n");
                    fclose(fptr);
                    return FAILURE;
                }
                new_sub->wor_count = wc;
                strcpy(new_sub->file_name, file_name);
                new_sub->sublink = new_main->slink;
                new_main->slink = new_sub;
            }
            arr[ind] = new_main;
        }
    }

    fclose(fptr);
    return SUCCESS;
}
