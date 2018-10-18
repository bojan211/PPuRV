#include "DoubleLinkedList.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


// Creates empty EmployeeList
void EmployeeListCreate(EmployeeList* list)
{
	list->head = NULL;
	list->tail = NULL;
}


// Frees all memory allocated by list
void EmployeeListDestroy(EmployeeList* list)
{
	if (list->head == NULL)
		return;
	employee* current = list->tail;
	while (current != list->head)
	{
		current = current->prev;
		free(current->next);
	}
	free(current);
	list->head = NULL;
	list->tail = NULL;
}


//Function inserts employee element to specific position in the list
bool EmployeeListInsert(EmployeeList* list, employee* location, const char* name, const char* group, float experience)
{
	employee* element = malloc(sizeof(employee));
	strncpy(element->name, name, NAME_SIZE-1);
	element->name[NAME_SIZE-1] = '\0';
	strncpy(element->group, group, GROUP_NAME_SIZE);
	element->group[GROUP_NAME_SIZE-1] = '\0';
	element->experience = experience;
	
	if (location == NULL)
	{
		element->next = list->head;
		element->prev = NULL;
		list->head = element;
	}
	else
	{
		element->next = location->next;
		element->prev = location;
		location->next = element;
	}

	if(element->next != NULL)
	{
		element->next->prev = element;
	} 
	else
	{
		list->tail = element;
	}
	
	return true;
}


//Function deletes employee element from specific position in the list
bool EmployeeListDelete(EmployeeList* list, employee* location)
{
	if(location == NULL)
		return false;
	
	if (location == list->head)
	{
		list->head = location->next;
	}
	else
	{
		location->prev->next = location->next;
	}
    if(location == list->tail)
	{
		list->tail = location->prev;
	}
	else
	{
		location->next->prev = location->prev;
	}
	
	free(location);
	return true;
}

//Function returns true if the list is empty
bool EmployeeListEmpty  (EmployeeList* list)
{
	return (list->head == NULL);
}

// Prints all list elements on standard out
void EmployeeListDump(EmployeeList* list)
{
	employee* current = list->head;
	while (current != NULL)
	{
		printf("*****************************************************\n");
		printf("NAME:       %s\n", current->name);
		printf("GROUP:      %s\n", current->group);
		printf("EXPERIENCE: %f\n", current->experience);
		current = current->next;
	};
	
}
