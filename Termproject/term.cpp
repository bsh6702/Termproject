
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

using namespace std;

ifstream file("test.txt");
int total = 0;
string str1 = "";
string str2 = "";
string str3 = "";

class TextEditor {
private:
    vector<vector<string>> saveData;
    static TextEditor* s_instance;

public:
    void save_vector() {
        ifstream file("test.txt");
        vector<vector <string>> save;
        vector <string> lineSave;

        char buf[100];
        int count = 0;

      
        while (file >> buf) {
            count += strlen(buf) + 1;
            if (count > 71) {
                count = 0;
                count += strlen(buf) + 1;
                save.push_back(lineSave);
                lineSave.clear();
            }
            lineSave.push_back(buf);
        }
        save.push_back(lineSave);
        set_data(save);
    }

    void resize(vector<vector<string>>& vec) {
        vector<vector <string>> newVec;
        vector <string> lineSave;
        int count = 0;
        string temp;

        for (int i = 0; i < vec.size(); i++) {
            for (int j = 0; j < vec[i].size(); j++) {
                count += vec[i][j].size() + 1;
                if (count > 70) {
                    temp = vec[i][j];
                    count = 0;

                    newVec.push_back(lineSave);
                    lineSave.clear();
                    lineSave.push_back(temp);
                    count = temp.size();
                }
                else {
                    lineSave.push_back(vec[i][j]);
                }
            }
        }
        newVec.push_back(lineSave);
        set_data(newVec);
    }

    void set_data(vector<vector<string>>& vec) {
        saveData = vec;
    }

    vector<vector<string>>& get_data() {
        return saveData;
    }

    static TextEditor* instance() {
        if (!s_instance)
            s_instance = new TextEditor;
        return s_instance;
    }
};

TextEditor* TextEditor::s_instance;

void PrintTwenty(vector<vector<string>>& save, int num) {
    int lineNum = 1;
    str1 = "";
    str2 = "last";
    cout << " " << lineNum << "| ";

    while (true) {
        if (save.size() - num <= 20) { 
            for (int i = save.size() - 20; i < save.size(); i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            total = save.size() - 20;
            str2 = "last";
            break;
        }
        else if (num <= 0) { 
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            total = 0;
            str1 = "first";
            str2 = "";
            break;
        }

        else {
            for (int i = num; i < save.size(); i++) {
                for (int j = 0; j < save[i].size(); j++) {
                    cout << save[i][j] << " ";
                }
                cout << endl;
                lineNum++;
                if (lineNum > 20) {
                    break;
                }
                cout << setw(2) << lineNum << "| ";
            }
            str2 = "";
            break;
        }
    }
}



void saveEnd() {
    vector<vector<string>> vec;
    vec = TextEditor::instance()->get_data();
    ofstream write("test.txt", ios::out);

    for (vector<string> temp : vec) {
        for (string s : temp) {
            write << s << " ";
        }
    }
}

void printDash() {
    for (int i = 0; i < 75; i++) {
        cout << "-";
    }
    cout << endl;
}

char* expectionInput(char* input) {
    string t[10];
    int j = 0;
    string temp = input;

    vector<vector<string>> vec;
    vec = TextEditor::instance()-> get_data();

    if (temp.find(" ") != string::npos) {
        throw "[error] Blanks were included. Input again";
    }

    char* tok = strtok(input, "(),");

    while (tok != NULL) {
        t[j] = tok;
        
        tok = strtok(NULL, "(),");
        j++;
    }
    if (t[0] == "i") {
        for (char const& c : t[1]) {
            if (!isdigit(c)) {
               
                throw "error";
            }
        }
        for (char const& c : t[2]) {
            if (!isdigit(c)) {
                throw "error";
            }
       
    }
    }
    return input;
}

int main() {
    
    wchar_t ch1[100] = L"n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료";
    wchar_t ch3[10] = L"입력:";

    locale::global(locale("en_US.UTF-8"));

    char optionNum[100];

    vector<vector <string>> save;

    TextEditor::instance()->save_vector();
    save = TextEditor::instance()->get_data();

    PrintTwenty(save, total);
    printDash();
    wcout << ch1 << endl;
    printDash();
    printDash();
    wcout << ch3 << " ";

    while (cin.getline(optionNum, 100, '\n')) {
        save = TextEditor::instance()->get_data();

        char* sentence = new char[strlen(optionNum) + 1];
        strcpy(sentence, optionNum);
        printDash();
        try {
            expectionInput(optionNum);
        }
        catch (const char* st) {
            PrintTwenty(save, total);
            printDash();
            wcout << ch1 << endl;
            printDash();
            wcout << st << endl;
            printDash();
            wcout << ch3 << " ";
            continue;
        }

        string t[10];
        int j = 0;
        char* tok2 = strtok(sentence, "(),");
        while (tok2 != NULL) {
            t[j] = tok2;
            tok2 = strtok(NULL, "(),");
            j++;
        }

    }
    file.close();

    return 0;
}