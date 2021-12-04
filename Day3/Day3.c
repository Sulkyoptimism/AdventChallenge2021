#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int COLS = 14;
static int BITNUM = 12;
char* get_average_at_pos(char** bin_list, int length, int pos, char round_char) {
	char* line = "------------";
	char str[2] = "00";
	int count = 0;
	for (int i = 0; i < length; i++) {
		str[1] = bin_list[i][pos];

		count += atoi(str);
	}

	if (count > (length * 0.5)) {
		return round_char=='1'?'1':'0';
	}
	else if (count == (length * 0.5)) {
		return round_char;
	}
	else if (count < (length * 0.5)) {
		return round_char == '0' ? '1' : '0';
	}
	else {
		return'-';
	}
}
void part1(char** bin_list, int length) {
	char gamma_str[12] = "------------";
	char epsil_str[12] = "------------";
	//char gamma_str[5] = "-----";
	//char epsil_str[5] = "-----";
	for (int i = 0; i < BITNUM; i++) {
		gamma_str[i] = get_average_at_pos(bin_list, length, i, '1');
		epsil_str[i] = gamma_str[i] == '0' ? '1' : '0';
	}
	//char* cp = "----------------";
	char* cp = (BITNUM > 5 ? "------------" : "-----");
	int gamma = strtol(gamma_str, &cp, 2);
	int epsil = ~gamma & (BITNUM > 5 ? 0x00000FFF : 0x0000000F);

	printf("gamma string: %s\n", gamma_str);
	printf("gamma: %i\n", gamma);

	printf("epsil string: %s\n", epsil_str);
	printf("epsil: %i\n", epsil);

	printf("product: %i\n", gamma * epsil);
}

int filter_lines(char** bin_list, char filter, int position, int length) {
	printf("filter: %c, position: %i\n", filter, position);
	int index = 0;
	if (length > 1) {
		for (int i = 0; i < length; i++) {
			if (bin_list[i][position] == filter) {
				strcpy_s(bin_list[index++], COLS, bin_list[i]);
				printf("Good lines: %s\n", bin_list[i]);
			}
		}
	}
	else {
		index = 1;
	}
	return index;
}



void part2(char** bin_list, char** bin_list2, int length) {
	char oxy_string[14] = "------------";
	char carbo_string[14] = "------------";
	//char gamma_str[5] = "-----";
	//char epsil_str[5] = "-----";
	int len = length;
	int len2 = length;
	for (int i = 0; i < BITNUM; i++) {
		char filter = get_average_at_pos(bin_list, len, i, '1');
		char filter2 = get_average_at_pos(bin_list2, len2, i, '0');
		len = filter_lines(bin_list, filter, i, len);
		len2 = filter_lines(bin_list2, filter2, i, len2);
	}

	strcpy_s(oxy_string, COLS, bin_list[0]);
	strcpy_s(carbo_string, COLS, bin_list2[0]);
	char* cp = (BITNUM > 5 ? "------------" : "-----");
	int oxygen = strtol(oxy_string, &cp, 2);
	int carbo = strtol(carbo_string, &cp, 2);

	printf("oxygen string: %s\n", oxy_string);
	printf("oxygen: %i\n", oxygen);

	printf("carbo string: %s\n", carbo_string);
	printf("carbo: %i\n", carbo);

	printf("product: %i\n", oxygen * carbo);
}


void main() {

	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, "reads.txt", "r"); // read only 
	char bin_lines[1000][14] = { 0 };
	int ind = 0;
	while (!feof(file)) {
		fgets(bin_lines[ind], COLS, file);
		printf("line: %s\n", bin_lines[ind]);
		ind++;
	}
	printf("\n");
	fclose(file);


	char** binlineP = malloc(ind * sizeof * binlineP);
	char** binlineP_copy = malloc(ind * sizeof * binlineP);
	for (int i = 0; i < ind; i++)
	{
		binlineP[i] = malloc(COLS * sizeof * binlineP[i]);
		binlineP_copy[i] = malloc(COLS * sizeof * binlineP_copy[i]);
	}

	for (int i = 0; i < ind; i++)
	{
		memcpy(binlineP[i], bin_lines[i], COLS);
		memcpy(binlineP_copy[i], bin_lines[i], COLS);
	}

	part1(binlineP,ind);
	part2(binlineP, binlineP_copy, ind);
}
