#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50

typedef struct _polinom* Position;

typedef struct _polinom {
    int coeff;
    int exp;
    Position next;
} Polinom;

Position CreatePolinomElement(int coeff, int exp) {
    Position newElement = (Position)malloc(sizeof(Polinom));
    if (!newElement) {
        printf("Allocation error!\n");
        return NULL;
    }
    newElement->coeff = coeff;
    newElement->exp = exp;
    newElement->next = NULL;
    return newElement;
}

void InsertSorted(Position head, Position newElement) {
    Position temp = head;
    while (temp->next != NULL && temp->next->exp > newElement->exp) {
        temp = temp->next;
    }
    if (temp->next != NULL && temp->next->exp == newElement->exp) {
        temp->next->coeff += newElement->coeff; //ako je isti eksponent onda se zbraja
        if (temp->next->coeff == 0) { //ako se oni ponište i koeficijent bude 0 ond se element brise
            Position toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
        }
        free(newElement);
    }
    else {
        newElement->next = temp->next;
        temp->next = newElement;
    }
}

void PrintPolinom(Position head) {
    Position clan = head; //slala se pozicija prvog clana
    while (clan != NULL) {
        printf("%dx^%d ", clan->coeff, clan->exp);
        clan = clan->next;
        if (clan) printf("+ ");
    }
    printf("\n");
}


void ReadFromFile(Position head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    int coeff, exp;

    while (fscanf(file, "%d %d", &coeff, &exp) == 2) {
        Position newElement = CreatePolinomElement(coeff, exp);
        InsertSorted(head, newElement);
    }

    fclose(file);
}


Position AddPolinoms(Position head1, Position head2) {
    Polinom resultHead = { 0, 0, NULL };
    Position temp1 = head1, temp2 = head2;
    while (temp1) {
        InsertSorted(&resultHead, CreatePolinomElement(temp1->coeff, temp1->exp)); //U InsertSorted se zbrajaju nakon sta dodamo oba polinoma
        temp1 = temp1->next;
    }
    while (temp2) {
        InsertSorted(&resultHead, CreatePolinomElement(temp2->coeff, temp2->exp));
        temp2 = temp2->next;
    }
    return resultHead.next;
}


Position MultiplyPolinoms(Position head1, Position head2) {
    Polinom resultHead = { 0, 0, NULL };
    for (Position temp1 = head1; temp1 != NULL; temp1 = temp1->next) {
        for (Position temp2 = head2; temp2 != NULL; temp2 = temp2->next) {
            InsertSorted(&resultHead, CreatePolinomElement(temp1->coeff * temp2->coeff, temp1->exp + temp2->exp)); //saljemo pomnozene polinome jer se mnoze svak sa svakim
        }
    }
    return resultHead.next;
}


void FreeList(Position head) {
    while (head) {
        Position temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Polinom head1 = { 0, 0, NULL };
    Polinom head2 = { 0, 0, NULL };


    ReadFromFile(&head1, "polinom1.txt");
    ReadFromFile(&head2, "polinom2.txt");

    printf("Polinom 1: ");
    PrintPolinom(head1.next);

    printf("Polinom 2: ");
    PrintPolinom(head2.next);


    Position sum = AddPolinoms(head1.next, head2.next);
    printf("Zbroj: ");
    PrintPolinom(sum);


    Position product = MultiplyPolinoms(head1.next, head2.next);
    printf("Umnozak: ");
    PrintPolinom(product);


    FreeList(head1.next);
    FreeList(head2.next);
    FreeList(sum);
    FreeList(product);

    return 0;
}

