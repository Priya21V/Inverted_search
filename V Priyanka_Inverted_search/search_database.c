#include <stdio.h>
#include <string.h>
#include "main.h"
/*Function to search data in the database*/
int search_database(Main_node *arr[28])
{
    char word[50];
    printf("Enter the word to search: ");  //reading word from the user
    scanf("%s", word);
    int index = find_index(word);  //finding index for given word
    Main_node *temp_main = arr[index];
    //traversing the index whether word is present or not
    while (temp_main)
    {
        if (strcmp(temp_main->word, word) == 0)
        {
            printf("[%2d] %-15s %5d file(s):", index, temp_main->word, temp_main->file_count);
            Sub_node *temp_sub = temp_main->slink;
            while (temp_sub)
            {
                printf("%6s File : %-20s : %5d time(s)", "", temp_sub->file_name, temp_sub->wor_count);
                temp_sub = temp_sub->sublink;
            }
            printf("->NULL\n");
            temp_main = temp_main->mlink;
            return SUCCESS;
        }
        temp_main = temp_main->mlink;
    }
    printf("INFO : %s is not found\n", word);
    return FAILURE;
}