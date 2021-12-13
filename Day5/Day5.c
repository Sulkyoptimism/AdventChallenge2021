#include <stdio.h>
#include <malloc.h>
#include <corecrt_memcpy_s.h>

#define COLS 16

struct point {
	int x;
	int y;
};

struct coords {
	struct point first;
	struct point second;
};


void add_to(struct coords* arraylist, int len, struct coords input) {
	struct coords* new_ords = malloc(sizeof(struct coords) * (len+1));

	int out_size = sizeof(&new_ords);
	int in_size = sizeof(input);
	new_ords[len], out_size, &input, in_size;
	struct coords* temp_p = &arraylist;
	arraylist = &new_ords;
	free(temp_p);

}

void main() {

	struct coords* ords = malloc(sizeof(struct coords));



	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, "test.txt", "r"); // read only 
	char buf[COLS] = {'0'};
	int ind = 0;
	while (!feof(file)) {

		fgets(buf, COLS, file);
		printf("line: %s\n", buf);
		int Ax, Ay, Bx, By = 0;
		sscanf_s(buf, "%i, %i -> %i, %i", &Ax, &Ay, &Bx, &By);
		struct coords temp;
		temp.first.x = Ax;
		temp.first.y = Ay;
		temp.second.x = Bx;
		temp.second.y = Ay;
		add_to(&ords, 0, temp);
		ind++;
	}
	printf("\n");
	fclose(file);
}