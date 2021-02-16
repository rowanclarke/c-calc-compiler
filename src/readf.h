#ifndef READF_H
#define READF_H

#include <stdio.h>
#include <stdlib.h>

void readf(char *filename, char *dest) {
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL) perror("Error opening file");
	fscanf(fp, "%[^\0]", dest);
	fclose(fp);
}

#endif
