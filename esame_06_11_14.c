#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME 101

struct n {
    char* name;
    int value;
    struct n *next;
};
typedef struct  n node;
typedef node* nodeptr;

void insert(nodeptr *list, char* name, int val);
int hash(int dim_table, char* name);
node** init_table(int dim_table, int num_record);
void print_table (nodeptr *table, int dim_table);
nodeptr search(nodeptr list, char* name);
node* init_array(int num_record, node** table, int dim_table);
int compare(const void* a, const void* b);

int main() {
    int num_record;
    int dim_table;
    node **table = NULL;
    node* array;

    if(scanf("%d", &num_record) != 1 || num_record <= 0)
        exit(0);
    dim_table = (num_record * 2);
    table = init_table(dim_table,num_record);
    array = init_array(num_record,table,dim_table);
    qsort(array,num_record,sizeof(node),compare);

    if(strcmp(array[14].name,"null") == 0) {
        int i = 0;
        while(strcmp(array[i].name,"null") != 0) {
            printf("%s\n",array[i].name);
            i++;
        }
    } else {
        for(int i = 0; i < 15; i++)
            printf("%s\n",array[i].name);
    }

    free(array);
    free(table);
    return 0;
}

int hash(int dim_table, char* name) {
    int sum = 0;
    int i = 0;
    while(name[i] != '\0') {
        if(name[i] != '\0')
            sum += (int)name[i];
        i++;
    }
    return sum % dim_table;
}

nodeptr search(nodeptr list, char* name) {
    nodeptr tmp = list;
    while(tmp != NULL) {
        if(strcmp(name,tmp->name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node** init_table(int dim_table, int num_record) {
    char string_name[MAXNAME];
    int val;
    int h;
    nodeptr tmp;
    node** table = malloc(sizeof(node*)*dim_table);

    for(int i = 0; i < dim_table; i++)
        table[i] = NULL;
    for(int i = 0; i < num_record; i++) {
        scanf("%s", string_name);
        scanf("%d", &val);
        h = hash(dim_table,string_name);
        tmp = search(table[h],string_name);
        if(tmp == NULL)
            insert(&table[h],string_name,val);
        if(tmp != NULL && tmp->value < val)
            tmp->value = val;
    }
    return table;
}

void insert(nodeptr *list, char* name, int val) {
    nodeptr new_node = malloc(sizeof(node));
    if (new_node != NULL) {
        new_node->name = malloc(sizeof(char)*(strlen(name)+1));
        strcpy(new_node->name,name);
        new_node->value = val;
        new_node->next = *list;
        *list = new_node;
    }
    return;
}

void print_table (nodeptr *table, int dim_table) {
    nodeptr tmp;
    printf("tabella hash:\n");
    for(int i = 0; i < dim_table; i++) {
        tmp = table[i];
        printf("%d -> ", i);
        if (tmp == NULL)
            printf("NULL\n");
        else {
            while(tmp != NULL) {
                printf("%s(%d)\t", tmp->name, tmp->value);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    return;
}

node* init_array(int num_record, node** table, int dim_table) {
    node* array = malloc(sizeof(node)*num_record);
    nodeptr tmp;
    int j = 0;
    for(int i = 0; i < num_record; i++) {
        array[i].name = malloc(sizeof(char)*MAXNAME);
        strcpy(array[i].name, "null");
        array[i].value = 0;
    }
    for(int i = 0; i < dim_table; i++) {
        tmp = table[i];
        if (tmp != NULL) {
            while(tmp != NULL) {
                if (tmp != NULL) {
                    strcpy(array[j].name,tmp->name);
                    array[j].value = tmp->value;
                    tmp = tmp->next;
                    j++;
                }
            }
        }
    }
    return array;
}
int compare(const void* a, const void* b) {
    if ((*(node*)a).value != ((*(node*)b).value))
        return -((*(node*)a).value - ((*(node*)b).value));
    return strcmp((*(node*)a).name, (*(node*)b).name);
}
