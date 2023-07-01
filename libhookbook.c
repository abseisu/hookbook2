/*
* libhookbook.c
* Adnan Bseisu, dab262
* CPSC 223, PSET 3.5
* 3/13
* Implements the functions read_profiles and print_list, both of which are used in main to read the pirate profiles from the two infiles and then print them once sorted.
*/

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "pirate_list.h"
#include "skills_list.h"
#include "libhookbook.h"
#include "pirate.h"

#define MAX_VALUE_LENGTH 64
#define MAX_LABEL_LENGTH 64

int read_profiles(char* file_1, char* file_2, pirate_list* pirates){
    // read file from command line
    FILE* pirate_file = fopen(file_1, "r");

    // check that file was correctly read
    if (pirate_file == NULL)
    {
        // Print an error to stderr and exit
        fprintf(stderr, "Invalid filename: %s", file_1);
        exit(1);
    }
    // create array that will hold string of each line in file (add 2, 1 for null terminator and 1 for colon)
    char line[MAX_LABEL_LENGTH + MAX_VALUE_LENGTH + 2];

    // current pirate 
    pirate* curr_p = NULL;

    // Read lines from the file until there are no more left to read
    while (fscanf(pirate_file, "%130[^\n]\n", line) > 0){

        char label[MAX_LABEL_LENGTH + 1];
        char value[MAX_VALUE_LENGTH + 1];

        // assign values of label and value to the label and value char arrays by using sscanf 
        if (sscanf(line, "%[^:]:%[^\n]", label, value) != 2) {
            exit(1);
        }

        // Check the label to see if this is a new profile (if label is name)
        if (strcmp(label, "name") == 0){
            // If not the first profile, add the pirate we just read to the pirate list   
            if (curr_p != NULL){
                // Only insert the current pirate into the list if it isn't already in the list
                if (list_index_of(pirates, curr_p) >= list_length(pirates)){
                    curr_p = list_insert(pirates, curr_p, list_length(pirates));
                }
                
            }
            curr_p = malloc(size_of_pirate());
            create_skills(curr_p);
            change_treasure(curr_p, 0);
            // assign name to current pirate
            change_name(curr_p, value);
        }

        if (strcmp(label, "vessel") == 0){
            // assign name to current pirate
            change_vessel(curr_p, value);
        }

        if (strcmp(label, "title") == 0){
            // assign title to current pirate
            change_title(curr_p, value);
        }

        if (strcmp(label, "port") == 0){
            // assign port to current pirate
            change_port(curr_p, value);
        }

        if (strcmp(label, "treasure") == 0){
            // assign treasure to current pirate
            change_treasure(curr_p, atoi(value));
        }

        if (strcmp(label, "skill") == 0){
            //append skills, indicated by labels, to a skills list
            if (s_append(get_skills(curr_p), value) != NULL){
                exit(1);
            }
        }
    }

    // insert the last pirate profile into the pirate list, only if it isn't already in the list
    if (list_index_of(pirates, curr_p) >= list_length(pirates)){
        curr_p = list_insert(pirates, curr_p, list_length(pirates));
    }

    // Close the first file
    fclose(pirate_file);

    // read second file from command line
    FILE* captain_file = fopen(file_2, "r");
     // check that file was correctly read
    if (captain_file == NULL)
    {
        // Print an error to stderr and exit
        fprintf(stderr, "Invalid filename: %s", file_2);
        exit(1);
    }

    // create temporary dummy pirate and captain pirate pointers
    pirate *temp_p = malloc(size_of_pirate());
    pirate *temp_c = malloc(size_of_pirate());

    // Read lines from the file until there are no more left to read
    while (fscanf(captain_file, "%130[^\n]\n", line) > 0){

        // character arrays to keep track of pirate/captain pairs
        char pir[MAX_VALUE_LENGTH + 1];
        char cap[MAX_VALUE_LENGTH + 1];

        // assign values of pirate and captain names to the pir and cap char arrays by using sscanf 
        if (sscanf(line, "%[^/]/%[^\n]", pir, cap) != 2) {
            exit(1);
        }

        // set the names of these dummy pirates to the names of the pirate and captain on the line
        change_name(temp_p, pir);
        change_name(temp_c, cap);
        printf("\n");

        //find indicies of corresponding pirates in the pirates list
        size_t p_idx = list_index_of(pirates, temp_p);
        size_t c_idx = list_index_of(pirates, temp_c);

        // assign the identified captain to the identified pirate in the pirates list
        change_captain(list_access(pirates, p_idx), list_access(pirates, c_idx));

        free(get_name(temp_p)); 
        free(get_name(temp_c));
    }

    // free dummy pointers

    free(temp_p);
    free(temp_c);

    // close captain file
    fclose(captain_file);

    // success
    return 0;

}

void print_list(pirate_list *pirates, char* s) {

    // Sort the `pirates` list based on criteria determined at runtime (passded in via char *s)
    list_sort(pirates, s);
    
    // Loop through each element of the `pirates` list
    for (int i = 0; i < list_length(pirates); i++) {
        
        // Print the pirate's name
        printf("Pirate: %s\n", get_name(list_access(pirates, i)));
        
        // Print the pirate's title
        printf("    Title: %s\n", get_title(list_access(pirates, i)));
        
        // Call a function to print the pirate's captain information
        print_captain_info(list_access(pirates, i));
        
        // Print the pirate's vessel
        printf("    Vessel: %s\n", get_vessel(list_access(pirates, i)));
        
        // Print the pirate's treasure
        printf("    Treasure: %d\n", get_treasure(list_access(pirates, i)));
        
        // Print the pirate's favorite port of call
        printf("    Favorite Port of Call: %s\n", get_port(list_access(pirates, i)));
        
        // Print the pirate's skills
        s_print_list(get_skills(list_access(pirates, i)));
    }
}
