#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

struct _person;
typedef struct _person* position;
typedef struct _person 
{
	char name[MAX_SIZE];
	char lastName[MAX_SIZE];
	int birthyear;

	position next;
}Person;

position CreatePerson(char* name, char*lastName, int by) {
	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Bad allocation!\n");
		return NULL;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->birthyear = by;
	newPerson->next = NULL;
	
	return newPerson;

}

int PrependList(position head, char* name, char*lastName, int by) {
	position newPerson = NULL;
	newPerson = CreatePerson(name, lastName, by);
	if (!newPerson) {
		printf("Failed in person creation!\n");
		return NULL;
	}

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;

}
int printList(position first)
{
	position temp = NULL;
	temp = first;

	while (temp != NULL)
	{
		printf("%s %s %d", temp->name, temp->lastName, temp->birthyear);
		temp = temp->next;

	}
	return EXIT_SUCCESS;

}

int AppendList(position head, char* name, char*lastName, int by) 
{
	position newPerson = NULL;
	newPerson = CreatePerson(name, lastName, by);
	position last = NULL;
	if (!newPerson) {
		printf("Failed in person creation!\n");
		return NULL;
	}

	last = FindLast(head);
	newPerson->next = last->next;
	last->next = newPerson;

}

position FindLast(position head)
{
	position last = NULL;
	last = head;

	while (last->next != NULL)
	{
		last = last->next;
	}
	return last;
}

position FindByLastName(position first, char* name, char*lastName, int by)
{
	position temp = NULL;
	temp = first;
	while (temp)
	{
		if(strcmp(lastName, temp->lastName)==0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
int Delete(position head, char* name) {
	position prev = NULL;
	position toDelete = NULL;
	prev = FindPrev(head, name);
	prev->next = toDelete->next;
	free(toDelete);
}
int main()
{
	Person head = {
		.name = {0},
		.lastName = {0},
		.birthyear = {0},
		.next = NULL
	};

	return 0;

}