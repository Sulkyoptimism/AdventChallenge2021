#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>

std::ifstream infile("thefile.txt");
using namespace std;


int count_tier(vector<int> numbers, int number) {
    int out = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] == number) {
            out++;
        }
    }
    return out;
}

void part1(vector<int> numbers) {
    int max_int = 0;
    for (std::size_t i = 0; i < numbers.size(); i++) {
        if (max_int < numbers[i]) {
            max_int = numbers[i];
        }
        cout << numbers[i] << std::endl;
    }

    cout << max_int << std::endl;

    map<int, int> data = map<int, int>();

    for (int i = 0; i < max_int + 1; i++)
    {
        data.emplace(i, count_tier(numbers, i));
    }

    int low_sum = 9999999999;
    int low_int = 0;
    for (int i = 0; i < max_int + 1; i++)
    {
        int new_sum = 0;
        for (int j = 0; j < max_int + 1; j++)
        {
            //n * abs(target - nn)
            new_sum += data.at(j) * (abs(i - j));
        }

        if (new_sum < low_sum) {
            low_sum = new_sum;
            low_int = i;
        }
    }

    printf("low int: %i,\tlow sum: %i\n", low_int, low_sum);
}

void part2(vector<int> numbers) {
    int max_int = 0;
    for (std::size_t i = 0; i < numbers.size(); i++) {
        if (max_int < numbers[i]) {
            max_int = numbers[i];
        }
        cout << numbers[i] << std::endl;
    }

    cout << max_int << std::endl;

    map<int, int> data = map<int, int>();

    for (int i = 0; i < max_int + 1; i++)
    {
        data.emplace(i, count_tier(numbers, i));
    }

    double low_sum = 999999999999;
    int low_int = 0;
    for (int targ = 0; targ < max_int + 1; targ++)
    {
        double new_sum = 0;
        for (int curr = 0; curr < max_int + 1; curr++)
        {
            //n * abs(target - nn)
            double diff = (abs(targ - curr));
            int num = data.at(curr);
            double temp_sum = 0;
            for (int k = 1; k <= diff; k++)
            {
                temp_sum += k;
            }

            new_sum += (temp_sum* num);

        }

        if (new_sum < low_sum) {
            low_sum = new_sum;
            low_int = targ;
        }
    }

    printf("low int: %i,\tlow sum: %f\n", low_int, low_sum);
}

void main() {

    ifstream infile("input.txt");
    vector<int> numbers = vector<int>();

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        for (int i; ss >> i;) {
            numbers.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        
        // process pair (a,b)
    }

    part1(numbers);
    part2(numbers);

}