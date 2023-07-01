/*
 * skills_list.h
 * Adnan Bseisu, dab262
 * CPSC 223, PSET 3.5
 * 3/13
 *
 * This is the header file that defines the functions associated with the opaque Pirate struct.
 */

#ifndef __SKILLS_LIST_H__
#define __SKILLS_LIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "pirate.h"


// Type of a list of skills
typedef struct skills_implementation skills_list;

/*
 * Allocate memory for a new skills_list and return a pointer to it.
 */
skills_list *s_list_create();

/*
 * Finds the index of the string in a skills list with the same value as s
 */
size_t s_list_index_of(skills_list *skills, char *s);

/*
 * Appends a string to the end of a skills list
 */
char *s_append(skills_list *skills, char *s);

/*
 * Accesses a string at a specified index of a skills list
 */
char *s_list_access(skills_list *skills, size_t idx);

/*
 * Sort the list of skills in alphabetical order by name
 */
void s_list_sort(skills_list* skills);

/*
 * Return the number of skills in the list.
 */
size_t s_list_length(skills_list *skills);

/*
 * Frees all memory associated with the skills list
 */
void s_list_destroy(skills_list *skills);

/*
 * Prints the skills in a skills list according to the formatting criteria given by the PSET specification 
 */
void s_print_list(skills_list *skills);

#endif
