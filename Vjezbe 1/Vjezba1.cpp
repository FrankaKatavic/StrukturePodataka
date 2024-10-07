#include <stdio.h>

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 1024
int numberofrows(const char*);

int main()
{
	int numofrows = 0;
	numofrows = numberofrows("dat.txt");
	return 0;

}

int numberofrows(const char* fileName) {
	FILE *fp = NULL;
	int numofrows = 0;
	char buffer[MAX] = {};
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error");
		return -1;
	}
	while (!feof(fp))
	{
		//fgets(buffer, );
		numofrows++;
	}
}