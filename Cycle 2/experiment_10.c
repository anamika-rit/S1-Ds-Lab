// Program to implement Prims Agorithm (MST)

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 999

typedef struct {
    int vertices;
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initialize_graph(Graph* graph, int num_vertices) {
    graph->vertices = num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph->adjacency_matrix[i][j] = INF;
        }
    }

    printf("Enter the number of edges: ");
    int num_edges;
    scanf("%d", &num_edges);

    printf("Enter each edge in the format (u v weight):\n");
    for (int i = 0; i < num_edges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        graph->adjacency_matrix[u][v] = weight;
        graph->adjacency_matrix[v][u] = weight;
    }
}

void prim_mst(Graph* graph) {
    int num_vertices = graph->vertices;
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mst_set[MAX_VERTICES];

    for (int i = 0; i < num_vertices; i++) {
        key[i] = INF;
        mst_set[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < num_vertices - 1; count++) {
        int min_key = INF;
        int min_index = -1;

        for (int v = 0; v < num_vertices; v++) {
            if (!mst_set[v] && key[v] < min_key) {
                min_key = key[v];
                min_index = v;
            }
        }

        mst_set[min_index] = true;

        for (int v = 0; v < num_vertices; v++) {
            if (graph->adjacency_matrix[min_index][v] < INF && !mst_set[v] &&
                graph->adjacency_matrix[min_index][v] < key[v]) {
                parent[v] = min_index;
                key[v] = graph->adjacency_matrix[min_index][v];
            }
        }
    }

    int total_cost = 0;
    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 1; i < num_vertices; i++) {
        if (parent[i] != -1) {
            printf("Edge: (%d - %d) Cost: %d\n", parent[i], i, graph->adjacency_matrix[i][parent[i]]);
            total_cost += graph->adjacency_matrix[i][parent[i]];
        }
    }

    printf("\nTotal Minimum Cost: %d\n", total_cost);
}

int main() {
    Graph graph;
    int num_vertices;

    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);

    if (num_vertices <= 0 || num_vertices > MAX_VERTICES) {
        printf("Invalid number of vertices. Must be between 1 and %d\n", MAX_VERTICES);
        return 1;
    }

    initialize_graph(&graph, num_vertices);
    prim_mst(&graph);

    return 0;
}
24
