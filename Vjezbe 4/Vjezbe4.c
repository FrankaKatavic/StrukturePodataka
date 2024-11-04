#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

//struct _polinom;
//typedef struct _polinom* position;
typedef struct _polinom {
	int el;
	int coeff;

}Polinom;
/*
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
 */

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


int InsertSorted(Position head, Position nE) {
	Position temp = head;
	while (temp->next && temp->next->exp < nE->) {
		temp = temp->next;
	}
	if (temp->next == NULL || temp->next->exp != nE->exp) {
		insertBehind(temp, nE);
	}
	else {
		int resultCoeff = nE->coeff + temp->next->coeff;
		if (resultCoeff == 0)
			DeleteAfter(temp);
		    free(nE);
		else{
			temp->next->coeff = resultCoeff;
			free(nE);
		}
	}
}

fgets(buffer, MAX_LINE, file);
while (strlen(buffer) > 0) {
	int status = sscanf(buffer, " %d %d %n", &c & e, &numBytes);
}

