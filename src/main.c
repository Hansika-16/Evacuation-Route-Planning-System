#include <stdio.h>
#include <limits.h>

#define MAX 50

int graph[MAX][MAX];
int blocked[MAX][MAX];
int safeZone[MAX];
int vertices;
void initializeGraph();
void addRoad();
void removeRoad();
void blockRoad();
void unblockRoad();
void markSafeZone();
void displayGraph();
void displaySafeZones();
void dijkstra(int source);
int minDistance(int dist[], int visited[]);
void printDistances(int dist[]);
void printPath(int parent[], int j);
void printAllPaths(int parent[], int dist[], int source);
void menu();
int isValidLocation(int loc);
int main() {
    int choice;
    int source;

    printf("Enter number of locations: ");
    scanf("%d", &vertices);

    initializeGraph();

    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            addRoad();
            break;
        case 2:
            removeRoad();
            break;
        case 3:
            blockRoad();
            break;
        case 4:
            unblockRoad();
            break;
        case 5:
            markSafeZone();
            break;
        case 6:
            displayGraph();
            break;
        case 7:
            displaySafeZones();
            break;
        case 8:
            printf("Enter evacuation source: ");
            scanf("%d", &source);
            if (isValidLocation(source))
                dijkstra(source);
            else
                printf("invalid source location\n");
            break;
        case 9:
            printf("System exited safely.\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
void initializeGraph() {
    int i, j;
    for (i = 0; i < vertices; i++) {
        safeZone[i] = 0;
        for (j = 0; j < vertices; j++) {
            graph[i][j] = 0;
            blocked[i][j] = 0;
        }
    }
}
int isValidLocation(int loc) {
    return (loc >= 0 && loc < vertices);
}
void addRoad() {
    int src, dest, dist;
    printf("Enter source destination distance: ");
    scanf("%d %d %d", &src, &dest, &dist);

    if (!isValidLocation(src) || !isValidLocation(dest)) {
        printf("Invalid location\n");
        return;
    }

    graph[src][dest] = dist;
    graph[dest][src] = dist;
    printf("Road added\n");
}
void removeRoad() {
    int src, dest;
    printf("Enter source destination: ");
    scanf("%d %d", &src, &dest);

    graph[src][dest] = 0;
    graph[dest][src] = 0;
    blocked[src][dest] = 0;
    blocked[dest][src] = 0;

    printf(" Road removed\n");
}
void blockRoad() {
    int src, dest;
    printf("Enter source destination: ");
    scanf("%d %d", &src, &dest);

    blocked[src][dest] = 1;
    blocked[dest][src] = 1;

    printf(" Road blocked\n");
}
void unblockRoad() {
    int src, dest;
    printf("Enter source destination: ");
    scanf("%d %d", &src, &dest);

    blocked[src][dest] = 0;
    blocked[dest][src] = 0;

    printf("Road unblocked\n");
}
void markSafeZone() {
    int loc;
    printf("Enter safe zone location: ");
    scanf("%d", &loc);

    if (isValidLocation(loc)) {
        safeZone[loc] = 1;
        printf(" Location %d marked as Safe Zone\n", loc);
    } else {
        printf("Invalid location\n");
    }
}
void displayGraph() {
    int i, j;
    printf("\nRoad Network:\n");

    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (blocked[i][j])
                printf(" X ");
            else
                printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
}
void displaySafeZones() {
    int i;
    printf("\nSafe Zones:\n");
    for (i = 0; i < vertices; i++) {
        if (safeZone[i])
            printf("Location %d is SAFE\n", i);
    }
}
void dijkstra(int source) {
    int dist[MAX], visited[MAX], parent[MAX];
    int i, count, u, v;

    for (i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (count = 0; count < vertices - 1; count++) {
        u = minDistance(dist, visited);
        if (u == -1) break;
        visited[u] = 1;

        for (v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] &&
                !blocked[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printDistances(dist);
    printAllPaths(parent, dist, source);
}
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, index = -1, i;

    for (i = 0; i < vertices; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
void printDistances(int dist[]) {
    int i;
    printf("\nShortest Evacuation Distances:\n");

    for (i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX)
            printf("Location %d -> Unreachable\n", i);
        else
            printf("Location %d -> %d\n", i, dist[i]);
    }
}
void printAllPaths(int parent[], int dist[], int source) {
    int i;
    printf("\nEvacuation Paths:\n");

    for (i = 0; i < vertices; i++) {
        if (i != source && dist[i] != INT_MAX) {
            printf("Path to %d: ", i);
            printPath(parent, i);
            printf("\n");
        }
    }
}
void printPath(int parent[], int j) {
    if (j == -1) return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}
void menu() {
    printf("\n Evacuation Menu\n");
    printf("1. Add Road\n");
    printf("2. Remove Road\n");
    printf("3. Block Road\n");
    printf("4. Unblock Road\n");
    printf("5. Mark Safe Zone\n");
    printf("6. Display Road Network\n");
    printf("7. Display Safe Zones\n");
    printf("8. Find Evacuation Path\n");
    printf("9. Exit\n");
    printf("Enter choice: ");
}
