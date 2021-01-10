#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int ROW[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int COL[] = { -1, 1, 1, -1, 2, -2, 2, -2 };

void BFS(int x_start, int y_start, int x_fin, int y_fin, int n) {
    int start = (x_start * n) + y_start;
    int fin = (x_fin * n) + y_fin;
    vector<bool> used (n * n, false);
    used[start] = true;
    vector<int> dist (n * n), parent (n * n);
    dist[start] = 1;
    queue<int> q;
    q.push(start);
    int curr_pos, new_pos, x, y;
    while (!q.empty()) {
        curr_pos = q.front();
        q.pop();
        if (curr_pos == fin) {
            cout << dist[curr_pos] << "\n";
            // get path via parent vector
            vector<int> path;
            while (curr_pos != start) {
                path.push_back(curr_pos);
                curr_pos = parent[curr_pos];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            for (int pos : path) {
                cout << (pos / n) + 1 << " " << (pos % n) + 1 << "\n";
            }
            return;
        }
        for (int i = 0; i < 8; ++i) {
            x = (curr_pos / n) + ROW[i];
            y = (curr_pos % n) + COL[i];
            new_pos = (x * n) + y;
            // validate if position is inside board
            if ( (x >= 0 && y >= 0 && x < n && y < n) && (!used[new_pos]) ){
                    used[new_pos] = true;
                    dist[new_pos] = dist[curr_pos] + 1;
                    parent[new_pos] = curr_pos;
                    q.push(new_pos);
            }
        }
    }
}

int main() {
    int n, x1, x2, y1, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    BFS(x1 - 1, y1 - 1, x2 - 1, y2 - 1, n);
    return 0;
}

