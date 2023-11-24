#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Booking {
    int bookingID;
    char customerName[50];
    char date[20];
    float startTime;
    float endTime;
    struct Booking* next;
};

struct Booking* createBooking(int bookingID, const char* customerName, const char* date, float startTime, float endTime) {
    struct Booking* newBooking = (struct Booking*)malloc(sizeof(struct Booking));
    
    if (newBooking != NULL) {
        newBooking->bookingID = bookingID;
        strncpy(newBooking->customerName, customerName, sizeof(newBooking->customerName)-1);
        strncpy(newBooking->date, date, sizeof(newBooking->date)-1);
        newBooking->startTime = startTime;
        newBooking->endTime = endTime;
        newBooking->next = NULL;
    }
    
    return newBooking;
}

void displayBooking(struct Booking* booking) {
    printf("Booking ID: %d\n", booking->bookingID);
    printf("Customer Name: %s\n", booking->customerName);
    printf("Date: %s\n", booking->date);
    printf("Start Time: %.2f\n", booking->startTime);
    printf("End Time: %.2f\n", booking->endTime);
    printf("\n");
}

void freeBooking(struct Booking* booking) {
    free(booking);
}

int main() {
    struct Booking* booking = NULL;
    int bookingID;
    char customerName[50];
    char date[20];
    float startTime, endTime;

    // Get user input for one booking
    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);
    while ((getchar()) != '\n');  // Clear input buffer

    printf("Enter Customer Name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';  // Remove newline character

    printf("Enter Date: ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';  // Remove newline character

    printf("Enter Start Time: ");
    scanf("%f", &startTime);
    while ((getchar()) != '\n');  // Clear input buffer

    printf("Enter End Time: ");
    scanf("%f", &endTime);
    while ((getchar()) != '\n');  // Clear input buffer

    booking = createBooking(bookingID, customerName, date, startTime, endTime);

    // Displaying the booking
    displayBooking(booking);

    // Freeing the memory allocated for the booking
    freeBooking(booking);

    return 0;
}
