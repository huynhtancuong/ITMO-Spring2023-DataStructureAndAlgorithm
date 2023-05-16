#include <iostream>
#include <queue>

#define maxN 100

bool a[maxN][maxN];
int Trace[maxN];
int n;
int color[maxN];

using namespace std;

void enter() {
    cin >> n;
    fill(a[0], a[0] + maxN * maxN, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 0) break;
            x--;
            a[i][x] = true;
            a[x][i] = true;
        } 
    }
    return;
}

int BFS() {
    queue<int> q;
    int u, v;

    q.push(0);
    fill(Trace, Trace + maxN, 0);
    Trace[0] = -1;
    do {
        u = q.front();
        q.pop();
        for (int v = 0; v<n; v++) {
            if (a[u][v]) {
                if (color[v] == color[u])
                    return -1;
                if (Trace[v]==0) {
                    q.push(v);
                    Trace[v] = u;
                    if (color[v] == -1)
                        color[v] = 1 - color[u];
                }
            }
                
        }
    } while (!q.empty());
    return 0;
}

int main() {

    enter();
    fill(color, color + maxN, -1);
    color[0] = 0;
    int status = BFS();
    if (status == -1)
        cout << "-1" << endl;
    else
    {
        for (int i = 0; i < n; i++) {
            cout << color[i];
        }
    }

    return 0;
}