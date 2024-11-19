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



/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definicija strukture za čvor stoga
typedef struct racun* Position;
typedef struct racun {
    int vri;
    Position next;
} Racun;

// Funkcija za dodavanje vrijednosti na stog
void push(int vri, Position VrhStoga) {
    Racun* noviEl = (Racun*)malloc(sizeof(Racun));
    if (!noviEl) {
        printf("Failed in node creation!\n");
        return;
    }
    noviEl->vri = vri;
    noviEl->next = VrhStoga->next;
    VrhStoga->next = noviEl;
}

// Funkcija za uklanjanje (pop) sa stoga
int pop(Position VrhStoga) {
    if (VrhStoga == NULL || VrhStoga->next == NULL) {
        printf("Stog je prazan\n");
        return -1;  // Vraća -1 ako je stog prazan
    }
    Position temp = VrhStoga->next;
    int poppedValue = temp->vri;
    VrhStoga->next = temp->next;
    free(temp);
    return poppedValue;
}

// Funkcija za računanje postfiksnog izraza koristeći stog
int computePostfix(const char* expr, Position VrhStoga) {
    int i = 0, num1, num2, result;
    char token[10];

    while (expr[i] != '\0') {
        // Preskoči praznine
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // Ako je token broj, dodaj ga na stog
        if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(num, VrhStoga);
        }
        // Ako je token operator, izračunaj operaciju
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            num2 = pop(VrhStoga);
            num1 = pop(VrhStoga);

            switch (expr[i]) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/':
                if (num2 != 0)
                    result = num1 / num2;
                else {
                    printf("Error: division by zero\n");
                    return -1;
                }
                break;
            }
            push(result, VrhStoga);
            i++;  // Pomakni se na sljedeći znak
        }
        else {
            i++;  // Preskoči sve ostale znakove (nepoznate znakove)
        }
    }

    // Na kraju bi u stogu trebao biti samo jedan rezultat
    return pop(VrhStoga);
}

// Funkcija za čitanje iz datoteke
void ReadFromFile(Position VrhStoga, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    char expr[1000];
    if (fgets(expr, sizeof(expr), file) != NULL) {
        // Učitaj postfiksni izraz iz datoteke i izračunaj rezultat
        printf("Postfiksni izraz: %s\n", expr);
        int result = computePostfix(expr, VrhStoga);
        if (result != -1) {
            printf("Rezultat postfiksnog izraza: %d\n", result);
        }
    }
    fclose(file);
}

int main() {
    Racun Stog;
    Stog.next = NULL;

    // Čitaj postfiksni izraz iz datoteke i izračunaj
    ReadFromFile(&Stog, "postfix.txt");

    return 0;
}
*/
