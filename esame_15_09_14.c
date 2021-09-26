#include <stdio.h>
#include <stdlib.h>

struct n {
    int val;
    int num_left;
    int num_right;
    struct n *left;
    struct n *right;
};
typedef struct n node;
typedef node* nodeptr;

nodeptr insert(nodeptr root, int value);
int check_input();
void print_tree(nodeptr root);
void left_visit(nodeptr root, nodeptr rootptr);
void right_visit(nodeptr root, nodeptr rootptr);
void tree_visit(nodeptr root,nodeptr rootptr);

int main() {
    int num_val;
    int value;
    nodeptr tree = NULL;
    nodeptr treeptr;

    num_val = check_input();
    for(int i = 0; i < num_val; i++) {
        scanf("%d", &value);
        tree = insert(tree, value);
    }
    treeptr = tree;
    tree_visit(tree,treeptr);
    print_tree(tree);

    free(tree);
    return 0;
}

int check_input() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0)
        exit(0);
    return n;
}

nodeptr insert(nodeptr root, int value) {
    if(root == NULL) {
        nodeptr new_node = malloc(sizeof(node));
        new_node->val = value;
        new_node->num_left = 0;
        new_node->num_right = 0;
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

void print_tree(nodeptr root) {
    if(root != NULL) {
        print_tree(root->left);
        if(root->num_left > root->num_right)
            printf("%d\n",root->val);
        print_tree(root->right);
    }
    return;
}

void left_visit(nodeptr root, nodeptr rootptr) {
    if(root->left != NULL) {
        rootptr->num_left++;
        left_visit(root->left,rootptr);
    }
    return;
}

void right_visit(nodeptr root, nodeptr rootptr) {
    if(root->right != NULL) {
        rootptr->num_right++;
        right_visit(root->right, rootptr);
    }
    return;
}

void tree_visit(nodeptr root, nodeptr rootptr) {
    if(root != NULL && rootptr != NULL) {
        left_visit(root,rootptr);
        right_visit(root,rootptr);
        tree_visit(root->left, rootptr->left);
        rootptr = root;
        tree_visit(root->right, rootptr->right);
    }
    return;
}
