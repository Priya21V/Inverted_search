#include<stdio.h>
#include "main.h"

/*Function to display the database*/
void display_database(Main_node *arr[28])
{
    printf("\nDisplaying the words and their files:\n");
    for (int i = 0; i < 28; i++)  
    {
        if (arr[i] != NULL)
        {
            Main_node *temp_main = arr[i]; 
            while (temp_main)
            {
                printf("[%2d] %-15s %5d file(s):", i, temp_main->word, temp_main->file_count);
                Sub_node *temp_sub = temp_main->slink; 
                while (temp_sub)
                {
                    printf("%6s File : %-20s : %5d time(s)", "",temp_sub->file_name, temp_sub->wor_count);
                    temp_sub = temp_sub->sublink;
                }
                printf("->NULL\n");
                temp_main = temp_main->mlink;
            }
        }
    }
}
