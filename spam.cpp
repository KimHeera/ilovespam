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
map<string, int> getWord(string filepath, string k);
int test20(string filepath, string k, map<string, int> train_ham, map<string, int> train_spam);
// int result(vector<double> p, vector<double> q, double threshold);

int main(int argc, char *argv[])
{
    map<string, int> frequency_ham;
    map<string, int> frequency_spam;

    frequency_ham = getWord("./csv/train/dataset_ham_train100.csv", "ham");

    cout << "/////////////////////////////////////////////////////" << endl;

    frequency_spam = getWord("./csv/train/dataset_spam_train100.csv", "spam");

    int h = test20("./csv/test/dataset_ham_test20.csv", "ham", frequency_ham, frequency_spam);
    int s = test20("./csv/test/dataset_spam_test20.csv", "spam", frequency_ham, frequency_spam);

    double result = ((double)(h + s) / 40.0) * 100;
    cout << "Accuracy : " << result << endl;

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

map<string, int> getWord(string filepath, string k)
{
    list<string> special = {"+", "\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/", ".", ",", "\n", " ", ":", ";", "", "-", "\"", ".\"", "\'", "_", "{", "}", "[", "]", "|", "\"\"", "\"Subject:"};
    vector<string> csv_read_row;
    string csv_line;
    int max = 1;
    bool check = false;
    vector<string> sp;
    set<string> words;
    map<string, int> frequency_map;

    ifstream trainHam(filepath);

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
                    if (t == k)
                    {
                        check = true;
                        for (string s : words)
                        {
                            frequency_map[s] = frequency_map[s] + 1;
                            // cout << "word: " << s << " || " << frequency_map[s] << endl;

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
    cout << "최대 빈도수 : " << max << endl;

    return frequency_map;
}

int test20(string filepath, string k, map<string, int> train_ham, map<string, int> train_spam)
{
    list<string> special = {"+", "\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/", ".", ",", "\n", " ", ":", ";", "", "-", "\"", ".\"", "\'", "_", "{", "}", "[", "]", "|", "\"\"", "\"Subject:"};
    vector<string> csv_read_row;
    vector<double> p_vector;
    string csv_line;
    bool check = false;
    vector<string> sp;
    set<string> words;
    double p = 1.0;
    double q = 1.0;
    int spam_cnt = 0;
    int ham_cnt = 0;
    int cnt = 0;

    ifstream trainHam(filepath);

    while (getline(trainHam, csv_line, ','))
    {
        csv_read_row = split(csv_line, '\n');

        for (string a : csv_read_row) //
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
                    if (a == k)
                    {
                        p = 1.0;
                        q = 1.0;
                        check = true;
                        for (string s : words)
                        {
                            if (train_ham[s] != 0 && train_spam[s] != 0)
                            {
                                // cout << "s: " << s << " data[s]: " << data[s] << endl;
                                p = p * ((double)train_spam[s] / 100.0);
                                q = q * ((double)train_ham[s] / 100.0);
                            }
                        }
                        cout << "카운트 : " << cnt << endl;
                        cout << "q : " << q << endl;
                        cout << "p : " << p << endl;

                        double r = p / (p + q);

                        if (k == "spam")
                        {
                            if (r > 0.95)
                            {
                                cout << "this is spam" << endl;
                                spam_cnt++;
                            }
                            else
                            {
                                cout << "this is ham" << endl;
                            }
                            cout << "r : " << r << endl;
                        }
                        else
                        {
                            if (r < 0.95)
                            {
                                cout << "this is ham" << endl;
                                ham_cnt++;
                            }
                            else
                            {
                                cout << "this is spam" << endl;
                            }
                            cout << "r : " << r << endl;
                        }
                        cnt++;
                        // cout << "r : " << r << endl;

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

    if (k == "spam")
    {
        cout << "spam : " << spam_cnt << endl;
        return spam_cnt;
    }
    else
    {
        cout << "ham : " << ham_cnt << endl;
        return ham_cnt;
    }
}