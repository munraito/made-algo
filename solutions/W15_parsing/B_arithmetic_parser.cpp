#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

using namespace std;

class Lexer {
public:
    explicit Lexer(const string& s) {
        str = s;
        index = 0;
        eos = false;
    }
    string next_token() {
        string token;
        char c = str[index];
        if (ALPHABET.find(c) == string::npos) {
            throw invalid_argument("wrong");
        }
        if (OPERATIONS.find(c) != string::npos) {
            token = c;
            ++index;
        } else if (c == '.') {
            eos = true;
            ++index;
        } else {
            while (isdigit(c)) {
                token += c;
                ++index;
                c = str[index];
            }
        }
        return token;
    }
    bool reach_eos() const {
        return eos;
    }
    void print_tokens() {
        while (!eos) {
            cout << next_token() << "\n";
        }
        index = 0;
        eos = false;
    }

private:
    const string OPERATIONS = "()+-*";
    const string ALPHABET = "0123456789." + OPERATIONS;
    bool eos;
    int index;
    string str;
};

class Parser {
public:
    explicit Parser(Lexer& lexer) : lexer(lexer) { }
    int parse() {
        curr = lexer.next_token();
        int result = parse_sum();
        if (!lexer.reach_eos()) {
            throw invalid_argument("wrong");
        }
        return result;
    }

private:
    Lexer lexer;
    string curr;

    // F -> N | (S)
    int parse_factor() {
        string prev = curr;
        if (prev == "(") {
            curr = lexer.next_token();
            int sum = parse_sum();
            string r_paren;
            if (!lexer.reach_eos()) {
                r_paren = curr;
            } else {
                throw invalid_argument("wrong");
            }
            if (!lexer.reach_eos() && r_paren == ")") {
                curr = lexer.next_token();
                return sum;
            }
            throw invalid_argument("wrong");
        }
        curr = lexer.next_token();
        return stoi(prev);
    }
    // P -> F | F * F
    int parse_product() {
        int left_factor, right_factor;
        left_factor = parse_factor();
        while (!lexer.reach_eos() && curr == "*") {
            curr = lexer.next_token();
            right_factor = parse_factor();
            left_factor *= right_factor;
        }
        return left_factor;
    }
    // S -> P | P + P | P - P
    int parse_sum() {
        int left_product, right_product;
        left_product = parse_product();
        string op = curr;
        while (!lexer.reach_eos() && (op == "+" || op == "-")) {
            curr = lexer.next_token();
            right_product = parse_product();
            if (op == "+") {
                left_product += right_product;
            } else {
                left_product -= right_product;
            }
            op = curr;
        }
        return left_product;
    }
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string s;
    cin >> s;
    // init lexer and parser
    Lexer lexer(s);
    Parser parser(lexer);
    int ans;
    bool got_err = false;
    // parse expression
    try {
        // lexer.print_tokens();
        ans = parser.parse();
    } catch (...) {
        got_err = true;
    }
    if (got_err) {
        cout << "WRONG";
    } else {
        cout << ans;
    }
    return 0;
}

