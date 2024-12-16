#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct _directory* Directory;

typedef struct _directory {
    char name[MAX_NAME];
    Directory parent;
    Directory child;
    Directory sibling;
} directory;


Directory kreirajDirektorij(char* name, Directory parent) {
    Directory newDir = (Directory*)malloc(sizeof(directory));
    if (!newDir) {
        printf("Alokacija memorije nije uspjela!\n");
        exit(1);
    }
    
    strncpy(newDir->name, name, MAX_NAME);
    
    newDir->parent = parent;
    newDir->child = NULL;
    newDir->sibling = NULL;
    return newDir;
}


void dodajDirektorij(Directory current, const char* name) {
    Directory newDir = kreirajDirektorij(name, current);
    if (!current->child) {
        current->child = newDir;
    }
    else {
        Directory temp = current->child;
        while (temp->sibling) {
            temp = temp->sibling;
        }
        temp->sibling = newDir;
    }
}


void ispisDirektorija(Directory current) {
    if (!current->child) {
        printf("Direktorij je prazan.\n");
        return;
    }
    Directory temp = current->child;
    printf("\n\nSadrzaj direktorija '%s':\n\n", current->name);
    while (temp) {
        printf("%s\n", temp->name);
        temp = temp->sibling;
    }
}


Directory promijeniDirektorij(Directory current, char name) {
    if (!current->child) {
        printf("Nema poddirektorija.\n");
        return current;
    }
    Directory temp = current->child;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->sibling;
    }
    printf("Direktorij '%s' ne postoji.\n", name);
    return current;
}


Directory povratakNaNadDirektorij(Directory current) {
    if (current->parent) {
        return current->parent;
    }
    printf("Vec ste u korijenskom direktoriju.\n");
    return current;
}


void oslobodiDirektorije(Directory dir) {
    if (dir->child) {
        oslobodiDirektorije(dir->child);
    }
    if (dir->sibling) {
        oslobodiDirektorije(dir->sibling);
    }
    free(dir);
}


void ocistiUlaz() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Directory* root = kreirajDirektorij("root", NULL);
    Directory* current = root;

    int choice;
    char name[MAX_NAME];

    do {
        printf("\n-- Meni --\n");
        printf("1. md (napravi direktorij)\n");
        printf("2. cd dir (promijeni direktorij)\n");
        printf("3. cd.. (nazad)\n");
        printf("4. dir (ispis sadrzaja)\n");
        printf("5. izlaz\n");
        printf("Odabir: ");
        if (scanf("%d", &choice) != 1) {
            printf("Neispravan unos.\n");
            ocistiUlaz();
            continue;
        }
        ocistiUlaz(); 

        switch (choice) {
        case 1:
            printf("Unesite ime novog direktorija: ");
            fgets(name, MAX_NAME, stdin);
            dodajDirektorij(current, name);
            break;
        case 2:
            printf("Unesite ime direktorija za ulazak: ");
            fgets(name, MAX_NAME, stdin);
            current = promijeniDirektorij(current, name);
            break;
        case 3:
            current = povratakNaNadDirektorij(current);
            break;
        case 4:
            ispisDirektorija(current);
            break;
        case 5:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Nevažeća opcija. Pokušajte ponovo.\n");
        }
    } while (choice != 5);

    oslobodiDirektorije(root);
    return 0;
}
