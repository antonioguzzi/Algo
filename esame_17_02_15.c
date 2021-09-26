#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct n {
    int val;
    int flag;
    struct n *left;
    struct n *right;
};
typedef struct n node;
typedef node* nodeptr;

struct l{
    int val;
    struct l *next;
};
typedef struct l list;
typedef list* listptr;

nodeptr insert(nodeptr root, int value);
void insert_list(listptr *l, int val);
int check_input();
void create_list(nodeptr root, listptr *l);
void get_target_leaf(nodeptr root, int* max_sum, int curr_sum, nodeptr* target_leaf);
int max_sum_path(nodeptr root);
bool mark_path(nodeptr root, nodeptr target_leaef);
int find_min(listptr l);

int main() {
    int num_val;
    int value;
    nodeptr tree = NULL;
    listptr head = NULL;

    num_val = check_input();
    for(int i = 0; i < num_val; i++) {
        scanf("%d", &value);
        tree = insert(tree, value);
    }

    max_sum_path(tree);
    create_list(tree,&head);
    printf("%d\n", find_min(head));

    free(tree);
    return 0;
}

int check_input() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("0\n");
        exit(0);
    }
    return n;
}

nodeptr insert(nodeptr root, int value) {
    if(root == NULL) {
        nodeptr new_node = malloc(sizeof(node));
        new_node->val = value;
        new_node->flag = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if(root->val < value)
        root->right = insert(root->right,value);
    else
        root->left = insert(root->left,value);
    return root;
}

void create_list(nodeptr root, listptr *l) {
    if(root != NULL) {
        if(root->flag == 1){
            insert_list(l,root->val);
        }
        create_list(root->left,l);
        create_list(root->right,l);
    }
   return;
}

int max_sum_path(nodeptr root) {
    if(root == NULL)
        return 0;
    nodeptr target_leaf;
    int max_sum = INT_MIN;

    get_target_leaf(root,&max_sum,0,&target_leaf);
    mark_path(root,target_leaf);
    return max_sum;
}

void get_target_leaf(nodeptr root, int* max_sum, int curr_sum, nodeptr* target_leaf) {
    if(root == NULL)
        return;
    curr_sum += root->val;

    if(root->left == NULL && root->right == NULL) {
        if(curr_sum > *max_sum) {
            *max_sum = curr_sum;
            *target_leaf = root;
        }
    }
    get_target_leaf(root->left, max_sum, curr_sum, target_leaf);
    get_target_leaf(root->right, max_sum, curr_sum, target_leaf);
}

bool mark_path(nodeptr root, nodeptr target_leaef) {
    if(root == NULL)
        return false;
    if(root == target_leaef || mark_path(root->left,target_leaef) || mark_path(root->right, target_leaef)) {
        root->flag = 1;
        return true;
    }
    return false;
}

void insert_list(listptr *l, int val){
    listptr new_node = malloc(sizeof(node));
    if(new_node != NULL){
        new_node->val = val;
        new_node->next = *l;
        *l = new_node;
    }
    return;
}

int find_min(listptr l){
    listptr tmp = l;
    int min = INT_MAX;
    while(tmp != NULL){
        if(tmp->val < min)
            min = tmp->val;
        tmp = tmp->next;
    }
    return min;
}






