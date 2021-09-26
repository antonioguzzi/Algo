#include <stdio.h>
#include <stdlib.h>

typedef struct _edges {
    int num_edges;
    int* edges;
} Edges;

typedef struct _queue {
    int *values;
    int capacity;
    int head;
    int tail;
} queue;
typedef queue* queueptr;

void queue_init(queueptr q, int capacity);
void queue_deinit(queueptr q);
void queue_push_back(queueptr q, int value);
int queue_pop_front(queueptr q);
int queue_is_empty(queueptr q);

Edges* read_graph(int dim_graph);
void print_graph(int dim_graph, Edges* graph);
int check_dim();
int euleriano(Edges* graph, int dim_graph, int from);

int main() {
    int dim_graph;
    Edges* graph;

    dim_graph = check_dim();
    graph = read_graph(dim_graph);
    print_graph(dim_graph,graph);
    if(!euleriano(graph,dim_graph,0))
        printf("Il grafo non è euleriano porchiddio\n");
    else
        printf("il grafo è euleriano\n");

    free(graph);
    return 0;
}

int check_dim() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Oh diocane fai a modo.\n");
        exit(0);
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


Edges* read_graph(int dim_graph) {
    Edges* graph;
    int num_edges;

    graph = malloc(sizeof(Edges) * dim_graph);
    for(int i = 0; i < dim_graph; i++) {
        scanf("%d", &num_edges);
        graph[i].num_edges = num_edges;
        graph[i].edges = malloc(sizeof(int)*num_edges);
        for(int j = 0; j < num_edges; j++)
            scanf("%d", graph[i].edges+j);
    }

    return graph;
}

void print_graph(int dim_graph, Edges* graph) {
    for(int i = 0; i < dim_graph; i++) {
        printf("numero vertici di %d: %d -> ", i, graph[i].num_edges);
        for(int j = 0; j < graph[i].num_edges; j++)
            printf("%d ", graph[i].edges[j]);
        printf("\n");
    }
    return;
}

int euleriano(Edges* graph, int dim_graph, int from){
    int* colors = malloc(sizeof(int)*dim_graph);
    queue q;
    int src, dest;

    for(int i = 0; i < dim_graph; i++)
        colors[i] = 0;
    colors[from] = 1;
    queue_init(&q,dim_graph);
    queue_push_back(&q,from);
    while(!queue_is_empty(&q)){
        src = queue_pop_front(&q);
        if (graph[src].num_edges % 2 == 1) return 0;
        for(int i = 0; i < graph[src].num_edges; i++){
            dest = graph[src].edges[i];
            if(!colors[dest]){
                colors[dest] = 1;
                queue_push_back(&q,dest);
            }
        }
    }
    for(int i = 0; i < dim_graph; i++)
        if(!colors[i]) return 0;
    queue_deinit(&q);
    return 1;
}
