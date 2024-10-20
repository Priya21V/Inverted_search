#ifndef MAIN_H
#define MAIN_H

#define SUCCESS 1
#define FAILURE 0
#define LIST_EMPTY -1
/*Structure for main node*/
typedef struct main
{
    int file_count;
    char word[50];
    struct main *mlink;
    struct sub *slink;
}Main_node;

/*Structure for sub node*/
typedef struct sub
{
    int wor_count;
    char file_name[50];
    struct sub *sublink;
}Sub_node;

/*Structure for storing file names*/
typedef struct file
{
    char file[50];
    struct file *link;
}File_t;


/*Function prototypes*/

int read_and_validate(int argc,char *argv[],File_t **head);
int find_index(char *word);
int create_database(Main_node *arr[28],File_t **head);
void display_database(Main_node *arr[28]);
int search_database(Main_node *arr[28]);
int save_database(Main_node *arr[28]);
int update_database(Main_node *arr[28],File_t **head);

#endif