#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct for managing turf bookings
struct Booking {
    int bookingID;
    char customerName[50];
    char date[20];
    char startTime[10];
    char endTime[10];
    struct Booking *next;
};

// Queue to manage bookings
struct BookingQueue {
    struct Booking *front;
    struct Booking *rear;
};

// Function to initialize the booking queue
void initializeBookingQueue(struct BookingQueue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Function to check if the booking queue is empty
int isBookingQueueEmpty(struct BookingQueue *queue) {
    return queue->front == NULL;
}

// Function to add a booking to the queue
void addBooking(struct BookingQueue *queue, int bookingID, const char *customerName, const char *date, const char *startTime, const char *endTime) {
    struct Booking *newBooking = (struct Booking *)malloc(sizeof(struct Booking));
    newBooking->bookingID = bookingID;
    strcpy(newBooking->customerName, customerName);
    strcpy(newBooking->date, date);
    strcpy(newBooking->startTime, startTime);
    strcpy(newBooking->endTime, endTime);
    newBooking->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newBooking;
        queue->rear = newBooking;
    } else {
        queue->rear->next = newBooking;
        queue->rear = newBooking;
    }
}

// Function to remove the first booking from the queue
void removeBooking(struct BookingQueue *queue) {
    if (queue->front != NULL) {
        struct Booking *temp = queue->front;
        queue->front = queue->front->next;

        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        free(temp);
    }
}

// Function to display all bookings in the queue
void displayBookings(struct BookingQueue *queue) {
    struct Booking *temp = queue->front;
    while (temp != NULL) {
        printf("Booking ID: %d, Customer Name: %s, Date: %s, Time: %s - %s\n",
               temp->bookingID, temp->customerName, temp->date, temp->startTime, temp->endTime);
        temp = temp->next;
    }
}

// Function to simulate an online turf management system
int main() {
    struct BookingQueue linearQueue, circularQueue, priorityQueue;
    initializeBookingQueue(&linearQueue);
    initializeBookingQueue(&circularQueue);
    initializeBookingQueue(&priorityQueue);

    int choice, bookingID;
    char customerName[50], date[20], startTime[10], endTime[10];

    srand(time(NULL));

    do {
        printf("\nTurf Management System\n");
        printf("1. Book Turf Slot (Linear Queue)   ");
        printf("2. Book Turf Slot (Circular Queue)   ");
        printf("3. Book Turf Slot (Priority Queue)\n");
        printf("4. Remove Booking        ");
        printf("5. View Bookings        ");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
            case 3:
                bookingID = rand() % 1000 + 1;
                printf("Enter Customer Name: ");
                scanf("%s", customerName);
                printf("Enter Date (MM/DD/YYYY): ");
                scanf("%s", date);
                printf("Enter Start Time (HH:MM): ");
                scanf("%s", startTime);
                printf("Enter End Time (HH:MM): ");
                scanf("%s", endTime);

                if (choice == 1) {
                    addBooking(&linearQueue, bookingID, customerName, date, startTime, endTime);
                    printf("Booking added to Linear Queue.\n");
                } else if (choice == 2) {
                    addBooking(&circularQueue, bookingID, customerName, date, startTime, endTime);
                    printf("Booking added to Circular Queue.\n");
                } else if (choice == 3) {
                    addBooking(&priorityQueue, bookingID, customerName, date, startTime, endTime);
                    printf("Booking added to Priority Queue.\n");
                }
                break;

            case 4:
                printf("Select Queue to Remove Booking:\n");
                printf("1. Linear Queue        ");
                printf("2. Circular Queue        ");
                printf("3. Priority Queue\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        if (!isBookingQueueEmpty(&linearQueue)) {
                            removeBooking(&linearQueue);
                            printf("Booking removed successfully from Linear Queue.\n");
                        } else {
                            printf("No bookings available to remove from Linear Queue.\n");
                        }
                        break;
                    case 2:
                        if (!isBookingQueueEmpty(&circularQueue)) {
                            removeBooking(&circularQueue);
                            printf("Booking removed successfully from Circular Queue.\n");
                        } else {
                            printf("No bookings available to remove from Circular Queue.\n");
                        }
                        break;
                    case 3:
                        if (!isBookingQueueEmpty(&priorityQueue)) {
                            removeBooking(&priorityQueue);
                            printf("Booking removed successfully from Priority Queue.\n");
                        } else {
                            printf("No bookings available to remove from Priority Queue.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
                break;

            case 5:
                printf("Select Queue to View Bookings:\n");
                printf("1. Linear Queue        ");
                printf("2. Circular Queue        ");
                printf("3. Priority Queue\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        if (!isBookingQueueEmpty(&linearQueue)) {
                            printf("Linear Queue Bookings:\n");
                            displayBookings(&linearQueue);
                        } else {
                            printf("No bookings available to display from Linear Queue.\n");
                        }
                        break;
                    case 2:
                        if (!isBookingQueueEmpty(&circularQueue)) {
                            printf("Circular Queue Bookings:\n");
                            displayBookings(&circularQueue);
                        } else {
                            printf("No bookings available to display from Circular Queue.\n");
                        }
                        break;
                    case 3:
                        if (!isBookingQueueEmpty(&priorityQueue)) {
                            printf("Priority Queue Bookings:\n");
                            displayBookings(&priorityQueue);
                        } else {
                            printf("No bookings available to display from Priority Queue.\n");
                        }
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
                break;

            case 6:
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}
