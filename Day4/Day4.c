#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int COLS = 24;
const int DIMS = 5;
const int INPUTLEN = 290;
const int BOARDNUM = 100;

struct bingo_board {
	short won;
	int last_coord[2];
	int last_input;
	int num_board[5][5];
	int hit_board[5][5];
};

void init_board(struct bingo_board* board) {
	board->won = 0;
	board->last_coord[0] = 0;
	board->last_coord[1] = 0;
	board->last_input = -1;
	for (int i = 0; i < DIMS; i++){
		for (int j = 0; j < DIMS; j++){
			board->hit_board[i][j] = 0;
			board->num_board[i][j] = -1;
		}
	}
}

int add_num(struct bingo_board* board, int number) {

	if (board->last_coord[1] == 5) {
		return 1;
	}



	board->num_board[board->last_coord[1]][board->last_coord[0]] = number;
	
	board->last_coord[0]++;
	board->last_coord[1] = board->last_coord[0] == DIMS ? board->last_coord[1] + 1 : board->last_coord[1];
	board->last_coord[0] = board->last_coord[0] % DIMS;
	return 0;
}

int evaluate(struct bingo_board* board) {
	int vcount[5] = { 0 };
	for (int r = 0; r < DIMS; r++){
		int hcount = 0;
		for (int c = 0; c < DIMS; c++){
			hcount += board->hit_board[r][c];
			vcount[c] += board->hit_board[r][c];
		}
		if (hcount == DIMS) {
			return 1;
		}
	}
	for (int i = 0; i < DIMS; i++){
		if (vcount[i] == DIMS) {
			return 1;
		}
	}
	return 0;
}

int hit_num(struct bingo_board* board, int hit_num) {
	board->last_input = hit_num;
	for (int row = 0; row < DIMS; row++){
		for (int col = 0; col < DIMS; col++){
			if (board->num_board[row][col] == hit_num) {
				board->hit_board[row][col] = 1;
			}
		}
	}
	return evaluate(board);
}

int get_output(struct bingo_board* board) {
	int sum = 0;
	for (int row = 0; row < DIMS; row++){
		for (int col = 0; col < DIMS; col++){
			if (board->hit_board[row][col] != 1) {
				sum += board->num_board[row][col];
			}
		}
	}
	return (sum * board->last_input);
}

int hit_all_nums_find_winner(struct bingo_board* boards, int* input, int input_count) {

	for (int n = 0; n < input_count; n++) {
		for (int i = 0; i < BOARDNUM; i++) {
			if (hit_num(&boards[i], input[n]) == 1) {
				return get_output(&boards[i]);
			}
		}

	}
}

int hit_all_nums_find_loser(struct bingo_board* boards, int* input, int input_count) {
	int counter = BOARDNUM;
	for (int n = 0; n < input_count; n++) {
		for (int i = 0; i < BOARDNUM; i++) {
			if (hit_num(&boards[i], input[n]) == 1 && boards[i].won ==0) {
				boards[i].won=1;
				counter--;
				if (counter == 0) {
					return get_output(&boards[i]);
				}
			}
		}

	}
}

void main() {

	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, "bingo.txt", "r"); // read only 
	//BOARDNUM
	struct bingo_board boards[100] ;
	for (int i = 0; i < BOARDNUM; i++)
	{
		init_board(&boards[i]);
	}
	char line[24] = { 0 };
	int ind = 0;
	int board_count = 0;
	//INPUTLEN
	char input[290] = { 0 };
	//
	int input_nums[101] = { 0 };
	int input_count = 0;

	while (!feof(file)) {

		if (ind == 0) {
			int digit_count = 0;

			int num1 = 0;
			int num2 = 0;
			fgets(input, INPUTLEN, file);
			for (int i = 0; i < INPUTLEN; i++){
				if (isdigit(input[i])) {
					sscanf_s(input + i, "%i", digit_count > 0 ? &num2 : &num1);
					if (isdigit(input[i + 1])) {
						i++;
					}
					digit_count++;
				}
				else {
					if (digit_count > 1) {
						num1 *= 10;
						num1 += num2;
					}
					input_nums[input_count++] = num1;
					digit_count = 0;
				}
			}
			if (digit_count > 1) {
				num1 *= 10;
				num1 += num2;
			}
			input_nums[input_count++] = num1;
			digit_count = 0;
			ind++;
		}
		fgets(line, COLS, file);
		printf("line: %s\n", line);
		if (strcmp(line, "\n") == 0) {
			continue;
		}
		int list[5] = { 0 };
		for (int i = 0; i < DIMS; i++){
			sscanf_s(line+(i*3), "%i", &list[i]);
		}
	
		for (int i = 0; i < DIMS; i++){
			int ret = add_num(&boards[board_count], list[i]);
			if (ret == 1) {
				board_count++;
				int ret = add_num(&boards[board_count], list[i]);
			}
		}
		ind++;
	}
	fclose(file);
	
	//part1
	int output = hit_all_nums_find_winner(boards, input_nums, input_count);

	int output2 = hit_all_nums_find_loser(boards, input_nums, input_count);
	printf("output: %i\n", output);
	printf("output2: %i\n", output2);
	printf("output2: %i\n", output2);
	//tried 44763

}