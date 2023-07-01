/*
* hookbook.c
* Adnan Bseisu, dab262
* CPSC 223, PSET 3.5
* 3/13
* Main file which is responsible for taking in command line arguments, reading from two infiles, and sorting and printing out the pirate profiles in that file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pirate_list.h"
#include "libhookbook.h"

int main(int argc, char *argv[]){

    // check that at least three command line arguments are entered
    if (argc < 4)
    {
        fprintf(stderr, "Invalid arguments\n");
        exit(1);
    }

    // check that third command-line argument is valid
    if (strcmp(argv[3], "-n") != 0 && strcmp(argv[3], "-v") != 0 && strcmp(argv[3], "-t") != 0){
        fprintf(stderr, "Invalid argument: %s\n", argv[3]); 
        exit(1);
    }
    // create list of pirates using list create function
    pirate_list *pirates = list_create();

    // read the pirate profiles and pirate/captain pares in the given files and assign the return value to an int so that we can check if the profiles if they were successfully read 
    int check_read_error = read_profiles(argv[1], argv[2], pirates);

    // pirate file cannot be opened, program exits with code 1
    if (check_read_error == 1){
        exit(1);
    }

    // pirate file correctly opened, so we can print the sorted pirate names in pirates
    print_list(pirates, argv[3]);

    // destroy pirate list
    list_destroy(pirates);
}
