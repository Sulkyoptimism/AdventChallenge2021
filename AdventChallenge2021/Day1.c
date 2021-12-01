#include <stdio.h>

void part1(int out[], int len) {

	int curr = out[0];
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (curr < out[i]) {
			count++;
		}
		curr = out[i];
	}
	printf("Number of increases %i\n", count);
}

void part2(int out[], int len) {
	int count = 0;
	for (size_t i = 0; i < len-3; i++){
		int sum1 = out[0 + i] + out[1 + i] + out[2 + i];
		int sum2 = out[1 + i] + out[2 + i] + out[3 + i];
		if (sum1 < sum2) {
			count++;
		}
	}
	printf("Number of increases %i\n", count);

}

void main() {
	int out[2000] = { 0 };

	FILE* file = NULL;
	errno_t err;
	int ind = 0;
	int num;
	err = fopen_s(&file, "measurements.txt", "r"); // read only 
	while (fscanf_s(file, "%d", &num) > 0) {
		out[ind] = num;
		ind++;
	}
	fclose(file);
	printf("done input\n");

	part1(out, ind);
	part2(out, ind);
}