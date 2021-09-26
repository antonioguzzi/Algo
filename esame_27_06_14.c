#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME 101
#define MAXNUMB 21

struct n {
    char* name;
    char* number;
    struct n *next;
};
typedef struct  n node;
typedef node* nodeptr;

void insert(nodeptr *list, char* name, char* number);
int hash(int dim_table, char* name);
void print_table (nodeptr *table, int dim_table);
node** init_table(int dim_table, int num_record);
void print_position_list(nodeptr list);

int main() {
    int num_record;
    int dim_table;
    int position;
    node **table = NULL;

    scanf("%d", &num_record);
    dim_table = (num_record * 2);
    table = init_table(dim_table,num_record);
    scanf("%d", &position);
    //print_table(table,dim_table);
    print_position_list(table[position]);

    return 0;
}

int hash(int dim_table, char* name){
    int sum = 0;
    int i = 0;
    while(name[i] != '\0'){
        if(name[i] != '\0')
            sum += (int)name[i];
        i++;
    }
    return sum % dim_table;
}

node** init_table(int dim_table, int num_record) {
    char string_name[MAXNAME];
    char string_numb[MAXNUMB];
    int h;
    node** table = malloc(sizeof(node*)*dim_table);
    for(int i = 0; i < dim_table; i++)
        table[i] = NULL;
    for(int i = 0; i < num_record; i++) {
        scanf("%s", string_name);
        scanf("%s", string_numb);
        h = hash(dim_table,string_name);
        insert(&table[h],string_name,string_numb);
    }
    return table;
}

void insert(nodeptr *list, char* name, char* number) {
    nodeptr new_node = malloc(sizeof(node));
    if (new_node != NULL) {
        new_node->name = malloc(sizeof(char)*(strlen(name)+1));
        strcpy(new_node->name,name);
        new_node->number = malloc(sizeof(char)*(strlen(number)+1));
        strcpy(new_node->number,number);
        new_node->next = NULL;

        nodeptr pre = NULL;
        nodeptr curr = *list;
        while(curr != NULL && strcmp(curr->name,new_node->name) <= 0) {
            pre = curr;
            curr = curr->next;
        }
        if (pre == NULL) {
            new_node->next = *list;
            *list = new_node;
        } else {
            pre->next = new_node;
            new_node->next = curr;
        }
    }
    return;
}

void print_table (nodeptr *table, int dim_table){
    nodeptr tmp;
    printf("tabella hash:\n");
    for(int i = 0; i < dim_table; i++) {
        tmp = table[i];
        printf("%d -> ", i);
        if (tmp == NULL)
            printf("NULL\n");
        else {
            while(tmp != NULL) {
                printf("%s %s\t", tmp->name, tmp->number);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    return;
}

void print_position_list(nodeptr list){
    nodeptr tmp = list;
    while(tmp != NULL){
        printf("%s %s\n", tmp->name, tmp->number);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}
