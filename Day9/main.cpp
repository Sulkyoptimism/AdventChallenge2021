#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

#define LENGTH 100
#define WIDTH 100


struct coord {
    int x;
    int y;
};

bool adjacent_lower(int map[LENGTH][WIDTH], int x, int y) {
    int x1 = x - 1;
    int x2 = x + 1;
    int y1 = y - 1;
    int y2 = y + 1;

    int comp = map[x][y];
    if (comp == 9) {
       // printf("warn\n");
    }

    if (x1 >= 0 && x1 < LENGTH) {
        int other = map[x1][y];
        if (other <= comp) {
            return true;
        }
    }
    if (x2 >= 0 && x2 < LENGTH) {
        int other = map[x2][y];
        if (other <= comp) {
            return true;
        }
    }
    if (y1 >= 0 && y1 < WIDTH) {
        int other = map[x][y1];
        if (other <= comp) {
            return true;
        }
    }
    if (y2 >= 0 && y2 < WIDTH) {
        int other = map[x][y2];
        if (other <= comp) {
            return true;
        }
    }
    
    return false;
}


int sum_lows(int map[LENGTH][WIDTH], vector<coord> points) {
    int sum = 0;
    for (int p = 0; p < points.size(); p++)
    {
        coord point = points.at(p);
        sum += 1+ map[point.x][point.y];

    }
    return sum;
}

int mapget(int map[LENGTH][WIDTH], coord point) {
    return map[point.x][point.y];
}

void part1(int map[LENGTH][WIDTH]) {

    //find adjacent points
        //if lower exists move on
        //else add index to low list

    vector<coord> low_list = vector<coord>();
    for (int row = 0; row < LENGTH; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            if (adjacent_lower(map, row, col) == false) {
                coord temp;
                temp.x = row;
                temp.y = col;
                low_list.push_back(temp);
            }
        }
    }

    //sum all the ratings
    int sum = sum_lows(map, low_list);
    printf("sum of lows: %i\n", sum);
}


vector<coord> search(int map[LENGTH][WIDTH], coord point, coord previous_point ) {
    vector<coord> out = vector<coord>();
    out.push_back(point);

    //set up alt comparison points
    coord point1;
    coord point2;
    coord point3;
    coord point4;
    point1.x = point.x+1;
    point1.y = point.y;    
    point2.x = point.x-1;
    point2.y = point.y;    
    point3.x = point.x;
    point3.y = point.y+1;
    point4.x = point.x;
    point4.y = point.y-1;

    //int num = mapget(map, point);

    //if alt point meets conditions and is larger but not 9 then recursively call the method again on the new point
    if (point1.x >= 0 && point1.x< LENGTH && !(point1.x == previous_point.x && point1.y == previous_point.y)) {
        if (mapget(map, point1) >= mapget(map, point) && mapget(map, point1)!=9) {
            vector<coord> temp = search(map, point1, point);
            out.insert(out.end(), temp.begin(), temp.end());
        }
    }

    if (point2.x >= 0 && point2.x < LENGTH && !(point2.x == previous_point.x && point2.y == previous_point.y)) {

        if (mapget(map, point2) >= mapget(map, point) && mapget(map, point2) != 9) {
            vector<coord> temp = search(map, point2, point);
            out.insert(out.end(), temp.begin(), temp.end());
        }
    }

    if (point3.y >= 0 && point3.y < WIDTH && !(point3.x == previous_point.x && point3.y == previous_point.y)) {

        if (mapget(map, point3) >= mapget(map, point) && mapget(map, point3) != 9) {
            vector<coord> temp = search(map, point3, point);
            out.insert(out.end(), temp.begin(), temp.end());
        }
    }

    if (point4.y >= 0 && point4.y < WIDTH && !(point4.x == previous_point.x && point4.y == previous_point.y)) {

        if (mapget(map, point4) >= mapget(map, point) && mapget(map, point4) != 9) {
            vector<coord> temp = search(map, point4, point);
            out.insert(out.end(), temp.begin(), temp.end());
        }
    }
    return out;
}

void part2(int map[LENGTH][WIDTH]) {
    //get low points
    vector<coord> low_list = vector<coord>();
    for (int row = 0; row < LENGTH; row++){
        for (int col = 0; col < WIDTH; col++){
            if (adjacent_lower(map, row, col) == false) {
                coord temp;
                temp.x = row;
                temp.y = col;
                low_list.push_back(temp);
            }
        }
    }


    coord blankpoint;
    blankpoint.x = -1;
    blankpoint.y = -1;

    //recursive search for bin coords
    vector<vector<coord>> products = vector<vector<coord>>();
    for (int i = 0; i < low_list.size(); i++)
    {
        vector<coord> temp = search(map, low_list.at(i), blankpoint);
        products.push_back(temp);
    }

    //get sizes of bins by plotting points on graph to remove duplicates
    vector<int> pit_sizes = vector<int>();
    for (int i = 0; i < products.size(); i++)
    {
        int grid[LENGTH][WIDTH] = { 0 };
        for (int k = 0; k < products.at(i).size(); k++)
        {
            grid[products.at(i).at(k).x][products.at(i).at(k).y] = 1;//...remove duplicates
        }
        int unique = 0;
        for (int row = 0; row < LENGTH; row++)
        {
            for (int col = 0; col < WIDTH; col++)
            {
                if (grid[row][col] == 1) {
                    unique++;
                }
            }
        }
        pit_sizes.push_back(unique);
    }

 
    //sort in decending order
    sort(pit_sizes.rbegin(), pit_sizes.rend());

    int product = 1;
    //multiply first three (largest)
    for (int i = 0; i < 3; i++)
    {
        product *= pit_sizes.at(i);
    }

    printf("product of bins: %i\n", product);

}

void main() {

    ifstream infile("input.txt");
    vector<string> input_line = vector<string>();

    int height_map[LENGTH][WIDTH] = { 0 };


    string line;
    int len_ind = 0;
    while (getline(infile, line)){
        for (int i = 0; i < WIDTH; i++){
            height_map[len_ind][i] = line[i] - '0';
        }
        len_ind++;
    }
    
    part1(height_map);
    //1524
    part2(height_map);
    std::cout << "done" << endl;
}
