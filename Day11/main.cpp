#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>


using namespace std;

#define LENGTH 10
#define WIDTH 10

struct coords {
    int x;
    int y;
};


class light_board {
public:
    int grid[LENGTH][WIDTH] = { 0 };
    bool pop_grid[LENGTH][WIDTH] = { false };
    bool popped_grid[LENGTH][WIDTH] = { false };



    light_board(int arr[LENGTH][WIDTH]) {
        for (int i = 0; i < LENGTH; i++) {
            for (int k = 0; k < WIDTH; k++) {
                this->grid[i][k] = arr[i][k];
            }
        }
    }

    int step() {
        int out = 0;
        for (int i = 0; i < LENGTH; i++) {
            for (int k = 0; k < WIDTH; k++) {
                if (this->grid[i][k] + 1 == 10) {
                    this->pop_grid[i][k] = true;
                    out++;
                }
                else {
                    this->grid[i][k]++;
                }
            }
        }
        return out;
    }


    int pop_adjacents(int y, int x) {
        int out = 0;
        if (x - 1 >= 0) {
            if (this->grid[y][x - 1] +1 == 10 && this->pop_grid[y][x - 1] != true) {
                this->pop_grid[y][x - 1] = true;
                out++;
            }
            else {
                this->grid[y][x - 1]++;
            }
        }
        if (x - 1 >= 0 && y-1>=0) {
            if (this->grid[y - 1][x - 1] + 1 == 10 && this->pop_grid[y - 1][x - 1] != true) {
                this->pop_grid[y-1][x - 1] = true;
                out++;

            }
            else {
                this->grid[y-1][x - 1]++;
            }
        }
        if (y - 1 >= 0) {
            if (this->grid[y - 1][x] + 1 == 10 && this->pop_grid[y - 1][x] != true) {
                this->pop_grid[y-1][x] = true;
                out++;

            }
            else {
                this->grid[y-1][x]++;
            }
        }
        if (y - 1 >= 0 && x+1<WIDTH) {
            if (this->grid[y - 1][x + 1] + 1 == 10 && this->pop_grid[y - 1][x + 1] != true) {
                this->pop_grid[y-1][x + 1] = true;
                out++;

            }
            else {
                this->grid[y-1][x +1]++;
            }
        }
        if (x + 1 < WIDTH) {
            if (this->grid[y][x + 1] + 1 == 10 && this->pop_grid[y][x + 1] != true) {
                this->pop_grid[y][x + 1] = true;
                out++;

            }
            else {
                this->grid[y][x + 1]++;
            }
        }
        if (x + 1 < WIDTH && y + 1 <LENGTH) {
            if (this->grid[y +1][x + 1] + 1 == 10 && this->pop_grid[y + 1][x + 1] != true) {
                this->pop_grid[y+1][x + 1] = true;
                out++;

            }
            else {
                this->grid[y+1][x + 1]++;
            }
        }
        if (y + 1 < LENGTH) {
            if (this->grid[y+1][x] + 1 == 10 && this->pop_grid[y + 1][x] != true) {
                this->pop_grid[y+1][x] = true;
                out++;

            }
            else {
                this->grid[y+1][x ]++;
            }
        }
        if (y + 1 < LENGTH && x - 1 >= 0) {
            if (this->grid[y+1][x - 1] + 1 == 10 && this->pop_grid[y + 1][x - 1] != true) {
                this->pop_grid[y+1][x - 1] = true;
                out++;

            }
            else {
                this->grid[y+1][x - 1]++;
            }
        }
        return out;
    }

    int pop_pass() {
        int out = 0;
        for (int i = 0; i < LENGTH; i++) {
            for (int k = 0; k < WIDTH; k++) {
                if (this->pop_grid[i][k] == true && this->popped_grid[i][k] != true) {
                    out += this->pop_adjacents(i,k);
                    this->popped_grid[i][k] = true;
                }
            }
        }
        return out;
    }

    void empty() {
        for (int i = 0; i < LENGTH; i++) {
            for (int k = 0; k < WIDTH; k++) {
                if (this->pop_grid[i][k] == true) {
                    this->grid[i][k] = 0;
                    this->pop_grid[i][k] = false;
                    this->popped_grid[i][k] = false;
                }
            }
        }
    }

    int pop_rec() {
        int total = 0;
        int temp = 0;
        temp = this->pop_pass();
        total += temp;
        while (temp != 0)
        {
            temp = 0;
            temp = this->pop_pass();
            total += temp;
        }
        this->empty();
        return total;
    }


    int step_for(int x) {
        int out = 0;
        for (int i = 0; i < x; i++)
        {
            out+=step();
            out+=pop_rec();
        }
        return out;
    }

    int step_for_flag() {
        int out = 0;
        int ind = 0;
        while (true)
        {
            out = 0;
            out += step();
            out += pop_rec();
            ind++;

            if (out == 100) {
                return ind;
            }
            if (ind % 100 == 0) {
                printf("flag ind: %i\n", ind);
            }
        }
    }
};


void part1(int arr[LENGTH][WIDTH]) {
    light_board lb = light_board(arr);
    int flashes = lb.step_for(100);
    printf("flashes: %i\n", flashes);
}


void part2(int arr[LENGTH][WIDTH]) {
    light_board lb = light_board(arr);
    int flashes = lb.step_for_flag();
    printf("flashes sync at: %i\n", flashes);
}

void main() {

    ifstream infile("input.txt");
    int arr[LENGTH][WIDTH] = { 0 };

    string line;
    int len_ind = 0;
    while (getline(infile, line)) {
        for (int i = 0; i < WIDTH; i++)
        {
            arr[len_ind][i] = line[i] - '0';
        }
        len_ind++;
    }

    
    

    part1(arr);
    part2(arr);
    std::cout << "done" << endl;
}
