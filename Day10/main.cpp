#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>


using namespace std;

#define LENGTH 100
#define WIDTH 100


int char_to_points(char illegal) {
    switch (illegal)
    {
    case ')':
        return 3;
    case ']':
        return 57;
    case '}':
        return 1197;
    case '>': 
        return 25137;
    default:
        return 0;
        break;
    }
}

char closer_for_opener(char opener) {
    switch (opener)
    {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    case '<':
        return '>';
    default:
        return '0';
        break;
    }
}


char opener_for_closer(char opener) {
    switch (opener)
    {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    case '>':
        return '<';
    default:
        return '0';
        break;
    }
}

bool open_char(char input_char) {
    if (input_char == '(' || input_char == '[' ||
        input_char == '{' || input_char == '<') {
        return true;
    }
    else {
        return false;
    }
}

void part1(vector<string> lines) {
    int point_total = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        stack<char> my_stack = stack<char>();
        for (int c = 0; c < lines.at(i).size(); c++)
        {
            char in_char = lines.at(i)[c];
            if(open_char(in_char)) {
                my_stack.push(in_char);
            }
            else{
                char comp1 = my_stack.top();
                char comp2 = opener_for_closer(in_char);
                if (comp1 == comp2) {
                    my_stack.pop();
                }
                else {
                    int points = char_to_points(in_char);
                    point_total += points;
                    printf("error found in line: %i with %c for %i points\n", i, in_char, points);
                    break;
                }
            }
        }
        printf("unfinished stack, moving on line %i\n", i);
    }
    printf("points total: %i\n", point_total);
}
double score_close_seq(vector<char> string) {
    double score = 0;
    for (int i = 0; i < string.size(); i++)
    {
        score *= 5;
        switch (string.at(i))
        {
        case ')':
            score += 1;
            break;
        case ']':
            score += 2;
            break;
        case '}':
            score += 3;
            break;
        case '>':
            score += 4;
            break;
        default:

            break;
        }

    }
    return score;
}


void part2(vector<string> lines) {
    int point_total = 0;
    vector<stack<char>> good_stacks = vector<stack<char>>();
    for (int i = 0; i < lines.size(); i++)
    {
        bool bad_line = false;

        stack<char> my_stack = stack<char>();
        for (int c = 0; c < lines.at(i).size(); c++)
        {
            char in_char = lines.at(i)[c];
            if (open_char(in_char)) {
                my_stack.push(in_char);
            }
            else {
                char comp1 = my_stack.top();
                char comp2 = opener_for_closer(in_char);
                if (comp1 == comp2) {
                    my_stack.pop();
                }
                else {
                    printf("bad line\n");
                    bad_line = true;

                    break;
                }
            }
        }
        printf("unfinished stack, moving on line %i\n", i);
        if (!bad_line) {
            good_stacks.push_back(my_stack);
        }
    }
    printf("points total:\n");

    vector<double> scores = vector<double>();
    for (int i = 0; i < good_stacks.size(); i++){
        vector<char> out = vector<char>();
        stack<char> stack = good_stacks.at(i);

        for (int c = 0; c < good_stacks.at(i).size(); c++){
            out.push_back(closer_for_opener(stack.top()));
            stack.pop();
        }
        double score = score_close_seq(out);
        if (score < 0) {
            printf("warn\n");
        }
        scores.push_back(score);
    }


    sort(scores.begin(), scores.end());
    double mid_score = scores.at((scores.size() / 2));
    printf("mid score: %l\n", mid_score);
}


void main() {

    ifstream infile("input.txt");
    vector<string> input_lines = vector<string>();


    string line;
    int len_ind = 0;
    while (getline(infile, line)) {
        input_lines.push_back(line);
        
        len_ind++;
    }

    part1(input_lines);
    part2(input_lines);
    std::cout << "done" << endl;
}
