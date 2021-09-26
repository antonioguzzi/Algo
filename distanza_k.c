#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edges {
    int num_edges;
    int* edges;
} edges;

typedef struct _queue {
    int *values;
    int capacity;
    int head;
    int tail;
} queue;
typedef queue* queueptr;

edges* read_graph(int dim_graph);
int check_input();
void print_graph(int dim_graph, edges* graph);
void bfs(edges* graph, int dim_graph, int k, int from);
void queue_init(queueptr q, int capacity);
void queue_deinit(queueptr q);
void queue_push_back(queueptr q, int value);
int queue_pop_front(queueptr q);
int queue_is_empty(queueptr q);


int main()
{
    edges *graph;
    int dim_graph;

    dim_graph = check_input();
    graph = read_graph(dim_graph);
    printf("Grafo:\n");
    print_graph(dim_graph,graph);
    printf("\na distanza 2 dalla sorgente 0:\n");
    bfs(graph,dim_graph,2,0);



    return 0;
}

edges* read_graph(int dim_graph) {
    edges* graph;
    int num_edges;

    graph = malloc(sizeof(edges)*dim_graph);
    for(int i = 0; i < dim_graph; i++) {
        scanf("%d", &num_edges);
        graph[i].num_edges = num_edges;
        graph[i].edges = malloc(sizeof(int)*num_edges);
        for(int j = 0; j < num_edges; j++)
            scanf("%d", graph[i].edges + j);
    }
    return graph;
}

void print_graph(int dim_graph, edges* graph) {
    for(int i = 0; i < dim_graph; i++) {
        printf("numero vertici %d -> ", graph[i].num_edges);
        for(int j = 0; j < graph[i].num_edges; j++)
            printf("%d ", graph[i].edges[j]);
        printf("\n");
    }
    return;
}

int check_input() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        exit(1);
    }
    return n;
}

void queue_init(queueptr q, int capacity) {
    q->values = malloc(sizeof(int) * capacity);
    q->head = 0;
    q->tail = -1;
    q->capacity = 0;
    return;
}

void queue_deinit(queueptr q) {
    free(q->values);
    q->head = 0;
    q->tail = -1;
    return;
}

void queue_push_back(queueptr q, int value) {
    q->tail++;
    (q->values)[q->tail] = value;
    q->capacity++;
    return;
}

int queue_pop_front(queueptr q) {
    int val = (q->values)[q->head];
    q->head++;
    q->capacity--;
    return val;
}

int queue_is_empty(queueptr q) {
    if(q->capacity == 0)
        return 1;
    return 0;
}

void bfs(edges* graph, int dim_graph, int k, int from){
    int* colors = malloc(sizeof(int)*dim_graph);
    int* distance = malloc(sizeof(int)*dim_graph);
    int src;
    int dest;
    queue q;

    for(int i = 0; i < dim_graph; i++){
        colors[i] = 0;
        distance[i] = INT_MIN;
    }

    colors[from] = 1;
    distance[from] = 0;

    queue_init(&q,dim_graph);
    queue_push_back(&q,from);
    while(!queue_is_empty(&q)){
        src = queue_pop_front(&q);
        for(int i = 0; i < graph[src].num_edges; i++){
            dest = graph[src].edges[i];
            if(colors[dest] == 0){
                colors[dest] = 1;
                distance[dest] = distance[src]+1;
                if (distance[dest] == k)
                    printf("%d ", dest);
                queue_push_back(&q,dest);
            }
        }
    }
    printf("\n");
    free(colors);
    free(distance);
    return;
}
