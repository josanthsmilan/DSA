#include <stdio.h>
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

// Function to search for a turf by name
void searchTurf(const char *name) {
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

// Function to delete a turf by ID
void deleteTurf(int id) {
    int index = -1;
    for (int i = 0; i < numTurfs; ++i) {
        if (turfs[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Remove the turf by shifting the remaining elements
        for (int i = index; i < numTurfs - 1; ++i) {
            turfs[i] = turfs[i + 1];
        }

        numTurfs--;

        printf("Turf with ID %d deleted successfully!\n", id);
    } else {
        printf("Turf with ID %d not found.\n", id);
    }
}

// Function to display all turfs
void displayAllTurfs() {
    printf("All Turfs:\n");
    for (int i = 0; i < numTurfs; ++i) {
        printf("ID: %d, Name: %s, Capacity: %d, Booked: %d\n",
               turfs[i].id, turfs[i].name, turfs[i].capacity, turfs[i].booked);
    }
}

// Function to display booked turfs
void displayBookedTurfs() {
    printf("Booked Turfs:\n");
    for (int i = 0; i < numTurfs; ++i) {
        if (turfs[i].booked > 0) {
            printf("ID: %d, Name: %s, Capacity: %d, Booked: %d\n",
                   turfs[i].id, turfs[i].name, turfs[i].capacity, turfs[i].booked);
        }
    }
}

// Function to display turf details
void displayTurfDetails(int id) {
    int index = -1;
    for (int i = 0; i < numTurfs; ++i) {
        if (turfs[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Turf Details:\n");
        printf("ID: %d\n", turfs[index].id);
        printf("Name: %s\n", turfs[index].name);
        printf("Capacity: %d\n", turfs[index].capacity);
        printf("Booked: %d\n", turfs[index].booked);
    } else {
        printf("Turf with ID %d not found.\n", id);
    }
}
// Function to calculate the height of the BST
int calculateBSTHeight(struct Turf* node) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = calculateBSTHeight(node->left);
    int rightHeight = calculateBSTHeight(node->right);

    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

// Function to book a turf
void bookTurf() {
    int id, numBookings;

    printf("Enter Turf ID to book: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < numTurfs; ++i) {
        if (turfs[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Enter the number of bookings: ");
        scanf("%d", &numBookings);

        if (numBookings <= turfs[index].capacity - turfs[index].booked) {
            turfs[index].booked += numBookings;
            printf("%d bookings made successfully for Turf ID %d!\n", numBookings, id);
        } else {
            printf("Booking failed. Insufficient capacity.\n");
        }
    } else {
        printf("Turf with ID %d not found.\n", id);
    }
}


int main() {
    int choice;
    char searchName[50];
    int deleteId;

    do {
        printf("\n1. Add Turf\n");
        printf("2. Search Turf\n");
        printf("3. Delete Turf\n");
        printf("4. Display All Turfs\n");
        printf("5. Display Booked Turfs\n");
        printf("6. Display Turf Details\n");
        printf("7. Book Turf\n");
        printf("8. Calculate BST Height\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTurf();
                break;
            case 2:
                printf("Enter Turf Name to search: ");
                scanf("%s", searchName);
                searchTurf(searchName);
                break;
            case 3:
                printf("Enter Turf ID to delete: ");
                scanf("%d", &deleteId);
                deleteTurf(deleteId);
                break;
            case 4:
                displayAllTurfs();
                break;
            case 5:
                displayBookedTurfs();
                break;
            case 6:
                printf("Enter Turf ID to display details: ");
                scanf("%d", &deleteId);
                displayTurfDetails(deleteId);
                break;
            case 7:
                bookTurf();
                break;
            case 8:
                // Calculate and display the height of the BST
                printf("Height of the BST: %d\n", calculateBSTHeight(root));
                break;

            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}
