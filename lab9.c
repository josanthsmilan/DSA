#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TURFS 100

struct Turf {
    int id;
    char name[50];
    int capacity;
    int booked;
    struct Turf* left;
    struct Turf* right;
};

struct Turf* root = NULL;
struct Turf turfs[MAX_TURFS];
int numTurfs = 0;

// Function to add a new turf
void addTurf() {
    if (numTurfs < MAX_TURFS) {
        struct Turf newTurf;

        printf("Enter Turf Name: ");
        scanf("%s", newTurf.name);

        printf("Enter Turf Capacity: ");
        scanf("%d", &newTurf.capacity);

        newTurf.id = numTurfs + 1;
        newTurf.booked = 0;

        turfs[numTurfs++] = newTurf;

        printf("Turf added successfully!\n");
    } else {
        printf("Cannot add more turfs. Maximum limit reached.\n");
    }
}

// Function to perform Breadth-First Traversal (BFT)
void breadthFirstTraversal(struct Turf* root) {
    if (root == NULL)
        return;

    struct Turf** queue = (struct Turf**)malloc(MAX_TURFS * sizeof(struct Turf*));
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct Turf* current = queue[++front];
        printf("ID: %d, Name: %s, Capacity: %d, Booked: %d\n",
               current->id, current->name, current->capacity, current->booked);

        if (current->left != NULL)
            queue[++rear] = current->left;
        if (current->right != NULL)
            queue[++rear] = current->right;
    }

    free(queue);
}

// Function to perform Depth-First Traversal (DFT)
void depthFirstTraversal(struct Turf* node) {
    if (node != NULL) {
        printf("ID: %d, Name: %s, Capacity: %d, Booked: %d\n",
               node->id, node->name, node->capacity, node->booked);

        depthFirstTraversal(node->left);
        depthFirstTraversal(node->right);
    }
}

// Search function using BFT
void searchTurfBFT(const char* name) {
    printf("BFT Search:\n");
    breadthFirstTraversal(root);

    for (int i = 0; i < numTurfs; ++i) {
        if (strcmp(turfs[i].name, name) == 0) {
            printf("Turf Found:\n");
            printf("ID: %d\n", turfs[i].id);
            printf("Name: %s\n", turfs[i].name);
            printf("Capacity: %d\n", turfs[i].capacity);
            printf("Booked: %d\n", turfs[i].booked);
            return;
        }
    }

    printf("Turf with name '%s' not found.\n", name);
}

// Search function using DFT
void searchTurfDFT(const char* name) {
    printf("DFT Search:\n");
    depthFirstTraversal(root);

    for (int i = 0; i < numTurfs; ++i) {
        if (strcmp(turfs[i].name, name) == 0) {
            printf("Turf Found:\n");
            printf("ID: %d\n", turfs[i].id);
            printf("Name: %s\n", turfs[i].name);
            printf("Capacity: %d\n", turfs[i].capacity);
            printf("Booked: %d\n", turfs[i].booked);
            return;
        }
    }

    printf("Turf with name '%s' not found.\n", name);
}

int main() {
    int choice;
    char searchName[50];

    do {
        printf("\n1. Add Turf\n");
        printf("2. Search Turf (BFT)\n");
        printf("3. Search Turf (DFT)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTurf();
                break;
            case 2:
                printf("Enter Turf Name to search: ");
                scanf("%s", searchName);
                searchTurfBFT(searchName);
                break;
            case 3:
                printf("Enter Turf Name to search: ");
                scanf("%s", searchName);
                searchTurfDFT(searchName);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
