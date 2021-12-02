#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int depth = 0;
int forwards = 0;
int aim = 0;


void part1(char* line) {
	if (line[0] == 'f') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			forwards += num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			forwards += num;
		}
	}
	else if (line[0] == 'd') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			depth += num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			depth += num;
		}
	}
	else if (line[0] == 'u') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			depth -= num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			depth -= num;
		}
	}
}

void part2(char* line) {
	if (line[0] == 'f') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			forwards += num;
			depth += aim * num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			forwards += num;
			depth += aim * num;
		}
	}
	else if (line[0] == 'd') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			aim += num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			aim += num;
		}
	}
	else if (line[0] == 'u') {
		if (isdigit(line[strlen(line) - 2])) {
			char in[2] = { line[strlen(line) - 2] };
			int num = atoi(in);
			aim -= num;
		}
		else {
			char in[2] = { line[strlen(line) - 1] };
			int num = atoi(in);
			aim -= num;
		}
	}
}


void main() {

	int ind = 0;
	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, "Directions.txt", "r"); // read only 
	char* line[16] = { 0 };
	while (!feof(file)){
		fgets(line, sizeof(line), file);
		printf("line: %s", line);
		//part1(line);
		part2(line);
		ind++;
		printf("\nforwards: %i\n", forwards);
		printf("depth: %i\n", depth);
	}
	ind;
	fclose(file);
	printf("forwards: %i\n", forwards);
	printf("depth: %i\n", depth);
	printf("sum: %i\n", depth*forwards);

	printf("done input\n");

	//part1(out, ind);
	//part2(out, ind);
}