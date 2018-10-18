#include <stdio.h>

#include "DoubleLinkedList.h"

int main(void)
{
	EmployeeList list;
	employee e1 = {"Petar","Bojanic",99};
	employee e2 = {"Nikola","Jovanovic",89};
	employee e3 = {"Milan","Bajic",97};
	employee e4 = {"Boris","Milic",34};
	employee e5 = {"Dragan","Bojic",55};
	
	EmployeeListCreate(&list);
	
	printf("Employee list %s!\n", EmployeeListEmpty(&list)?"is empty":"is not empty");
	
	EmployeeListInsert(&list, NULL, "Tesa", "Tesanovic", 99);
	EmployeeListInsert(&list, list.tail, "Aleksandar", "Pavkovic", 89);
	EmployeeListInsert(&list, list.tail, "Ljubodrag","Simonovic",97);
	EmployeeListInsert(&list, list.tail, "Momcilo","Milinkovic",34);
	EmployeeListInsert(&list, list.tail, "Milan","Gutovic",55);
	
	EmployeeListDump(&list);

	printf("\n\n");
	printf("Employee list %s!\n", EmployeeListEmpty(&list)?"is empty":"is not empty");
	printf("\n\n");
	
	EmployeeListDelete(&list, list.head);
	EmployeeListDelete(&list, list.head->next);
	EmployeeListDelete(&list, list.tail->prev);

	EmployeeListDump(&list);
	
	char name[NAME_SIZE];
	char group[GROUP_NAME_SIZE];
	float experience;
	for(int i = 0; i < 3; i++)
	{
		printf("Add employee %d \n", i);
		printf("Enter name (max 20): \n");
        scanf("%s", name);
		printf("Enter last name (max 20): \n");
        scanf("%s", group);
		printf("Enter experience: \n");
        scanf("%f", &experience);
	    EmployeeListInsert(&list, list.tail, name, group, experience);
	}
	
	EmployeeListDump(&list);
	
	int index = 0;
	for(int i = 0; i < 3; i++)
	{
		printf("Remove employee: \n", i);
		printf("Enter index: \n"); 
		scanf("%d", &index);
		
		employee* current = list.head;
		while (index > 0 && current!=NULL)
		{
			current = current->next;
			index--;
		}
		if(current!=NULL)
		{
			EmployeeListDelete(&list, current);
		}
	}
	
	EmployeeListDump(&list);
	
	printf("\n\n");
	
	printf("Employee list %s!\n", EmployeeListEmpty(&list)?"is empty":"is not empty");

	return 0;
}
