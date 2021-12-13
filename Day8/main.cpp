#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class seg_disp
{
public:
    char zero[7]    = "     "   ;
    char one[3]     = " "       ;
    char two[6]     = "   "     ;
    char three[6]   = "   "     ;
    char four[5]    = "   "     ;
    char five[6]    = "    "    ;
    char six[7]     = "     "   ;
    char seven[4]   = "  "      ;
    char eight[8]   = "      "  ;
    char nine[7]    = "     "   ;




    char top        = ' '       ;
    char topleft    = ' '       ;
    char topright   = ' '       ;
    char middle     = ' '       ;
    char botleft    = ' '       ;
    char botright   = ' '       ;  
    char bot        = ' '       ;

    seg_disp();
    ~seg_disp();
    int found = 0;

    void add_num(string code) {
        switch (code.length())
        {
        case 2:
            for (int i = 0; i < 2; i++){
                one[i] = code[i];
            }
            break;

        case 3:
            for (int i = 0; i < 3; i++){
                seven[i] = code[i];
            }
            break;

        case 4:
            for (int i = 0; i < 4; i++){
                four[i] = code[i];
            }
            break;

        case 7:
            for (int i = 0; i < 7; i++){
                eight[i] = code[i];
            }
            break;

        case 5:

            found = 0;

            for (int i = 0; i < 5; i++){
                if (code[i] == one[0] || code[i] == one[1]) {
                    found++;
                }
            }
            if (found == 2) {
                for (int k = 0; k < 5; k++){
                    three[k] = code[k];
                }
            }
            else {
                found = 0;
                for (int i = 0; i < 5; i++) {
                    if (code[i] == four[0] || code[i] == four[1] || code[i] == four[2] || code[i] == four[3]) {
                        found++;
                    }
                }
                if (found == 2) {
                    for (int k = 0; k < 5; k++) {
                        two[k] = code[k];
                    }
                }
                else if (found == 3) {
                    for (int k = 0; k < 5; k++) {
                        five[k] = code[k];
                    }
                }
            }
            break;

        case 6:

            found = 0;

            for (int i = 0; i < 6; i++) {
                if (code[i] == four[0] || code[i] == four[1] || code[i] == four[2] || code[i] == four[3]) {
                    found++;
                }
            }
            if (found == 4) {
                for (int k = 0; k < 6; k++) {
                    nine[k] = code[k];
                }
                break;
            }

            found = 0;

            for (int i = 0; i < 6; i++) {
                if (code[i] == one[0] || code[i] == one[1]) {
                    found++;
                }
            }
            if (found == 2) {
                for (int k = 0; k < 6; k++) {
                    zero[k] = code[k];
                }
            }
            else {
                for (int k = 0; k < 6; k++) {
                    six[k] = code[k];
                }
            }
            break;

        default:
            break;
        }

    }


    void find_chars() {
        find_top();
        find_topleft_and_botright();
        find_topright();
        find_middle();
        find_botleft();
        find_bot();
    }

    void find_top() {
        for (int i = 0; i < 3; i++){
            if (!(seven[i] == one[0] || seven[i] == one[1])) {
                top = seven[i];
            }
        }
    }

    void find_topleft_and_botright() {
        char arr[3] = "  ";
        int count = 0;
        for (int i = 0; i < 7; i++) {
            if (!(eight[i] == two[0] || eight[i] == two[1] || eight[i] == two[2] || eight[i] == two[3]
                || eight[i] == two[4] )) {
                arr[count++] = eight[i];
            }
        }
        for (int i = 0; i < 2; i++)
        {
            if (arr[i] != one[0] && arr[i] != one[1]) {
                topleft = arr[i];
            }
            if (arr[i] == one[0] || arr[i] == one[1]) {
                botright = arr[i];
            }
        }
    }

    void find_bot() {
        for (int i = 0; i < 7; i++) {
            if (!(eight[i] == top || eight[i] == topleft || eight[i] == topright || eight[i] == middle
                || eight[i] == botleft || eight[i] == botright)) {
                bot = eight[i];
            }
        }
    }

    void find_middle() {
        for (int i = 0; i < 7; i++) {
            if (!(eight[i] == zero[0] || eight[i] == zero[1] || eight[i] == zero[2] || eight[i] == zero[3]
                || eight[i] == zero[4] || eight[i] == zero[5])) {
                middle = eight[i];
            }
        }
    }

    void find_topright() {
        for (int i = 0; i < 7; i++) {
            if (!(eight[i] == six[0] || eight[i] == six[1] || eight[i] == six[2] || eight[i] == six[3]
                || eight[i] == six[4] || eight[i] == six[5])) {
                topright = eight[i];
            }
        }
    }

    void find_botleft() {
        for (int i = 0; i < 7; i++) {
            if (!(eight[i] == nine[0] || eight[i] == nine[1] || eight[i] == nine[2] || eight[i] == nine[3]
                || eight[i] == nine[4] || eight[i] == nine[5])) {
                botleft = eight[i];
            }
        }
    }

    int decode(string line) {
        string temp = line;
        sort(temp.begin(), temp.end());

        string zero_comp = zero;
        string five_comp = five;
        string two_comp = two;
        string three_comp = three;
        string nine_comp = nine;
        string six_comp = six;

        switch (temp.length())
        {
        case 2:return 1;
        case 4:return 4;
        case 3:return 7;
        case 7:return 8;
        case 5:
            sort(five_comp.begin(), five_comp.end());

            sort(two_comp.begin(), two_comp.end());

            sort(three_comp.begin(), three_comp.end());


            if (temp.compare(two_comp)==0) {
                return 2;
            }
            else if(temp.compare(five_comp) == 0) {
                return 5;
            }
            else if(temp.compare(three_comp) == 0) {
                return 3;
            }
        case 6:
            sort(nine_comp.begin(), nine_comp.end());

            sort(six_comp.begin(), six_comp.end());

            sort(zero_comp.begin(), zero_comp.end());


            if (temp.compare(six_comp) == 0) {
                return 6;
            }
            else if (temp.compare(nine_comp) == 0) {
                return 9;
            }
            else if (temp.compare(zero_comp) == 0) {
                return 0;
            }



        default:
            return -1;
            break;
        }

    }
private:

};

seg_disp::seg_disp()
{
}

seg_disp::~seg_disp()
{
}



    

int count_unique_chars(int len) {
    switch (len)
    {
    case 2:
        return 1;
        break;
    case 3:
        return 1;
        break;
    case 4:
        return 1;
        break;
    case 7:
        return 1;
        break;

    default:
        return 0;
        break;
    }
}

void part1(vector<string> lines) {
    int count = 0;
    for (size_t i = 0; i < lines.size(); i++)
    {
        string temp = lines.at(i);

        string delim = " ";
        string token = "";
        size_t pos = 0;

        while ((pos = temp.find(delim)) != string::npos) {
            token = temp.substr(0, pos);
            temp.erase(0, pos + delim.length());
            count += count_unique_chars(token.length());
        }
        count += count_unique_chars(temp.length());


    }
    std::printf("Count: %i \n", count);
}

void part2(vector<string> in_lines, vector<string> out_lines) {


    int sum = 0;
    for (size_t i = 0; i < in_lines.size(); i++)
    {
        string temp = in_lines.at(i);
        vector<string> temp_list = vector<string>();
        string delim = " ";
        string token = "";
        size_t pos = 0;

        seg_disp segd = seg_disp();
        seg_disp* sg = &segd;
        while ((pos = temp.find(delim)) != string::npos) {
            token = temp.substr(0, pos);
            temp.erase(0, pos + delim.length());
            temp_list.push_back(token);
        }
        temp_list.push_back(temp);

        for (int j = 0; j < 10; j++)
        {
            if (temp_list[j].length() == 2 || temp_list[j].length() == 4 || temp_list[j].length() == 7 || temp_list[j].length() == 3) {
                sg->add_num(temp_list[j]);
            }
        }
        for (int j = 0; j < 10; j++)
        {
            if (!(temp_list[j].length() == 2 || temp_list[j].length() == 4 || temp_list[j].length() == 7 || temp_list[j].length() == 3)) {
                sg->add_num(temp_list[j]);
            }
        }
        sg->find_chars();

        string temp2 = out_lines.at(i);
        pos = 0;
        token = "";
        int num = 0;
        int factor = 1000;
        temp2.erase(0, pos + delim.length());
        while ((pos = temp2.find(delim)) != string::npos) {
            token = temp2.substr(0, pos);
            temp2.erase(0, pos + delim.length());
            num+=sg->decode(token)*factor;
            factor /= 10;
        }
        num += sg->decode(temp2) * factor;
        sum += num;
    }

    std::printf("sum: %i", sum);
}


void main() {

    ifstream infile("input.txt");
    vector<string> input_line = vector<string>();
    vector<string> output_line = vector<string>();

    string line;
    while (getline(infile, line))
    {
        bool flip = false;
        stringstream ss(line);
        string delim = "|";
        string token = "";
        size_t pos = 0;
        pos = line.find(delim);
        token = line.substr(0, pos);
        input_line.push_back(token);
        line.erase(0, pos + delim.length());
        output_line.push_back(line);
    }

    part1(output_line);
    part2(input_line, output_line);
    std::cout << "done" << endl;
}
 