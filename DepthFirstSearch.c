#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for adjacency list node
struct Node {
    int data;
    struct Node* next;
};

// Structure for adjacency list
struct List {
    struct Node* head;
};

// Structure for graph
struct Graph {
    int vertices;
    struct List* array;
};

// Create a new adjacency list node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Create a graph of given vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct List*)malloc(vertices * sizeof(struct List));

    for (int i = 0; i < vertices; i++)
        graph->array[i].head = NULL;

    return graph;
}

// Add edge to undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add edge from dest to src (for undirected)
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// DFS utility function
void DFSUtil(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->data;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// DFS traversal function
void DFS(struct Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++)
        visited[i] = false;

    DFSUtil(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

// Example usage
int main() {
    int vertices = 5;
    struct Graph* graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Depth First Search starting from vertex 0:\n");
    DFS(graph, 0);

    return 0;
}
