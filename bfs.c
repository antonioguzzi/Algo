#include <stdio.h>
#include <stdlib.h>

//struttura per la coda
typedef struct _queue {
    int *values;
    int capacity;
    int head;
    int tail;
} queue;
typedef queue* queueptr;

//struttura per il grafo
typedef struct Edges {
    int num_edges;
    int* edges;
} edges;

//funzioni per la coda
void queue_init(queueptr q, int capacity);
void queue_deinit(queueptr q);
void queue_push_back(queueptr q, int value);
int queue_pop_front(queueptr q);
int queue_is_empty(queueptr q);

//funzioni per il grafo
edges* read_graph(int dim_graph);
int check_input();
int bfs(edges* graph, int dim_graph, int from, int to);
void print_graph(int dim_graph, edges* graph);

//main
int main() {
    edges *graph;
    int dim_graph;
    int num_query;
    int from;
    int to;

    dim_graph = check_input();
    graph = read_graph(dim_graph);
    num_query = check_input();
    for(int i = 0; i < num_query; i++) {
        scanf("%d %d", &from, &to);
        printf("%d\n", bfs(graph,dim_graph,from,to));
    }
    //print_graph(dim_graph,graph);

    return 0;
} //fine main

//legge il grafo da input
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

//stampa il grafo
void print_graph(int dim_graph, edges* graph) {
    for(int i = 0; i < dim_graph; i++) {
        printf("numero vertici %d -> ", graph[i].num_edges);
        for(int j = 0; j < graph[i].num_edges; j++)
            printf("%d ", graph[i].edges[j]);
        printf("\n");
    }
    return;
}

//controlla l'input della dimensione
int check_input() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        exit(1);
    }
    return n;
}

//inizializza la coda
void queue_init(queueptr q, int capacity) {
    q->values = malloc(sizeof(int) * capacity);
    q->head = 0;
    q->tail = -1;
    q->capacity = 0;
    return;
}

//libera la coda
void queue_deinit(queueptr q) {
    free(q->values);
    q->head = 0;
    q->tail = -1;
    return;
}

//inserisce in coda
void queue_push_back(queueptr q, int value) {
    q->tail++;
    (q->values)[q->tail] = value;
    q->capacity++;
    return;
}

//estrae la testa
int queue_pop_front(queueptr q) {
    int val = (q->values)[q->head];
    q->head++;
    q->capacity--;
    return val;
}

//controlla se la coda è vuota
int queue_is_empty(queueptr q) {
    if(q->capacity == 0)
        return 1;
    return 0;
}

//visita bfs per percorsi
int bfs(edges* graph, int dim_graph, int from, int to) {
    if(from == to)
        return 0;
    int* distance = malloc(sizeof(int)*dim_graph);
    queue q;
    int source;
    int dest;

    for(int i = 0; i < dim_graph; i++)
        distance[i] = -1;

    distance[from] = 0;
    queue_init(&q,dim_graph);
    queue_push_back(&q,from);
    while(queue_is_empty(&q) != 1) {
        source = queue_pop_front(&q);
        for(int i = 0; i < graph[source].num_edges; i++) {
            dest = graph[source].edges[i];
            if(distance[dest] == -1) {
                distance[dest] = distance[source] + 1;
                if(dest == to) {
                    int ds;
                    ds = distance[dest];
                    queue_deinit(&q);
                    free(distance);
                    return ds;
                }
                queue_push_back(&q,dest);
            }

        }
    }
    queue_deinit(&q);
    free(distance);
    return -1;
}




