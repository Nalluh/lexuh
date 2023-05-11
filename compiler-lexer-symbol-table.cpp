#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <unordered_map>


using namespace std;


 int c =0;
int Memory_address = 5000;
string symbolT [3][1000];

//[0][c] = identifier
//[1][c] = memAddres
//[2][c] = type




bool isComment(char current, char next) {
    if (current == '[' && next == '*') {
        return true;
    }
    return false;
}

bool endOfComment(char current, char next) {
    if (current == '*' && next == ']') {
        return true;
    }
    return false;
}

bool isSingleDigit(string current) {
    if (current == "0" || "1" || "2" || "3" || "4" || "5" || "6" || "7" || "8" || "9") {
        return true;
    }
    return false;
}

bool isKeyword(string st) {
    if (st == "int" || st == "function" || st == "bool" || st == "real" || st == "if" ||
        st == "else" || st == "fi" || st == "return" || st == "put" || st == "get" || st == "while"
        || st == "endwhile" || st == "true" || st == "false") {
        return true;
    }
    return false;
}

bool isOperator(char current) {
    if (current == '=' || current == '!' || current == '>' || current == '<' || current == '*' ||
        current == '/' || current == '-' || current == '+') {
        return true;
    }
    return false;
}

bool isLogicalOperator(char current, char next) {
    if ((current == '<' || current == '>' || current == '!') && (next == '=')) {
        return true;
    }
    if ((current == '=' ) &&( next == '>' || next == '<' || next == '=')) {
        return true;
    }

    return false;
}

bool isSeparator(char current) {
    if (current == '(' || current == ')' || current == '{' || current == '}' || current == ';' ||
        current == ':' || current == '#' || current == '|' || current == ',') {
        return true;
    }
    return false;
}


void lexer(string input, string name_of_output) {
    string current_token = "";
    string current_type = "";
    int decimals = 0;
    int commentChecker = 0;
    bool comment, flag = false;
    ofstream outputFile;
   
    bool iFlag = false;


    outputFile.open(name_of_output + ".txt", ios::app);
    for (size_t i = 0; i < input.length(); i++) {
        char current_char = input[i];
        char next_char = input[i + 1];

        if (isComment(current_char, next_char) == true) {
            while (input[i] != ']')
            {
                i++;
                if (endOfComment(current_char, next_char) == true) {
                    cout << "Done";
                }
            }
            if (endOfComment(current_char, next_char) == true) {
                commentChecker = 0;
            }
        }

        if (commentChecker == 1) {
            continue;
        }
        else if (isspace(current_char)) {
            continue;
        }
        else if (isalpha(current_char)) {
            current_token += current_char;
            while (isalnum(input[i + 1])) {
                current_token += input[++i];
            }
            if (isKeyword(current_token) == true) {
                current_type = current_token;
                if (current_token == "if" || current_token == "while"  || current_token == "put" || current_token == "get")
                {
                    if (input[i + 1] != '(') {
                        outputFile << "Keyword         " << current_token << endl;
                        //outputFile <<  "Error () expected" << endl;
                        exit(0);
                    }
                    if (input[i + 1] == '(' ) {
                        if (current_token == "if") {
                            outputFile << "Keyword         " << current_token << endl;
                        //    outputFile << " < Statement List > -> <Statement> <Statement List Prime> \n <Statement List Prime> ->, <Statement List> \n <" << current_token << "> \n <If> -> <Condition> <Statement>" << endl;

                        }
                        if (current_token == "while") {
                            //outputFile << " < Statement List > -> <Statement> <Statement List Prime> \n <Statement List Prime> ->, <Statement List> \n <" << current_token << "> \n <While> -> <Condition> <Statement>" << endl;

                        }
                        if (current_token == "put") {
                          //  outputFile << " < Statement List > -> <Statement> <Statement List Prime> \n <Statement List Prime> ->, <Statement List> \n <" << current_token << "> \n <Print> -> <Expression>" << endl;

                        }
                        if (current_token == "get") {
                           // outputFile << " < Statement List > -> <Statement> <Statement List Prime> \n <Statement List Prime> ->, <Statement List> \n <" << current_token << "> \n <Scan> -> <IDS>" << endl;

                        }
                       
                       
                        i++;
                            
                    }
                    
                }
                else if (current_token == "int" || current_token == "bool" ) { //|| current_token == "real"
                    string str = to_string(Memory_address);
                    symbolT[2][c] = current_token;
                    symbolT[1][c]  = str;

                    iFlag = true;
                    outputFile << "Keyword         " << current_token << endl;
                    //outputFile << "< Parameter list > -> <Parameter> <Parameter list Prime> \n <Parameter list Prime> ->, <Parameter list> \n <Parameter> -> <Qualifier>" << endl;

                }
                else if (current_token == "function") {
                    //outputFile << " < Identifier > ->  <Opt Parameter List> \n <Opt Declaration List> <Body> ->  <Body> \n";

                }
                else {
                    outputFile << "Keyword         " << current_token << endl;
                    //outputFile << " < Statement List > -> <Statement> <Statement List Prime> \n <Statement List Prime> ->, <Statement List> \n " << endl;
                }
            }
            else {
                if (i > 1)
                {
                    if (isOperator(input[i - 1])) {
                        outputFile << "Identifier      " << current_token << endl;
                       // outputFile << "<Term> -> <Factor> <Term Prime>" << endl;
                        flag = true;
                    }

                }
                if (isOperator(input[i+1])) {
                    outputFile << "Identifier      " << current_token << endl;
                    //outputFile << "<Term Prime>->e \n <Expression Prime> -> + <Term> <Expression Prime>" << endl;
                        
                }
                
                else if(!flag){
                    if(iFlag && current_token != "main"){
                        symbolT[0][c] = current_token;
                          c++;
                  Memory_address++;
                    iFlag = false;
                    }
                    outputFile << "Identifier      " << current_token << endl;
                  //  outputFile << "<Statement> -> <Assign> \n < Assign > -> <Identifier> = <Expression>;" << endl;
                
                }

            }
            flag = false;
            current_token = "";
        }
        else if (isdigit(current_char) || current_char == '.') {

            current_token += current_char;
            if (current_char == '.') {
                decimals++;
            }
            while (isdigit(input[i + 1]) || input[i + 1] == '.') {
                current_token += input[++i];
                if (input[i + 1] == '.') {
                    decimals++;
                }
            }
            if (decimals == 1) {
                outputFile << "Real            " << current_token << endl;
                //outputFile << "<Term> -> <Factor> <Term Prime> \n <Factor> -> <Primary> \n <Real>" << endl;


                decimals = 0;
            }
            else if (isSingleDigit(current_token) == true) {
                outputFile << "Integer         " << current_token << endl;
               // outputFile << "<Term> -> <Factor> <Term Prime> \n <Factor> -> <Primary> \n <Integer>" << endl;


            }
            current_token = "";
        }
        else if (isOperator(current_char) == true) {
            if (isLogicalOperator(current_char, next_char) == true) {
                current_token += current_char;
                current_token += next_char;
                outputFile << "Operator        " << current_token << endl;
             //   outputFile << "<Condition> -> <Relop> " << endl;


                i++;
            }
            else {
                current_token = current_char;
                outputFile << "Operator        " << current_token << endl;
               // outputFile << "<Term> -> <Factor> <Term_Prime> \n <Term_Prime> -> *<Factor> <Term_Prime> | / <Factor> <Term_Prime> \n";

            }
            current_token = "";
        }
        else if (isSeparator(current_char) == true) {
            current_token = current_char;
            if (current_token == "#")
            {
                outputFile << "Separator       " << current_token << endl;
            //    outputFile << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << endl;

            }//TODO


        }
        else if (current_char == '[') {
            while ((input[i] != ']') && i < input.length() - 1) {
                i++;
            }
        }
        else {
            current_token = current_char;
            outputFile << "Unknown:         " << current_token << endl;
           // outputFile << "<Empty>" << endl;

            current_token = "";

            continue;
        }
        current_token = "";
    }
   

    outputFile.close();
}



int main(int argc, char* argv[]) {

    string input, name_of_output, complete_input, name_of_input;
    ifstream myfile;
    ofstream outputFile;
    int counter = 0;
    cout << "Which file do you want to access: ";
    cin >> name_of_input;


    myfile.open(name_of_input + ".txt");
    if (!myfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        cin.ignore();
        return 0;
    }
    cout << "What do you want to name output file: ";
    cin >> name_of_output;
    if (myfile.is_open()) {
        outputFile.open(name_of_output + ".txt", ios::app);
        outputFile << "Token           " << "Lexeme" << endl;
        outputFile << "______________________" << endl << endl;
        

        while (getline(myfile, input)) {
            lexer(input, name_of_output);
        
        }
         outputFile << "Symbol Table: \n";
        outputFile << "Identifier    Memory Location    Type  \n";
         for(int i =0; i <= c; i++){
        outputFile << symbolT[0][i] << "          ";
        outputFile << symbolT[1][i] << "           ";
        outputFile << symbolT[2][i] << "\n";
         }
    outputFile.close();
    }


    myfile.close();

    cout << name_of_output + ".txt" << " created" << endl;

    return 0;
}


/* while not finished(i.e. not end of the source file) do
    call the lexer for a token
    print the tokenand lexeme
    endwhile
}*/