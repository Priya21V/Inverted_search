#include<stdio.h>
#include <string.h>
#include "main.h"
/*Function to save the data to database*/
int save_database(Main_node *arr[28])
{
    char file_name[50];
    printf("Enter the file name: ");  //reading file name from the user
    scanf("%s",file_name);
    //validating file name
    char *ptr=strstr(file_name,".");
    if(ptr==NULL)
    {
        printf("Please provide .txt file\n");
        return FAILURE;
    }
    if(strcmp(ptr,".txt")!=0)
    {
        printf("Please provide .txt file\n");
        return FAILURE;
    }

    /*Opening the file in write mode*/
    FILE *fptr=fopen(file_name,"w");
    if(fptr==NULL)
    {
        printf("Failed to open %s file\n",file_name);
        return FAILURE;
    }
    /*Writing to the file in #index;word;file_count;file name:word_count# format*/
    for(int i=0; i<28; i++)
    {
        if(arr[i]!=NULL)
        {
            Main_node *temp_main = arr[i]; 
            while (temp_main)
            {
                fprintf(fptr,"#%d;",i);
                
                fprintf(fptr,"%s;%d;", temp_main->word, temp_main->file_count);
                Sub_node *temp_sub = temp_main->slink; 
                while (temp_sub)
                {
                    fprintf(fptr,"%s;%d;", temp_sub->file_name, temp_sub->wor_count);
                    temp_sub = temp_sub->sublink;
                }
                fprintf(fptr,"%c\n",'#');

                temp_main = temp_main->mlink;
            }
            
        }
        
    }
    fclose(fptr);
    return SUCCESS;
}