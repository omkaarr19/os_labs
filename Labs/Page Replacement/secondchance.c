#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FRAMES 100
#define MAX_REFERENCE_STRING_LENGTH 999

// Function to find and update the page
static bool findAndUpdate(int x, int arr[], bool second_chance[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (arr[i] == x) {
            second_chance[i] = true; // Mark that the page deserves a second chance
            return true; // Page found, no need to replace any page
        }
    }
    return false; // Page not found, replacement needed
}

// Function to replace and update the page
static int replaceAndUpdate(int x, int arr[], bool second_chance[], int frames, int pointer) {
    while (true) {
        if (!second_chance[pointer]) { // Page found for replacement
            arr[pointer] = x; // Replace with new page
            return (pointer + 1) % frames; // Return updated pointer
        }
        second_chance[pointer] = false; // Mark it 'false' as it got one chance
        pointer = (pointer + 1) % frames; // Update pointer in round-robin manner
    }
}

// Function to print the total number of page faults
static void printHitsAndFaults(char reference_string[], int frames) {
    int pointer = 0, pf = 0, l = 0;
    int arr[MAX_FRAMES];
    bool second_chance[MAX_FRAMES];
    int pages[MAX_REFERENCE_STRING_LENGTH];
    
    memset(arr, -1, sizeof(arr)); // Initialize array to hold page numbers
    memset(second_chance, false, sizeof(second_chance)); // Initialize second chance array
    
    char *token = strtok(reference_string, " ");
    
    while (token != NULL) {
        pages[l++] = atoi(token); // Convert string to integer and store in pages array
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < l; i++) {
        int x = pages[i];
        if (!findAndUpdate(x, arr, second_chance, frames)) { // Check if page needs replacement
            pointer = replaceAndUpdate(x, arr, second_chance, frames, pointer); // Replace page
            pf++; // Increment page fault count
        }
    }
    printf("Total page faults were %d\n", pf); // Print total page faults
}

// Main function to take user input and call the printHitsAndFaults function
int main() {
    char reference_string[MAX_REFERENCE_STRING_LENGTH];
    int frames;

    printf("Enter the reference string: ");
    fgets(reference_string, sizeof(reference_string), stdin);
    reference_string[strcspn(reference_string, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    if (frames > MAX_FRAMES) {
        printf("Number of frames should be less than or equal to %d\n", MAX_FRAMES);
        return 1;
    }

    printHitsAndFaults(reference_string, frames); // Call the function to print page faults

    return 0;
}
