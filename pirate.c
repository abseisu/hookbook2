/*
 * pirate.c
 * Adnan Bseisu, dab262
 * CPSC 223, PSET 3.5
 * 3/13
 * Implements the Pirate struct and associated functions (given that I have made it opaque)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pirate.h"
#include "skills_list.h"

// The Pirate struct can be adjusted for more fields in the future
struct Pirate
{
    char* name;             // The pirate's name
    char* title;            // The pirate's title
    pirate* captain;        // The pirate's captain
    char* vessel;           // The pirate's vessel
    char* port;             // The pirate's favorite port of call
    int num_treasures;      // The number of treasures the pirate has
    skills_list* skills;    // A list of the pirate's skills
};

// Create the list of skills for the pirate
void create_skills(pirate *p)
{
    p->skills = s_list_create();
}

// Print the captain's information
void print_captain_info(pirate* p)
{
    if (p->captain == NULL)
    {
        printf("    Captain: (None)\n");
        return;
    }

    printf("    Captain: %s\n", get_name(p->captain));
    printf("        Captain's Title: %s\n", get_title(p->captain));
    printf("        Captain's Favorite Port of Call: %s\n", get_port(p->captain));
}

// Get the size of the Pirate struct
int size_of_pirate()
{
    return sizeof(pirate);
}

// Change the pirate's name
void change_name(pirate* p, char* new_name)
{
    // Allocate memory for the new name
    p->name = malloc(64 * sizeof(char)); 
    // Copy the new name into the allocated memory
    strcpy(p->name, new_name);
}

// Change the pirate's favorite port of call
void change_port(pirate* p, char* new_port)
{
    // Allocate memory for the new port
    p->port = malloc(64 * sizeof(char)); 
    // Copy the new port into the allocated memory
    strcpy(p->port, new_port);
}

// Change the pirate's title
void change_title(pirate* p, char* new_title)
{
    // Allocate memory for the new title
    p->title = malloc(64 * sizeof(char)); 
    // Copy the new title into the allocated memory
    strcpy(p->title, new_title);
}

// Change the pirate's vessel
void change_vessel(pirate* p, char* new_vessel)
{
    // Allocate memory for the new vessel
    p->vessel = malloc(64 * sizeof(char)); 
    // Copy the new vessel into the allocated memory
    strcpy(p->vessel, new_vessel);
}

// Change the number of treasures the pirate has
void change_treasure(pirate* p, int new_treasure)
{
    p->num_treasures = new_treasure;
}

// Change the pirate's captain
void change_captain(pirate* p, pirate* c)
{
    // Point to the new captain
    p->captain = c;
}

// Get the list of skills for the pirate
skills_list* get_skills(pirate* p)
{
    return p->skills;
}

// Get the pirate's name
char* get_name(pirate* p)
{
    return p->name;
}

// Get the pirate's port
char* get_port(pirate* p){
    if (p->port == NULL){
        // Default value
        return "(None)";
    }
    return p->port;
}

// Get the pirate's title
char* get_title(pirate* p){
    if (p->title == NULL){
        // Default value
        return "(None)";
    }
    return p->title;
}

// Get the pirate's vessel
char* get_vessel(pirate* p){
    if (p->vessel == NULL){
        // Default value
        return "(None)";
    }
    return p->vessel;
}

// Get the pirate's number of treasures
int get_treasure(pirate* p){
    return p->num_treasures;
}

// Get the pirate's captain (if any)
pirate* get_captain(pirate* p){
    if (p->captain == NULL){
        // Default, no captain
        return NULL;
    }
    return p->captain;
}
