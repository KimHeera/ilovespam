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

vector<string> split(string input, char delimiter);

int main(int argc, char *argv[])
{
    list<string> special = {"+", "\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/", ".", ",", "\n", " ", ":", ";", "", "-", "\"", ".\"", "\'", "_", "{", "}", "[", "]", "|", "\"\"", "\"Subject:"};
    vector<string> csv_read_row;
    string csv_line;
    string str_buf_1;
    int max = 0;
    bool check = false;
    vector<string> sp;
    set<string> words;
    map<string, int> frequency_map;
    ifstream trainHam("./csv/train/dataset_ham_train100.csv");
    ifstream trainSpam("./csv/train/dataset_spam_train100.csv");

    if (trainHam.is_open())
    {
        while (getline(trainHam, csv_line, ','))
        {
            csv_read_row = split(csv_line, '\n');
            for (string a : csv_read_row)
            {
                sp = split(a, ' ');

                for (string t : sp)
                {
                    if (check)
                    {
                        if ((find(special.begin(), special.end(), t) == special.end()))
                        {
                            words.insert(t);
                        }
                        check = false;
                    }
                    else
                    {
                        if (t == "ham")
                        {
                            check = true;
                            for (string s : words)
                            {
                                frequency_map[s] = frequency_map[s] + 1;
                                cout << "word: " << s << " || " << frequency_map[s] << endl;

                                if (max < frequency_map[s])
                                    max = frequency_map[s];
                            }
                            words.clear();
                        }
                        else
                        {
                            if ((find(special.begin(), special.end(), t) == special.end()))
                            {
                                words.insert(t);
                            }
                        }
                    } // check가 false이면
                }     //공백으로 나눈 문장 for문
            }         // string 한 줄씩 읽는 for문
        }
    } // getline while문
      //파일 열렸으면

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

    // cnt = space.size();

    cout << "최대 빈도수 : " << max << endl;

    return 0;
}

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
