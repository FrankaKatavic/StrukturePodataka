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

position CreatePerson(char* name, char* lastName, int by) {
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

int PrependList(position head, char* name, char* lastName, int by) {
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

int AppendList(position head, char* name, char* lastName, int by)
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
	return EXIT_SUCCESS;
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

position FindByLastName(position first, char* name, char* lastName, int by)
{
	position temp = NULL;
	temp = first;
	while (temp)
	{
		if (strcmp(lastName, temp->lastName) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
int Delete(position head, position name) {
	position prev = NULL;
	position toDelete;
	prev = FindPrev(head, name);

	if (prev != NULL) {
		toDelete = prev->next;
		prev->next = prev->next->next;
		free(toDelete);
	}
	return 0;

}

position FindPrev(position head, position wanted) {
	position temp = head;

	while (temp->next != NULL) {
		if (temp->next == wanted) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}






int main()
{
	Person head = {
		.name = "",
		.lastName = "",
		.birthyear = 0,
		.next = NULL
	};
	/*
	// Testiranje funkcija
	PrependList(&head, "Ana", "Kovac", 1990);
	AppendList(&head, "Jana", "Peric", 1985);
	AppendList(&head, "Pero", "Horvat", 2000);

	printf("Lista:\n");
	printList(&head);

	// Brisanje osobe
	position toDelete = FindByLastName(&head, "Peric");
	if (toDelete) {
		Delete(&head, toDelete);
	}

	printf("\nNova lista:\n");
	printList(&head);
	*/
	return 0;

}
