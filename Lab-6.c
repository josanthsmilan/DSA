#include <stdio.h>
#include <stdlib.h>

#define MAX_TURFS 100

struct Turf {
    int turfId;
    float price;
};

void merge(struct Turf arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    struct Turf L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Turf arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void writeToFile(struct Turf turfs[], int n, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp != NULL) {
        fwrite(turfs, sizeof(struct Turf), n, fp);
        fclose(fp);
    } else {
        printf("Error opening file for writing!\n");
    }
}

void readFromFile(struct Turf turfs[], int n, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        fread(turfs, sizeof(struct Turf), n, fp);
        fclose(fp);
    } else {
        printf("Error opening file for reading!\n");
    }
}

void getTurfData(struct Turf turfs[], int n) {
    printf("Enter details for %d turfs:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter price for turf %d: ", i + 1);
        scanf("%f", &turfs[i].price);
        turfs[i].turfId = i + 1;
    }
}

void printTurfs(struct Turf turfs[], int n) {
    printf("Turf ID\tPrice\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\n", turfs[i].turfId, turfs[i].price);
    }
}

int main() {
    struct Turf turfs[MAX_TURFS];
    int numTurfs;

    printf("Enter the number of turfs: ");
    scanf("%d", &numTurfs);

    if (numTurfs <= 0 || numTurfs > MAX_TURFS) {
        printf("Invalid number of turfs. Please enter a number between 1 and %d.\n", MAX_TURFS);
        return 1;
    }

    getTurfData(turfs, numTurfs);

    printf("Before sorting:\n");
    printTurfs(turfs, numTurfs);

    // Sorting using Merge Sort
    mergeSort(turfs, 0, numTurfs - 1);

    printf("\nAfter sorting using Merge Sort:\n");
    printTurfs(turfs, numTurfs);

    // Writing data to a file
    writeToFile(turfs, numTurfs, "turf_data.txt");

    // Reading data back from file
    struct Turf turfsFromFile[MAX_TURFS];
    readFromFile(turfsFromFile, numTurfs, "turf_data.txt");

    printf("\nData read from file:\n");
    printTurfs(turfsFromFile, numTurfs);

    return 0;
}
