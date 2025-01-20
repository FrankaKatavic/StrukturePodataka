#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _grad* PositionG;

typedef struct _grad { // stablo gradova
    char naziv[50];
    int broj_stanovnika;
    PositionG left;
    PositionG right;
} Grad;

typedef struct _drzava* PositionD;

typedef struct _drzava { // lista država
    char naziv[50];
    PositionG root;
    PositionD next;
} Drzava;

PositionG createGrad(char* naziv, int broj_stanovnika) {
    PositionG q = (PositionG)malloc(sizeof(Grad));
    if (!q) {
        printf("Greska u alokaciji memorije!\n");
        return NULL;
    }
    strcpy(q->naziv, naziv);
    q->broj_stanovnika = broj_stanovnika;
    q->left = q->right = NULL;
    return q;
}

PositionD createDrzava(char* naziv) {
    PositionD q = (PositionD)malloc(sizeof(Drzava));
    if (!q) {
        printf("Greska u alokaciji memorije!\n");
        return NULL;
    }
    strcpy(q->naziv, naziv);
    q->root = NULL;
    q->next = NULL;
    return q;
}

PositionG insertGrad(PositionG root, PositionG q) {
    if (root == NULL) {
        return q;
    }
    if (q->broj_stanovnika < root->broj_stanovnika) {
        root->left = insertGrad(root->left, q);
    }
    else if (q->broj_stanovnika > root->broj_stanovnika ||
        (q->broj_stanovnika == root->broj_stanovnika && strcmp(q->naziv, root->naziv) < 0)) {
        root->right = insertGrad(root->right, q);
    }
    return root;
}

PositionD insertDrzava(PositionD head, PositionD q) {
    if (head == NULL || strcmp(q->naziv, head->naziv) < 0) {
        q->next = head;
        return q;
    }
    head->next = insertDrzava(head->next, q);
    return head;
}

PositionD ReadFile(PositionD head) {
    FILE* file = fopen("drzave.txt", "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke: drzave.txt\n");
        return NULL;
    }

    char drzavaNaziv[50], gradoviDatoteka[50];
    while (fscanf(file, "%s %s", drzavaNaziv, gradoviDatoteka) == 2) {
        PositionD q = createDrzava(drzavaNaziv);
        head = insertDrzava(head, q);

        FILE* gradoviFile = fopen(gradoviDatoteka, "r");
        if (!gradoviFile) {
            printf("Greska pri otvaranju datoteke: %s\n", gradoviDatoteka);
            continue;
        }

        char gradNaziv[50];
        int brojStanovnika;
        while (fscanf(gradoviFile, "%[^,],%d", gradNaziv, &brojStanovnika) == 2) {
            PositionG g = createGrad(gradNaziv, brojStanovnika);
            q->root = insertGrad(q->root, g);
        }

        fclose(gradoviFile);
    }

    fclose(file);
    return head;
}

void pretraziGradove(PositionG root, int prag) {
    if (root) {
        pretraziGradove(root->left, prag);
        if (root->broj_stanovnika > prag) {
            printf("\t%s (%d)\n", root->naziv, root->broj_stanovnika);
        }
        pretraziGradove(root->right, prag);
    }
}

void ispisiGradove(PositionG root) {
    if (root) {
        ispisiGradove(root->left);
        printf("%s (%d)\n", root->naziv, root->broj_stanovnika);
        ispisiGradove(root->right);
    }
}

void ispisiDrzave(PositionD head) {
    while (head) {
        printf("Drzava: %s\n", head->naziv);
        ispisiGradove(head->root);
        head = head->next;
    }
}

int main() {
    PositionD head = NULL;
    head = ReadFile(head);
    if (!head) {
        return 1;
    }

    printf("Podaci o drzavama i gradovima:\n");
    ispisiDrzave(head);

    char drzava[50];
    int prag;
    printf("\nUnesite ime drzave: ");
    scanf("%s", drzava);
    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &prag);

    PositionD current = head;
    while (current && strcmp(current->naziv, drzava) != 0) {
        current = current->next;
    }

    if (current) {
        printf("Gradovi u drzavi %s s vise od %d stanovnika:\n", drzava, prag);
        pretraziGradove(current->root, prag);
    }
    else {
        printf("Drzava %s nije pronadjena.\n", drzava);
    }

    return 0;
}
