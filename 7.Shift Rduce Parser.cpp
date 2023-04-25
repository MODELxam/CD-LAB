//
//  main.cpp
//  Shift Rduce Parser
//
//  Created by Anshu Aaron Varma on 19/04/23.
//

#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

// Define the grammar rules as a set of productions
const string productions[] = {
    "E->E+T",
    "E->T",
    "T->T*F",
    "T->F",
    "F->(E)",
    "F->i"
};

// Define the precedence table
const map<char, int> precedence = {
    {'+', 1},
    {'*', 2},
    {'(', 0},
};

// Parse the input string using a stack and a table-driven approach
bool parse(string input) {
    stack<char> stk;
    stk.push('$');
    stk.push('E');

    int i = 0;
    while (!stk.empty() && i < input.size()) {
        char top = stk.top();

        if (top == input[i]) {
            stk.pop();
            i++;
        } else if (precedence.count(top) && precedence.count(input[i])) {
            if (precedence.at(top) >= precedence.at(input[i])) {
                // reduce
                for (int j = 0; j < sizeof(productions) / sizeof(productions[0]); j++) {
                    if (productions[j][3] == top) {
                        int len = productions[j].size() - 3;
                        while (len--) {
                            stk.pop();
                        }
                        stk.push(productions[j][0]);
                        break;
                    }
                }
            } else {
                // shift
                stk.push(input[i]);
                i++;
            }
        } else {
            // invalid input
            return false;
        }
    }

    return stk.top() == '$' && i == input.size();
}

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    cin >> input;

    if (parse(input)) {
        cout << "Valid expression" << endl;
    } else {
        cout << "Invalid expression" << endl;
    }

    return 0;
}
