#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Trie {
public:
    Trie() {
        next.assign(100000, vector<int>(26, -1));
        is_terminal.assign(100000, false);
        is_visited.assign(100000, false);
        size = 1;
    }
    int insert(const string& s) {
        int v = 0;
        for (char c : s) {
            int s_i = c - 'a';
            if (next[v][s_i] == -1) {
                next[v][s_i] = size;
                ++size;
            }
            v = next[v][s_i];
        }
        is_terminal[v] = true;
        return size;
    }
    void contains(const string& s, int start) {
        int v = 0;
        for (int i = start; i < s.length(); ++i) {
            if (is_terminal[v]) {
                is_visited[v] = true;
            }
            int s_i = s[i] - 'a';
            if (next[v][s_i] == -1) {
                return;
            }
            v = next[v][s_i];
        }
        if (is_terminal[v]) {
            is_visited[v] = true;
        }
    }
    bool get_visited(int i) {
        return is_visited[i];
    }
private:
    vector<vector<int> > next;
    vector<bool> is_terminal;
    vector<bool> is_visited;
    int size;
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string text;
    int m;
    cin >> text >> m;
    // push all words to trie, also save their levels
    Trie trie;
    vector<int> word_level;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        word_level.push_back(trie.insert(s) - 1);
    }
    // search all substrings of text in trie, flag visited
    for (int i = 0; i < text.length(); ++i) {
        trie.contains(text, i);
    }
    // print visit state for every word from trie
    for (int i = 0; i < m; ++i) {
        if ( trie.get_visited(word_level[i]) ) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}

