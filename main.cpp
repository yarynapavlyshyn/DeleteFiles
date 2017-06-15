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

bool getPermission(string fileName){
    cout << "Do you really want to delete " << fileName << " (Y/N): ";
    string answer;
    cin >> answer;
    if (answer != "Y")
        return false;
    else
        return true;
}

int func(vector<string> files, bool toDeleteScilently, bool ToDeleteDirectory){
    struct dirent *entry;
    string f;
    bool removed = false;
    bool isDirectory = !strstr(f.c_str(),".");
    bool allowed = true;

    for (int i = 0; i < files.size(); i++) {
        f = files[i];
        if (!toDeleteScilently){
            allowed = (getPermission(f));
        }
        if (!allowed){
            break;
        }

        if (!strstr(f.c_str(),".")){ //  if the name don`t contain "." --> is directory
            if (ToDeleteDirectory){ //if it is allowed to delete the directory
                remove(f.c_str());
                cout << "Deleting" << endl;
            }
        }
        else{
            remove(f.c_str());
            cout << "Deleting" << endl;
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

    func(FILES, toDeleteScilently, ToDeleteDirectory);

    return 0;
}
