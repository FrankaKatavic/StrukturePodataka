#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct racun* Position;

typedef struct racun {
	int vri;
	Position next;
} Racun;


int push(int vri, Position VrhStoga) {
	Racun* noviEl = (Racun*)malloc(sizeof(Racun));
	if (!noviEl) {
		printf("Failed in node creation!\n");
		return 0;
	}
	noviEl->vri = vri;
	noviEl->next = VrhStoga->next;
	VrhStoga->next = noviEl;
};


int pop(Position VrhStoga) {
	if (VrhStoga == NULL) {
		printf("Stog je prazan\n");
		return EXIT_FAILURE;
	}
	Position temp = VrhStoga;
	int poppedValue = temp->vri;
	VrhStoga = temp->next;
	free(temp);
	return poppedValue;
};


/*
int dodajStogu(position head){
position noviCvor = NULL;
noviCvor = (Position)malloc(sizeof(Cvor));
Position prev = NULL;
if (!noviCvor) {
printf("Failed in node creation!\n");
return 0;
}
if (prev != NULL){
noviCvor->next = prev->next;
prev->next = noviCvor;
}
return EXIT_SUCCESS;
}


void ReadFromFile(Position head, const char* filename) {
FILE* file = fopen(filename, "r");
if (!file) {
printf("Cannot open file %s\n", filename);
return;
}

int vrijednost;

while () {

}

fclose(file);
}
*/


int main() {

	retrun 0;
}