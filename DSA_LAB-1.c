#include <stdio.h>
#include <string.h>
#define MAX_TURF_AREAS 100
#define MAX_MATRIX_SIZE 10

struct TurfArea {
    char name[50];
    float area;
    int equipmentCount;
};

struct Matrix {
    int rows;
    int cols;
    float data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
};

struct TurfArea turfAreas[MAX_TURF_AREAS];
int numTurfAreas = 0;

// Function to display a matrix
void displayMatrix(struct Matrix mat) {
    printf("Matrix (%d x %d):\n", mat.rows, mat.cols);
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%.2f\t", mat.data[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices
struct Matrix addMatrices(struct Matrix mat1, struct Matrix mat2) {
    struct Matrix result;
    result.rows = mat1.rows;
    result.cols = mat1.cols;

    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            result.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
        }
    }

    return result;
}

// Function to multiply two matrices
struct Matrix multiplyMatrices(struct Matrix mat1, struct Matrix mat2) {
    struct Matrix result;
    result.rows = mat1.rows;
    result.cols = mat2.cols;

    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat2.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < mat1.cols; k++) {
                result.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
            }
        }
    }

    return result;
}

// Function to get matrix elements from user input
struct Matrix getMatrixFromInput() {
    struct Matrix mat;
    printf("Enter the number of rows: ");
    scanf("%d", &mat.rows)/
    printf("Enter the number of columns: ");
    scanf("%d", &mat.cols);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("Enter element at row %d, column %d: ", i + 1, j + 1);
            scanf("%f", &mat.data[i][j]);
        }
    }

    return mat;
}

void displayTurfAreas() {
    if (numTurfAreas == 0) {
        printf("No turf areas in the system.\n");
        return;
    }

    printf("Turf Areas:\n");
    for (int i = 0; i < numTurfAreas; i++) {
        printf("Name: %s\n", turfAreas[i].name);
        printf("Area: %.2f square meters\n", turfAreas[i].area);
        printf("Equipment Count: %d\n", turfAreas[i].equipmentCount);
        printf("\n");
    }
}

void addTurfArea() {
    if (numTurfAreas == MAX_TURF_AREAS) {
        printf("Maximum turf areas reached. Cannot add more.\n");
        return;
    }

    struct TurfArea newTurfArea;
    printf("Enter turf area name: ");
    scanf("%s", newTurfArea.name);
    printf("Enter turf area size (in square meters): ");
    scanf("%f", &newTurfArea.area);
    printf("Enter equipment count: ");
    scanf("%d", &newTurfArea.equipmentCount);

    turfAreas[numTurfAreas] = newTurfArea;
    numTurfAreas++;

    printf("Turf area added successfully.\n");
}

void removeTurfArea(char name[]) {
    int found = 0;
    for (int i = 0; i < numTurfAreas; i++) {
        if (strcmp(turfAreas[i].name, name) == 0) {
            for (int j = i; j < numTurfAreas - 1; j++) {
                turfAreas[j] = turfAreas[j + 1];
            }
            numTurfAreas--;
            printf("Turf area '%s' removed successfully.\n", name);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Turf area '%s' not found. Removal failed.\n", name);
    }
}

int main() {
    int choice;
    char turfName[50];

    do {
        printf("\nTurf Management System\n");
        printf("1. Add Turf Area\n");
        printf("2. Remove Turf Area\n");
        printf("3. Display Turf Areas\n");
        printf("4. Add Matrices\n");
        printf("5. Multiply Matrices\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTurfArea();
                break;

            case 2:
                printf("Enter the name of the turf area to remove: ");
                scanf("%s", turfName);
                removeTurfArea(turfName);
                break;
            case 3:
                displayTurfAreas();
                break;

            case 4:
                printf("Addition of Matrices:\n");
                struct Matrix mat1 = getMatrixFromInput();
                struct Matrix mat2 = getMatrixFromInput();
                struct Matrix resultAdd = addMatrices(mat1, mat2);
                displayMatrix(resultAdd);
                break;

            case 5:
                printf("Multiplication of Matrices:\n");
                struct Matrix mat1Multiply = getMatrixFromInput();
                struct Matrix mat2Multiply = getMatrixFromInput();
                struct Matrix resultMultiply = multiplyMatrices(mat1Multiply, mat2Multiply);
                displayMatrix(resultMultiply);
                break;

            case 6:
                printf("Exiting the Turf Management System.\n");
                break;

            default:
                printf("Invalid choice. Please choose a valid option.\n");
        }
    } while (choice != 6);

    return 0;
}
