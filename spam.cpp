#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string input, char delimiter)
{
    {
        vector<string> string_vector;
        stringstream ss(input);
        string temp;

        while (getline(ss, temp, delimiter))
        {
            string_vector.push_back(temp);
        }

        return string_vector;
    }
}

int main(int argc, char *argv[])
{
    list<string> special = {"+", "\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/", ".", ",", "\n", " ", ":", ";", "", "-", "\"", ".\"", "\'", "_", "{", "}", "[", "]", "|", "\"\"", "\"Subject:"};
    vector<string> csv_read_row;
    string str_buf;
    string str_buf_1;
    double cnt = 0;
    vector<string> sp;
    vector<string> space;
    vector<string> sp_special;
    ifstream trainHam("./csv/train/dataset_ham_train100.csv");
    ifstream trainSpam("./csv/train/dataset_spam_train100.csv");

    if (trainHam.is_open())
    {
        // cout << "train ham 열림 :: " << endl;

        while (getline(trainHam, str_buf, ','))
        {
            csv_read_row.push_back(str_buf); //제대로 들어감
            // cout << csv_read_row.back() << endl;
        }
        // for (string s : sp)
        //     {
        //         cout << s << "||" << endl;
        //     }

        for (int i = 0; i < csv_read_row.size(); i++)
        {
            vector<string> sp = split(csv_read_row[i], '\n'); //개행문자로 자르기
            for (string a : sp)
            {
                space = split(a, ' ');

                // for (int i = 0; i < space.size(); i++)
                // {
                //     cout << space[i] << "  나와라" << endl;
                // }
                for (string s : space)
                {
                    if ((find(special.begin(), special.end(), s) == special.end()))
                    {
                        cout << s << "||" << endl;
                        sp_special.push_back(s);
                    }
                    // if (s.find(l) != string::npos)
                    // {
                    //     sp_special = split(s, l.c_str());
                    //     // sp_special.push_back(s);
                    // }
                    // else
                    //     sp_special.push_back(s);
                    // // cout << "di " << endl;
                    // // for (string c : special)
                    // // {
                    // //     int d = space[i].find(c);
                    // //     space[i].erase(space[i + d]);
                    // // }
                    // cnt++;
                    // cout << space[i] << "||";
                }
            }
        }
        // for (int i = 0; i < sp_special.size(); i++)
        // {
        //     cout << sp_special[i] << " || " << endl;
        // }

        // for(string l : space)
    }
    else
    {
        cout << "파일을 찾을 수 없습니다!" << endl;
    }

    cout << "/////////////////////////////////////" << endl;

    trainHam.close();

    if (trainSpam.is_open())
    {
        // cout << "train spam 열림 :: " << endl;
        while (getline(trainSpam, str_buf_1, ','))
        {
            // cout << str_buf_1 << endl;
        }

        trainSpam.close();
    }
    else
    {
        cout << "파일을 찾을 수 없습니다!" << endl;
    }

    // cout << "단어 개수 : " << cnt << endl;

    return 0;
}
