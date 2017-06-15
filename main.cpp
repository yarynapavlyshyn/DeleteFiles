#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

vector<string> split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

int func(vector<string> files){
    cout << "in func()" << endl;
    struct dirent *entry;
    string f;

    for (int i = 0; i < files.size(); i++) {
        f = files[i];
        cout << f << endl;
        entry = readdir(opendir(f.c_str()));
        if(entry->d_type == 4){
            cout << "it`s dir";
        }
    }
}

void printVector(vector<string> elems){
    for (int i = 0; i < elems.size(); i++) {
        cout << elems[i] << " ";
    }
    cout << endl;
}

int main()
{
    char user_command_input[1024];

    //string commandKeyword = "rm";

    cin.getline(user_command_input, 1024);

    vector<string> els = split(user_command_input, ' ');
    printVector(els);

    string actualKeyword = els[0];
    cout << "keyword: " << actualKeyword << endl;
    bool ToDeleteDirectory = false;
    bool toDeleteScilently = false;

    int filterIndex = els.size() - 1;
    int numberOfFilters = 0;
    if (els[filterIndex] == "-R") {
        ToDeleteDirectory = true;
        filterIndex --;
        numberOfFilters ++;
    }
    if (els[filterIndex] == "-f") {
        toDeleteScilently = true;
        numberOfFilters ++;
    }

    vector<string> FILES(els.begin()+1, els.end()-numberOfFilters);

    printVector(FILES);

    func(FILES);

    return 0;
}
