// Program to implement BFS,DFS,Topological Sort

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// Adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
};

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
void initGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
}

// Function to add an edge to the graph (Directed)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// DFS (Depth First Search) - Recursive
void DFSUtil(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        adjList = adjList->next;
    }
}

// DFS Traversal
void DFS(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = { false };
    printf("DFS starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);

    // Check for any unvisited vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }

    printf("\n");
}

// BFS (Breadth First Search)
void BFS(struct Graph* graph, int startVertex) {
    bool visited[MAX_VERTICES] = { false };
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS starting from vertex %d: ", startVertex);
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* adjList = graph->adjList[currentVertex];
        while (adjList != NULL) {
            int adjVertex = adjList->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            adjList = adjList->next;
        }
    }

    // Check for any unvisited vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            queue[rear++] = i;  // Start BFS from unvisited nodes
            visited[i] = true;
            printf("%d ", i);
        }
    }

    printf("\n");
}

// Topological Sort - Using DFS 
void topologicalSortUtil(struct Graph* graph, int vertex, bool visited[], int stack[], int* stackIndex) {
    visited[vertex] = true;
    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            topologicalSortUtil(graph, adjVertex, visited, stack, stackIndex);
        }
        adjList = adjList->next;
    }

    stack[*stackIndex] = vertex;
    (*stackIndex)++;
}

void topologicalSort(struct Graph* graph) {
    bool visited[MAX_VERTICES] = { false };
    int stack[MAX_VERTICES];
    int stackIndex = 0;

    // Process each vertex to ensure all are covered in the sort
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
        }
    }

    printf("Topological Sort: ");
    for (int i = stackIndex - 1; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// Function to display the graph (adjacency list)
void displayGraph(struct Graph* graph) {
    printf("\nGraph Representation (Adjacency List):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjList = graph->adjList[i];
        printf("Vertex %d: ", i);
        while (adjList != NULL) {
            printf("%d -> ", adjList->vertex);
            adjList = adjList->next;
        }
        printf("NULL\n");
    }
}

// Function to display the graph (Adjacency Matrix)
void displayAdjMatrix(struct Graph* graph) {
    printf("\nGraph Representation (Adjacency Matrix):\n");

    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjList = graph->adjList[i];
        while (adjList != NULL) {
            adjMatrix[i][adjList->vertex] = 1;
            adjList = adjList->next;
        }
    }

    // Print the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph graph;
    int vertices, edges, src, dest, startVertex, choice;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initGraph(&graph, vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source and destination separated by space): ", i + 1);
        scanf("%d %d", &src, &dest);

        // Add directed edge to the graph
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            addEdge(&graph, src, dest);
        } else {
            printf("Invalid edge! Please enter vertices within the range of 0 to %d.\n", vertices - 1);
            i--;
        }
    }

    do {
        printf("\nMenu:\n");
        printf("1. Display Graph (Adjacency List)\n");
        printf("2. Adjacency Matrix\n");
        printf("3. Perform DFS Traversal\n");
        printf("4. Perform BFS Traversal\n");
        printf("5. Perform Topological Sort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayGraph(&graph);
                break;
            case 2:
                displayAdjMatrix(&graph);
                break;
            case 3:
                printf("\nEnter the start vertex for DFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= 0 && startVertex < vertices) {
                    DFS(&graph, startVertex);
                } else {
                    printf("Invalid start vertex!\n");
                }
                break;
            case 4:
                printf("\nEnter the start vertex for BFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= 0 && startVertex < vertices) {
                    BFS(&graph, startVertex);
                } else {
                    printf("Invalid start vertex!\n");
                }
                break;
            case 5:
                topologicalSort(&graph);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
