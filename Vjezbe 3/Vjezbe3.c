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
		return 0;
	}

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;

}
int printList(position first)
{
	position temp = NULL;
	temp = first->next;

	while (temp != NULL)
	{
		printf("%s %s %d \n", temp->name, temp->lastName, temp->birthyear);
		temp = temp->next;

	}
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

int AppendList(position head, char* name, char* lastName, int by)
{
	position newPerson = NULL;
	newPerson = CreatePerson(name, lastName, by);
	position last = NULL;
	if (!newPerson) {
		printf("Failed in person creation!\n");
		return 0;
	}

	last = FindLast(head);
	newPerson->next = last->next;
	last->next = newPerson;
	return EXIT_SUCCESS;
}


position FindByLastName(position first, char* lastName)
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



int insertBehind(position head, char* lastname, char* nameNew, char* lastNameNew, int by)
{
	position newPerson = NULL;
	newPerson = CreatePerson(nameNew, lastNameNew, by);
	position prev = NULL;
	if (!newPerson) {
		printf("Failed in person creation!\n");
		return 0;
	}
	prev = FindByLastName(head, lastname);
	if (prev != NULL)
	{
		newPerson->next = prev->next;
		prev->next = newPerson;
	}
	return EXIT_SUCCESS;
}

int insertBefore(position head, char* lastname, char* nameNew, char* lastNameNew, int by)
{
	position newPerson = NULL;
	newPerson = CreatePerson(nameNew, lastNameNew, by);
	position prev = NULL;
	position behind = NULL;
	if (!newPerson) {
		printf("Failed in person creation!\n");
		return 0;
	}
	behind = FindByLastName(head, lastname);
	prev = FindPrev(head, behind);
	if (prev != NULL)
	{
		newPerson->next = prev->next;
		prev->next = newPerson;
	}
	return EXIT_SUCCESS;
}
int unos(position head)
{
	position x = head->next;
	FILE* file = fopen("popis.txt", "w");
	if (!file) {
		printf("Ne mogu otvoriti datoteku.\n");
		return 1;
	}

	while (x != NULL)
	{
		fprintf(file, "%s %s %d\n", x->name, x->lastName, x->birthyear);
		x = x->next;
	}
	

	fclose(file);
	return EXIT_SUCCESS;
}

int citanje(position head)
{
	FILE* file = fopen("popis.txt", "r");
	if (!file) {
		printf("Ne mogu otvoriti datoteku.\n");
		return 1;
	}

	char name[MAX_SIZE];
	char lastName[MAX_SIZE];
	int birthyear;

	while (fscanf(file, "%s %s %d", name, lastName, &birthyear) == 3) {
		AppendList(head, name, lastName, birthyear);
	}

	fclose(file);
	return EXIT_SUCCESS;
}
void SortirajListu(position head) {
	position p, prev, temp, end = NULL;
	int swapped;

	do {
		swapped = 0;
		p = head;

		while (p->next != end && p->next->next != NULL) {
			prev = p;
			temp = p->next;

			// Usporedimo prezimena; ako su prezimena ista, uspoređujemo imena
			if (strcmp(temp->lastName, temp->next->lastName) > 0 ||
				(strcmp(temp->lastName, temp->next->lastName) == 0 && strcmp(temp->name, temp->next->name) > 0)) {

				prev->next = temp->next;
				temp->next = temp->next->next;
				prev->next->next = temp;

				swapped = 1;
			}

			p = p->next;
		}
		end = p;
	} while (swapped);
}
int DeleteAll(position head) {
	position temp = head->next;
	position toDelete = NULL;

	while (temp != NULL) {
		toDelete = temp;
		temp = temp->next;
		free(toDelete);
	}

	head->next = NULL;
	return EXIT_SUCCESS;
}
int main()
{
	Person head = {
		.name = "",
		.lastName = "",
		.birthyear = {0},
		.next = NULL
	};
	
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
	
	insertBehind(&head, "Horvat", "Lana", "Matic", 2004);
	printList(&head);
	printf("\n\n");
	insertBefore(&head, "Matic", "Sara", "Lukenda", 2003);
	printList(&head);

	//unos(&head);
	printf("\n\n");

	printf("Lista nakon ucitavanja iz datoteke:\n");
	citanje(&head);
	printList(&head);
	SortirajListu(&head);
	printf("\n\n");
	printList(&head);
	
	DeleteAll(&head);
	printf("\n\n Bez liste:");
	printList(&head);

	
	return 0;

}
