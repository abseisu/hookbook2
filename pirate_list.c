/*
* pirate_list.c
* Adnan Bseisu, dab262
* CPSC 223, PSET 3.5
* 3/13
* Implements functions declared in the pirate_list.h file, and implements our Array List
*/

#include <stdio.h>
#include <string.h>


#include "pirate.h"
#include "pirate_list.h"

#define INITIAL_CAPACITY 25

#define RESIZE_FACTOR 2

struct implementation {
    pirate **array;
    size_t len;
    size_t capacity;
};

// Allocate memory for a new pirate_list and return a pointer to it.
pirate_list *list_create()
{
    pirate_list *list = (pirate_list*)malloc(sizeof(pirate_list));
    list->len = 0;
    list->capacity = INITIAL_CAPACITY;
    list->array = malloc(list->capacity * sizeof(pirate*));
    return list;
}


// Return the index of the pirate with the same name as p, or a value greater than or equal to the length of the list if there is no pirate in the list with a matching name.
size_t list_index_of(pirate_list *pirates, pirate *p){
    for (size_t i = 0; i < list_length(pirates); i++)
    {
        if(strcmp(get_name(list_access(pirates, i)), get_name(p)) == 0){
            return i;
        }
    }
    return pirates->len;
}

/*
 * Only if there is no pirate in the list with the same name as p, insert pirate p into the list at index idx by copying the pointer, shifting the latter part of the list one “slot” to the right.
 * If there is a pirate in the list with the same name as p, do nothing, and return a pointer to the pirate that was not inserted.
 * If the pirate was inserted into the list, return NULL
 */

void list_expand_if_necessary(pirate_list* pirates){
    // Check if the list needs to be expanded
    if (pirates->len >= pirates->capacity)
    {
        // Print a message to stderr
        fprintf(stderr, "Expand to %lu\n", pirates->capacity * RESIZE_FACTOR);
        // Increase the capacity of the list
        pirates->capacity *= RESIZE_FACTOR;
        // Reallocate memory for the array of pointers to pirates
        pirates->array = realloc(pirates->array, pirates->capacity * sizeof(pirate*));
    }   
}

void list_contract_if_necessary(pirate_list* pirates){
    // Check if the list needs to be contracted
    if (pirates->len - 1 <= (pirates->capacity / (RESIZE_FACTOR)))
    {
        // Check if the capacity of the list after contracting is still greater than or equal to the initial capacity
        if (pirates->capacity / RESIZE_FACTOR >= INITIAL_CAPACITY)
        {
            // Print a message to stderr
            fprintf(stderr, "Contract to %lu\n", pirates->capacity / RESIZE_FACTOR);
        }
        // Decrease the capacity of the list
        pirates->capacity /= RESIZE_FACTOR;
        // Reallocate memory for the array of pointers to pirates
        pirates->array = realloc(pirates->array, pirates->capacity * sizeof(pirate*));
    }
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx){

    // If pirate is already in the list, then we need to return a pointer to it
    size_t index = list_index_of(pirates, p);
    if (index < list_length(pirates)) {
        return list_access(pirates, index);
    }

    int length = list_length(pirates);

    list_expand_if_necessary(pirates);

    // Pirate is not already in list, so we need to insert it

    if (index == length){
        pirates->array[index] = p;
        pirates->len++;
        return NULL;
   }
   if (index < length){
        // We are inserting, so we need to push all pirates to the right of idx one to the right in the array
        for (size_t i = list_length(pirates) - 1 ; i >= idx; i--) {
            pirates->array[i + 1] = pirates->array[i];
        }
        pirates->array[idx] = p;
        pirates->len++;
        // p successfully inserted at idx
        return NULL;
   }

   return p;

    
}

/*
 * Remove the pirate from the list with the same name as p, and return a pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL
 */
pirate *list_remove(pirate_list *pirates, pirate *p){

    int length = list_length(pirates);

    // Index of pirate to remove
    size_t idx = list_index_of(pirates, p);

    // check if index is invalid
    if (idx >= length){
        return NULL;
    }

    list_contract_if_necessary(pirates);
    
    // if idx happens to be last index in array, then we can just decrement the lengtb
    if (idx == length - 1){
        pirates->len--;
        return p;
    }
    // if idx isn't the last index, we need to shift elements right of index left
    for (size_t i = idx ; i < list_length(pirates); i++) {
        pirates->array[i] = pirates->array[i+1];
    }
    pirates->len--;
    return p;
}

/*
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).
 */
pirate *list_access(pirate_list *pirates, size_t idx){
    
    // First, check if idx is invalid. 
    if (idx >= pirates->len){
        return NULL;
    }
    
    // idx is valid 

    //return a pointer to the desired pirate
    return pirates->array[idx];

    
}


// Merges two pirate arrays into a single sorted array
void merge(pirate **left, int leftLen, pirate **right, int rightLen, char* s) {
    // Allocate memory for the result array
    pirate **result = (pirate **) malloc(sizeof(pirate *) * (leftLen + rightLen));
    // Initialize counters
    int i = 0;  // Counter for left array
    int j = 0;  // Counter for right array
    int k = 0;  // Counter for result array

    // Merge the left and right arrays into the result array
    while (i < leftLen && j < rightLen) {
        // If the criteria passed in at runtime is to sort by increasing lexicographic order of the pirate names, then use strcmp and get_name to do this
        if (strcmp(s,  "-n") == 0){
            if (strcmp(get_name(left[i]), get_name(right[j])) <= 0) {
            result[k++] = left[i++];  // Add element from left array to result array
            } 
            else {
                result[k++] = right[j++];  // Add element from right array to result array
            }
        }
        // If the criteria passed in at runtime is to sort by increasing lexicographic order of the vessel names, then use strcmp and get_vessel to do this
        else if (strcmp(s,  "-v") == 0){
            if (strcmp(get_vessel(left[i]), get_vessel(right[j])) <= 0) {
                result[k++] = left[i++];  // Add element from left array to result array
            } 
            else {
                result[k++] = right[j++];  // Add element from right array to result array
            }
        }
        // If the criteria passed in at runtime is to sort by decreasing of the number of treasures, then just compare num_treasures
        else if (strcmp(s,  "-t") == 0){
            if (get_treasure(left[i]) >= get_treasure(right[j])) {
                result[k++] = left[i++];  // Add element from left array to result array
            } 
            else {
                result[k++] = right[j++];  // Add element from right array to result array
            }
        } 
    }

    // Add any remaining elements from left array to result array
    while (i < leftLen) {
        result[k++] = left[i++];
    }

    // Add any remaining elements from right array to result array
    while (j < rightLen) {
        result[k++] = right[j++];
    }

    // Copy the sorted result array back into the left array
    for (i = 0; i < leftLen + rightLen; i++) {
        left[i] = result[i];
    }

    // Free memory allocated for the result array
    free(result);
}

// Helper function to merge sort pirates
void merge_sort(pirate **pirates, int len, char *s) {
    if (len < 2) {
        return;
    }

    // Split the array into two halves
    int mid = len / 2;
    pirate **left = pirates;
    pirate **right = pirates + mid;

    // Recursively sort the left and right halves
    merge_sort(left, mid, s);
    merge_sort(right, len - mid, s);

    // Merge the sorted left and right halves back into a single array
    merge(left, mid, right, len - mid, s);
}

// Sort the list of pirates in alphabetical order by name
void list_sort(pirate_list *pirates, char *s){
    pirate **array = pirates->array;
    merge_sort(array, list_length(pirates), s);
}


// Return the number of pirates in the list.
size_t list_length(pirate_list *pirates){
    return pirates->len;
}

// Free all memory associated with the pirate_list, but leave the memory associated with the pirates in the list untouched
void list_destroy(pirate_list *pirates){

   for (int i = 0; i < pirates->len; i++) {
        pirate *p = pirates->array[i];
        free(get_name(p));
        // free title char*
        if(strcmp(get_title(p), "(None)") != 0){
            free(get_title(p));
        }
        // free vessel char*
        if(strcmp(get_vessel(p), "(None)") != 0){
            free(get_vessel(p));
        }
        // free port char*
        if(strcmp(get_port(p), "(None)") != 0){
            free(get_port(p));
        }
        // destroy the skills list
        s_list_destroy(get_skills(p));
        // free the actual pirate struct at this index
        free(p);
    }
    // free the array itself
    free(pirates->array);
    // free the pirate list struct itself
    free(pirates);
}



