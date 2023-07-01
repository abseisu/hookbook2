/*
 * skills_list.h
 * Adnan Bseisu, dab262
 * CPSC 223, PSET 3.5
 * 3/13
 *
 * This is the header file that defines the functions associated with the opaque Pirate struct.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include header files for custom types and functions
#include "pirate.h"
#include "skills_list.h"

#define INITIAL_CAPACITY 5
#define RESIZE_FACTOR 2

// Define the implementation of the skills_list
struct skills_implementation {
    char **array;  // Array of pointers to strings
    size_t length; // Number of elements in the array
    size_t capacity; // Maximum number of elements that can be stored in the array
};

// Create a new skills_list with the default initial capacity
skills_list *s_list_create(){
    skills_list *lst = malloc(sizeof(skills_list)); // Allocate memory for the list
    if (!lst) { // Check if allocation was successful
        fprintf(stderr, "Error: Failed to allocate memory for skills_list.\n");
        return NULL;
    }
    lst->capacity = INITIAL_CAPACITY;
    lst->length = 0;
    lst->array = malloc(lst->capacity * sizeof(char*)); // Allocate memory for the array of pointers
    return lst;
}

// Find the index of the given skill in the list, or return the length of the list if the skill is not found
size_t s_list_index_of(skills_list *skills, char *s){
    for (size_t i = 0; i < skills->length; i++)
    {
        if(strcmp(skills->array[i], s) == 0){ // Compare the strings
            return i;
        }
    }
    return skills->length; // Return the length of the list if the skill is not found
}

// Append a new skill to the end of the list
char *s_append(skills_list *skills, char *s) {
    if (skills->length >= skills->capacity) { // Check if the list is full
        skills->capacity *= RESIZE_FACTOR; // Increase the capacity of the list
        skills->array = realloc(skills->array, skills->capacity * sizeof(char *)); // Reallocate memory for the array of pointers
    }
    skills->array[skills->length] = malloc(strlen(s) + 1); // Allocate memory for the new string
    if (skills->array[skills->length] == NULL) { // Check if allocation was successful
        return "Failed to allocate memory";
    }
    strcpy(skills->array[skills->length], s); // Copy the string to the new memory
    skills->length++; // Increment the length of the list
    return NULL;
}

// Return a pointer to the string at the given index in the list
char *s_list_access(skills_list *skills, size_t idx){
    if (skills == NULL) { // Check if the list is NULL
        return NULL;
    }
    if (idx >= skills->length){ // Check if the index is out of bounds
        return NULL;
    }
    return skills->array[idx]; // Return the pointer to the string
}

// Swap the values of two pointers to char*
void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Compare two strings using strcmp
int compare_strings(char* str1, char* str2) {
    return strcmp(str1, str2);
}

/*
 * Sort the list of skills in alphabetical order by name
 */
void s_list_sort(skills_list* skills) {
    // Initialize indexing variables
    size_t i;
    size_t j;
    size_t min;

    // Iterate through the skills list
    for (i = 0; i < skills->length - 1; i++) {
        // Set the minimum index to the current index
        min = i;
        // Iterate through the remaining elements in the list
        for (j = i + 1; j < skills->length; j++) {
            // Compare the strings at the current index and the minimum index
            if (compare_strings(skills->array[j], skills->array[min]) < 0) {
                // Update the minimum index if necessary
                min = j;
            }
        }
        // Swap the elements at the current index and the minimum index
        swap(&skills->array[min], &skills->array[i]);
    }
}

/*
 * Return the number of skills in the list.
 */
size_t s_list_length(skills_list *skills){
    // Return the length of the skills list
    return skills->length;
}

void s_print_list(skills_list *skills) {
    // If the skills list is empty, print a message and return
    if(skills->length==0){
        printf("    Skills: (None)\n\n");
        return;
    }

    // Sort the skills list
    s_list_sort(skills);

    // Print the header for the skills list
    printf("    Skills: ");

    // Initialize a counter variable
    size_t i = 0;

    // Iterate through the skills list
    while (i < s_list_length(skills)) {
        // Initialize a rating variable
        int rating = 0;
        // Get the current skill
        char *current_skill = s_list_access(skills, i);
        // Initialize a variable to keep track of the end of the current skill group
        size_t j = i;
        // Count the number of skills with the same name as the current skill
        while (j < s_list_length(skills) && strcmp(current_skill, s_list_access(skills, j)) == 0) {
            rating++;
            j++;
        }

        // Print the current skill
        if (i == 0){
            printf("%s", current_skill);
        }
        else{
            printf("            %s", current_skill);
        }

        // Print the rating for the current skill
        for (int k = 0; k < rating; k++) {
            printf(" *");
        }

        printf("\n");
         // Move the counter to the end of the current skill group
        i = j;
    }

    // Print a newline character to separate the skills list from the next section
    printf("\n");
}

/*
 * Free all memory associated with the skills list
 */
void s_list_destroy(skills_list *skills){
    // Check if the skills list is empty
    if (skills->array == NULL){
        return;
    }

    // Free the memory associated with each skill
    for (size_t i = 0; i < skills->length; i++){
        if (skills->array[i] != NULL){
            free(skills->array[i]);
        }
    }

    // Free the memory associated with the skills list itself
    free(skills->array);
    free(skills);
}
