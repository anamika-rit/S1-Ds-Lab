// Program to implement BFS,DFS,Topological Sort

#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int adj_matrix[MAX][MAX]; // Adjacency matrix
bool visited[MAX]; // Visited array for traversal
int vertex_count = 0; // Number of vertices

void add_vertex() {
    if (vertex_count >= MAX) {
        printf("Cannot add more vertices. Maximum reached.\n");
        return;
    }
    vertex_count++;
    printf("Vertex %d added.\n", vertex_count - 1);
}

void add_edge(int start, int end) {
    if (start >= vertex_count || end >= vertex_count) {
        printf("Invalid vertex index!\n");
        return;
    }
    adj_matrix[start][end] = 1;
    printf("Edge added from %d to %d.\n", start, end);
}

// Function to print the adjacency matrix
void print_adj_matrix() {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

void bfs(int start) {
    bool visited[MAX] = {false};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    printf("BFS: ");
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        for (int i = 0; i < vertex_count; i++) {
            if (adj_matrix[vertex][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void dfs_helper(int vertex) {
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < vertex_count; i++) {
        if (adj_matrix[vertex][i] && !visited[i]) {
            dfs_helper(i);
        }
    }
}

void dfs(int start) {
    // Reset visited array before starting DFS
    for (int i = 0; i < MAX; i++) visited[i] = false;

    printf("DFS: ");
    dfs_helper(start);

    // After the first DFS, revisit unvisited nodes by calling DFS for them
    for (int i = 0; i < vertex_count; i++) {
        if (!visited[i]) {
           
            dfs_helper(i);  // Perform DFS starting from the unvisited node
            printf("\n");
        }
    }
}


void topological_sort_helper(int vertex, int stack[], int *top) {
    visited[vertex] = true;

    for (int i = 0; i < vertex_count; i++) {
        if (adj_matrix[vertex][i] && !visited[i]) {
            topological_sort_helper(i, stack, top);
        }
    }

    stack[(*top)++] = vertex;
}

void topological_sort() {
    for (int i = 0; i < MAX; i++) visited[i] = false;

    int stack[MAX], top = 0;

    for (int i = 0; i < vertex_count; i++) {
        if (!visited[i]) {
            topological_sort_helper(i, stack, &top);
        }
    }

    printf("Topological Sort: ");
    while (top > 0) {
        printf("%d ", stack[--top]);
    }
    printf("\n");
}

int main() {
    int choice, start, end, vertex;

    do {
        printf("\n1. Add Vertex\n2. Add Edge\n3. BFS\n4. DFS\n5. Topological Sort\n6. Print Adjacency Matrix\n0. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_vertex();
                break;
            case 2:
                printf("Enter start and end vertex: ");
                scanf("%d %d", &start, &end);
                add_edge(start, end);
                break;
            case 3:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &vertex);
                bfs(vertex);
                break;
            case 4:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &vertex);
                dfs(vertex);
                break;
            case 5:
                topological_sort();
                break;
            case 6:
                print_adj_matrix();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
