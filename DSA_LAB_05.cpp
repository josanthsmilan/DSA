#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SLOTS 20 // Maximum number of available slots

typedef struct {
    int slotID; // Unique identifier for each slot
    int startTime; // Time in 24-hour format (Example: 1330 represents 1:30 PM)
    int endTime; // Time in 24-hour format
    int booked; // Flag to indicate whether the slot is booked or not
} TurfSlot;

TurfSlot turfSlots[MAX_SLOTS]; // Global array to hold turf slots

// Function to initialize turf slots with default values
void initializeTurfSlots() {
    // Initialize turf slots with default values (for demonstration purposes)
    for (int i = 0; i < MAX_SLOTS; i++) {
        turfSlots[i].slotID = i + 1;
        turfSlots[i].startTime = 900 + i * 100; // Example: Start time from 9:00 AM
        turfSlots[i].endTime = 1000 + i * 100; // Example: End time till 10:00 AM
        turfSlots[i].booked = 0; // Initially, all slots are available
    }
}

// Function to display available turf slots
void displayAvailableSlots() {
    printf("Available Turf Slots:\n");
    printf("+--------+------------------+------------------+\n");
    printf("| SlotID |     Start Time    |      End Time     |\n");
    printf("+--------+------------------+------------------+\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        printf("| %-6d | %04d hrs          | %04d hrs          |\n", turfSlots[i].slotID, 
               turfSlots[i].startTime, turfSlots[i].endTime);
    }
    printf("+--------+------------------+------------------+\n");
}

// Function to book a turf slot
void bookTurfSlot(int slotID) {
    if (slotID < 1 || slotID > MAX_SLOTS) {
        printf("Invalid Slot ID\n");
        return;
    }

    if (turfSlots[slotID - 1].booked) {
        printf("Slot %d is already booked\n", slotID);
    } else {
        turfSlots[slotID - 1].booked = 1;
        printf("Slot %d booked successfully\n", slotID);
    }
}

// Function to perform Bubble Sort on turf slots based on start time
void bubbleSortTurfSlots() {
    for (int i = 0; i < MAX_SLOTS - 1; i++) {
        for (int j = 0; j < MAX_SLOTS - 1 - i; j++) {
            if (turfSlots[j].startTime > turfSlots[j + 1].startTime) {
                TurfSlot temp = turfSlots[j];
                turfSlots[j] = turfSlots[j + 1];
                turfSlots[j + 1] = temp;
            }
        }
    }
}

// Function to perform Insertion Sort on turf slots based on end time
void insertionSortTurfSlots() {
    for (int i = 1; i < MAX_SLOTS; i++) {
        TurfSlot key = turfSlots[i];
        int j = i - 1;
        while (j >= 0 && turfSlots[j].endTime > key.endTime) {
            turfSlots[j + 1] = turfSlots[j];
            j = j - 1;
        }
        turfSlots[j + 1] = key;
    }
}

// Function to perform Linear Search for a booked slot based on start time
int linearSearchStartTime(int startTime) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (turfSlots[i].booked && turfSlots[i].startTime == startTime) {
            return i;
        }
    }
    return -1;
}

// Function to perform Sentinel Search for a booked slot based on end time
int sentinelSearchEndTime(int endTime) {
    int last = turfSlots[MAX_SLOTS - 1].endTime;
    turfSlots[MAX_SLOTS - 1].endTime = endTime;

    int i = 0;
    while (turfSlots[i].endTime != endTime) {
        i++;
    }

    turfSlots[MAX_SLOTS - 1].endTime = last;

    if (i < MAX_SLOTS - 1 || endTime == last) {
        return i;
    } else {
        return -1;
    }
}

// Function to perform Binary Search for a booked slot based on slot ID
int binarySearchSlotID(int slotID) {
    int low = 0, high = MAX_SLOTS - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (turfSlots[mid].slotID == slotID) {
            return mid;
        } else if (turfSlots[mid].slotID < slotID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    srand(time(NULL));
    initializeTurfSlots();

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display Available Turf Slots\n");
        printf("2. Book a Turf Slot\n");
        printf("3. Bubble Sort Turf Slots (Start Time)\n");
        printf("4. Insertion Sort Turf Slots (End Time)\n");
        printf("5. Linear Search (Start Time)\n");
        printf("6. Sentinel Search (End Time)\n");
        printf("7. Binary Search (Slot ID)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableSlots();
                break;

            case 2:
                {
                    int slotID;
                    printf("Enter the Slot ID to book: ");
                    scanf("%d", &slotID);
                    bookTurfSlot(slotID);
                }
                break;

            case 3:
                bubbleSortTurfSlots();
                printf("Turf Slots sorted using Bubble Sort based on Start Time\n");
                break;

            case 4:
                insertionSortTurfSlots();
                printf("Turf Slots sorted using Insertion Sort based on End Time\n");
                break;

            case 5:
                {
                    int searchStartTime;
                    printf("Enter the Start Time to search: ");
                    scanf("%d", &searchStartTime);
                    int index = linearSearchStartTime(searchStartTime);
                    if (index != -1) {
                        printf("Booked slot found at index %d\n", index);
                    } else {
                        printf("No booked slot found for the given Start Time\n");
                    }
                }
                break;

            case 6:
                {
                    int searchEndTime;
                    printf("Enter the End Time to search: ");
                    scanf("%d", &searchEndTime);
                    int index = sentinelSearchEndTime(searchEndTime);
                    if (index != -1) {
                        printf("Booked slot found at index %d\n", index);
                    } else {
                        printf("No booked slot found for the given End Time\n");
                    }
                }
                break;

            case 7:
                {
                    int searchSlotID;
                    printf("Enter the Slot ID to search: ");
                    scanf("%d", &searchSlotID);
                    int index = binarySearchSlotID(searchSlotID);
                    if (index != -1) {
                        printf("Slot ID found at index %d\n", index);
                    } else {
                        printf("Slot ID not found\n");
                    }
                }
                break;

            case 0:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

