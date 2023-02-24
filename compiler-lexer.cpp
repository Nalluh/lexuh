#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;
void lexer(string input){
  
    string current_token = "";
    string current_type = "";
    cout << "Token    " << "Lexeme" << endl;
    for (size_t i = 0; i < input.length(); i++) {
        char current_char = input[i];

        if (isspace(current_char)) {
            continue;
        }
        else if (isalpha(current_char)) {
            current_token += current_char;
            while (isalnum(input[i + 1])) {
                current_token += input[++i];
            }
            if (current_token == "int" || current_token == "function" || current_token == "int" || current_token == "bool" || current_token == "real" || current_token == "if" ||
                current_token == "else" || current_token == "fi" || current_token == "return" || current_token == "put" || current_token == "get" || current_token == "while"
                || current_token == "endwhile" || current_token == "true" || current_token == "false") {
                current_type = current_token;
                cout << "Keyword: " << current_token << endl;
            }
            else {
                cout << "Identifier: " << current_token << endl;
            }
            current_token = "";
        }
        else if (isdigit(current_char) || current_char == '.') {
            current_token += current_char;
            while (isdigit(input[i + 1]) || input[i + 1] == '.') {
                current_token += input[++i];
            }
            if (current_token == "0" || "1" || "2" || "3" || "4" || "5" || "6" || "7" || "8" || "9") {
                cout << "Integer: " << current_token << endl;
            }
            else {
                cout << "Real: " << current_token << endl;
            }
            current_token = "";
        }
        else if (current_char == '=' || current_char == '!' || current_char == '>' || current_char == '<' || current_char == '*' ||
            current_char == '/' || current_char == '-' || current_char == '+') {
            cout << "Operator: " << current_char << endl;
        }
        else if (current_char == '(' || current_char == ')' || current_char == '{' || current_char == '}') {
            cout << "Separator: " << current_char << endl;
        }
        else if (current_char == '[') {
            while (input[i + 1] != ']' && i < input.length() - 1) {
                i++;
            }
        }
        else {
            // Ignore other characters
            continue;
        }
    }

    
}

int main(int argc, char* argv[]) {
    string input;
    ifstream myfile(argv[1]);
    if (!myfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        return 1;
    } 
    while (!myfile.eof())
    {
        myfile >> input;
    }  
    cout << input;
    //string input = "while  (fahr <= upper)  -int 5  a = 23.00; endwhile  [*this is sample *]";
   // lexer(input);

    /* while not finished(i.e. not end of the source file) do
        call the lexer for a token
        print the tokenand lexeme
        endwhile *\
}