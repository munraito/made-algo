#include <iostream>
#include <string>
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
        } else if (CONST_START.find(c) != string::npos) {
            token = get_const(c);
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
    const string DED = "Ded Moroz";
    const string SNEG = "Snegurochka";
    const string MOROZ = "Moroz";
    const string CONST_START = "DSMP";
    const string PODAROK = "Podarok(";
    const string OPERATIONS = "()+-*";
    const string ALPHABET = "0123456789." + OPERATIONS + DED + SNEG + PODAROK;
    bool eos;
    int index;
    string str;

    string get_const(char c) {
        char const_c;
        string const_str;
        int const_index = 0;
        string token;
        if (c == DED[0]) {
            const_c = DED[0];
            const_str = DED;
            token = "2020";
        } else if (c == SNEG[0]) {
            const_c = SNEG[0];
            const_str = SNEG;
            token = "10";
        } else if (c == MOROZ[0]) {
            const_c = MOROZ[0];
            const_str = MOROZ;
            token = "-30";
        } else {
            const_c = PODAROK[0];
            const_str = PODAROK;
            token = "gift";
        }
        while (c == const_c) {
            ++index;
            ++const_index;
            c = str[index];
            const_c = const_str[const_index];
        }
        if (const_index == const_str.length()) {
            return token;
        } else {
            throw invalid_argument("wrong");
        }
    }
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

    static int happy_new_year(int x) {
        if (x > 0) {
            return x + 5;
        } else {
            return -x;
        }
    }
    // F -> N | (S)
    int parse_factor() {
        string prev = curr;
        bool gift = false;
        if (prev == "(" || prev == "gift") {
            if (prev == "gift") {
                gift = true;
            }
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
                if (!gift) {
                    return sum;
                } else {
                    return happy_new_year(sum);
                }
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
    getline(cin, s);
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

