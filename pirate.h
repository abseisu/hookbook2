/*
 * pirate.h
 * Adnan Bseisu, dab262
 * CPSC 223, PSET 3.5
 * 3/13
 *
 * This is the header file that defines the functions associated with the opaque Pirate struct.
 */

#ifndef __PIRATE_H__
#define __PIRATE_H__

#include "skills_list.h" // include header file for skills list

// Define the Pirate struct as an opaque data type to be implemented in pirate.c
struct Pirate;

// Define the Pirate type as a pointer to the Pirate struct
typedef struct Pirate pirate;

// Declare functions associated with the Pirate struct

// Create a skills list for a given pirate
void create_skills(pirate *p);

// Print the captain's information
void print_captain_info(pirate* p);

// Get the size of a Pirate struct
int size_of_pirate();

// Change the name of the pirate being pointed to
void change_name(pirate* p, char* new_name);

// Get the name of the pirate being pointed to
char* get_name(pirate* p);

// Get the port of the pirate being pointed to
char* get_port(pirate* p);

// Get the vessel of the pirate being pointed to
char* get_vessel(pirate* p);

// Get the title of the pirate being pointed to
char* get_title(pirate* p);

// Get the captain of the pirate being pointed to
pirate* get_captain(pirate* p);

// Get the treasure of the pirate being pointed to
int get_treasure(pirate* p);

// Change the captain of the pirate being pointed to
void change_captain(pirate* p, pirate* c);

// Get the skills list of the pirate being pointed to
skills_list* get_skills(pirate* p);

// Change the vessel of the pirate being pointed to
void change_vessel(pirate* p, char* new_vessel);

// Change the port of the pirate being pointed to
void change_port(pirate* p, char* new_port);

// Change the title of the pirate being pointed to
void change_title(pirate* p, char* new_title);

// Change the treasure of the pirate being pointed to
void change_treasure(pirate* p, int new_treasure);

// Print the captain's information
void print_captain_info(pirate* p);

// Free the memory allocated to a Pirate struct
void free_pirate(pirate *p);

#endif
