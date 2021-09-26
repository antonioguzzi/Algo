#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Edges {
    int num_edges;
    int* edges;
} edges;

edges* read_graph(int dim_graph);
void print_graph(int dim_graph, edges* graph);
int check_dim_graph();
void recursive_dfs(edges* graph, int souce, int*colors);
int* dfs(edges* graph, int dim_graph, int from);
int is_connected(int* colors, int dim_graph);

int main() {
    srand(time(NULL));
    edges *graph;
    int dim_graph;
    int* colors;
    int from;

    dim_graph = check_dim_graph();
    from = 0 + rand() % (dim_graph);
    graph = read_graph(dim_graph);
    colors = dfs(graph,dim_graph,from);
    printf("%d\n", is_connected(colors,dim_graph));
    return 0;
}

int check_dim_graph() {
    int n;
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        exit(1);
    }
    return n;
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

void recursive_dfs(edges* graph, int souce, int*colors) {
    int dest;
    for(int i = 0; i < graph[souce].num_edges; i++) {
        dest = graph[souce].edges[i];
        if(!colors[dest]) {
            colors[dest] = 1;
            recursive_dfs(graph,dest,colors);
        }
    }
}

int* dfs(edges* graph, int dim_graph, int from) {
    int* colors = malloc(sizeof(int)*dim_graph);
    for(int i = 0; i < dim_graph; i++)
        colors[i] = 0;
    colors[from] = 1;
    recursive_dfs(graph,from,colors);
    return colors;
}

int is_connected(int* colors, int dim_graph) {
    for(int i = 0; i < dim_graph; i++) {
        if(colors[i] == 0)
            return 0;
    }
    return 1;
}

