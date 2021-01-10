#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Lexer {
public:
    explicit Lexer(const string& s) {
        index = 0;
        while (s[index] != '.') {
            tokens.push_back(next_token(s));
        }
    }
    string next_token(const string& s) {
        string token;
        if (isdigit(s[index])) {
            while (isdigit(s[index])) {
                token += s[index];
                index++;
            }
        } else {
            token = s[index];
            index++;
        }
        return token;
    }
    void print_tokens() {
        for (const auto& t : tokens) {
            cout << t << "\n";
        }
    }

private:
    int index;
    vector<string> tokens;
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string s;
    cin >> s;
    // split to lexemes
    Lexer lexer(s);
    // output
    lexer.print_tokens();
    return 0;
}

