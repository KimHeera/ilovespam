#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<string> csv_read_row;
    string str_buf;
    ifstream file("./csv/train/dataset_ham_train100.csv");

    // if (file.fail())
    // {
    //     return (cout << "fail :: " << endl) && 0;
    // }

    if (file.is_open())
    {
        while (getline(file, str_buf, ','))
        {
            cout << "야호 " << str_buf << endl;
        }
        // vector<string> row = csv_read_row(file, ',');

        // if (!row[0].find("#"))
        // {
        //     continue;
        // }
        // else
        // {
        //     for (int i = 0, leng = row.size() - 2; i < leng; i++)
        //         cout << row[i] << "\t";
        // }
        // for (string t : row)
        //     cout << "word: " << t << endl;

        // cout << endsl;
    }
    return 0;
}