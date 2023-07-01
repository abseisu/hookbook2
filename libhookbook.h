/*
* libhookbook.h
* Adnan Bseisu, dab262
* CPSC 223, PSET 3.5
* 3/13
* Defines two helper functions implemented in libhookbook.c and used in hookbook.c
*/

#ifndef __LIB_HOOKBOOK_H__
#define __LIB_HOOKBOOK_H__

#include <stdlib.h>

// reads in the profiles of the pirates from the first file given in through the command-line and the pirate/captain pairs through the second file
int read_profiles(char* file_1, char* file_2, pirate_list* pirates);

// prints each pirate's information according to the criteria outlined in the PSET specification
void print_list(pirate_list *pirates, char* s);

#endif
