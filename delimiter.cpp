#include "bits/stdc++.h"
using namespace std;

int greeting();
vector<string> acceptFileNamesFromUser(int nOfFiles);
string readTextFromFiles();
void parentheses_check(string textInput);

int main()
{

    int nOfFilesToCheck = greeting();
    vector<string> files = acceptFileNamesFromUser(nOfFilesToCheck);

    //To read files    
    for (int i = 0, n = files.size(); i < n; ++i)
    {
        string nameOfFile = files[i];
        
        ifstream file;
        file.open(nameOfFile);
        string textOfFile = "";
        
        while (file)
        {
            string line = "";
            file >> line;
            textOfFile.append(line);
        }

        parentheses_check(textOfFile);
        file.close();
    }
    
    return 0;
}

int greeting()
{
    cout << "\t \t Welcome to the Delimiter Checking Program! \t \t" << endl;

    cout << "\t \t Enter number of files to check: ";
    int numberOfFilesToCheck = 0; cin >> numberOfFilesToCheck;
    return numberOfFilesToCheck;
}

vector<string> acceptFileNamesFromUser(int nOfFiles)
{
    vector<string> fileNames;
    for (int i = 0; i < nOfFiles; ++i)
    {
        string name = "";
        cout << "Enter name of file " <<  (i + 1) << " (with extenstion): " << "\n";
        cin >> name;
        fileNames.push_back(name);
    }

    return fileNames;
}

void parentheses_check(string textInput)
{
    int lenOfInputText = textInput.length();
    stack<pair<char, int>> s;

    for (int i = 0; i < lenOfInputText; ++i)
    {
        char ch = textInput[i];
        switch (ch)
        {
            case '{':
            case '(':
            case '[':
                s.push({ch, i});
                break;
            case ')':
                s.pop();
                break;
            case '}':
                s.pop();
                break;
            case ']':
                s.pop();
                break;
            default:
                break;
        }
    }

    if (!s.empty())
    {
        cout << "Odd characters are as follows: " << endl;
        while (!s.empty())
        {
            pair<char, int> p = s.top();
            s.pop();
            cout << p.first << " found unpaired. Character count of << " << p.first << " is: " << p.second << endl;
        }
    }
    return;
}
