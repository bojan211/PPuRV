#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

#include <stdint.h>
#include <stdbool.h>

#define NAME_SIZE 20
#define GROUP_NAME_SIZE 20

typedef struct employee
{
	char    name[NAME_SIZE];
	char    group[GROUP_NAME_SIZE];
	float 	experience;
	struct 	employee* prev;
	struct 	employee* next;
} employee;

typedef struct EmployeeList
{
	employee* head;  // Pointer to first element in list
	employee* tail;  // Pointer to last element in list
} EmployeeList;

// Creates empty EmployeeList
void EmployeeListCreate(EmployeeList* list);

// Frees all memory allocated by list
void EmployeeListDestroy(EmployeeList* list);

//Function inserts employee element to specific position in the list
bool EmployeeListInsert(EmployeeList* list, employee* location, const char* name, const char* group, float experience);

//Function deletes employee element from specific position in the list
bool EmployeeListDelete(EmployeeList* list, employee* location);

//Function returns true if the list is empty
bool EmployeeListEmpty  (EmployeeList* list);

// Prints all list elements on standard out
void EmployeeListDump (EmployeeList* list);

#endif /*DOUBLELINKEDLIST_H_*/
