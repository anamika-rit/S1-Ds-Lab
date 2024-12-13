// Program to implement Kruskals Algorithm

#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define INF 999999

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} DisjointSet;

void initDisjointSet(DisjointSet sets[], int n);
int findSet(DisjointSet sets[], int vertex);
int unionSets(DisjointSet sets[], int x, int y);
void kruskalMST(Edge edges[], int edgeCount, int n);
void sortEdges(Edge edges[], int edgeCount);

void kruskalMST(Edge edges[], int edgeCount, int n) {
    DisjointSet sets[MAX_EDGES];
    
    initDisjointSet(sets, n);
    
    sortEdges(edges, edgeCount);
    
    int mstWeight = 0;
    printf("Minimum Spanning Tree Edges:\n");
    
    // Process each edge in sorted order
    for (int i = 0; i < edgeCount; i++) {
        int x = findSet(sets, edges[i].src);
        int y = findSet(sets, edges[i].dest);
        
        // If x and y belong to different sets, include this edge
        if (x != y) {
            printf("Edge (%d, %d) = %d\n", edges[i].src + 1, edges[i].dest + 1, edges[i].weight);
            mstWeight += edges[i].weight;
            unionSets(sets, x, y);
        }
    }
    
    printf("\nMinimum Spanning Tree Total Weight: %d\n", mstWeight);
}

void initDisjointSet(DisjointSet sets[], int n) {
    for (int i = 0; i < n; i++) {
        sets[i].parent = i;
        sets[i].rank = 0;
    }
}

int findSet(DisjointSet sets[], int vertex) {
    if (sets[vertex].parent != vertex) {
        sets[vertex].parent = findSet(sets, sets[vertex].parent); // Path compression
    }
    return sets[vertex].parent;
}

int unionSets(DisjointSet sets[], int x, int y) {
    int rootX = findSet(sets, x);
    int rootY = findSet(sets, y);
    
    // If they are already in the same set, return 0 (no union)
    if (rootX == rootY) return 0;
    
    // Union by rank
    if (sets[rootX].rank < sets[rootY].rank) {
        sets[rootX].parent = rootY;
    } else if (sets[rootX].rank > sets[rootY].rank) {
        sets[rootY].parent = rootX;
    } else {
        sets[rootY].parent = rootX;
        sets[rootX].rank++;
    }
    
    return 1;
}

void sortEdges(Edge edges[], int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, edgeCount;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edgeCount);
    
    Edge edges[MAX_EDGES];
    
    printf("Enter the edges in the format (src dest weight):\n");
    for (int i = 0; i < edgeCount; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }
    
    kruskalMST(edges, edgeCount, n);
    
    return 0;
}
