#include <iostream>
#include <queue>
#include <vector>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> G(n + 1), Gr(n + 1);
    std::vector<std::set<int>> se(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        if (se[x].find(y) == se[x].end()) {
            se[x].insert(y);
            G[x].push_back(y);
            Gr[y].push_back(x);
        }
    }

    std::vector<int> smith(n + 1, -1);
    std::vector<bool> marked(n + 1);
    std::vector<int> target(n + 1);
    std::vector<int> out_cnt(n + 1);

    for (int v = 1; v <= n; ++v) {
        out_cnt[v] = (int)G[v].size();
    }

    std::vector<std::queue<int>> qs(n + 2);

    for (int v = 1; v <= n; ++v) {
       if (out_cnt[v] == 0) {
           qs[0].push(v);
        }
    }

    for (int k = 0; k <= n; ++k) {
        std::queue<int>& q = qs[k];
        while (!q.empty()) {
            int v = q.front(); q.pop();

            if (marked[v] || target[v] != k || out_cnt[v] != 0) {   
                continue;
            }

            smith[v] = k;
            marked[v] = true;

            for (int u : Gr[v]) {
                if (marked[u] || target[u] != k) {
                    continue;
                }

                for (int w : Gr[u]) {
                    if (!marked[w] && target[w] == k) {
                        out_cnt[w]--;
                        if (out_cnt[w] == 0) {
                            q.push(w);
                        }
                    }
                }

                target[u] = k + 1;

                int cnt = 0;
                for (int x : G[u]) {    
                    if (!marked[x] && target[x] == k + 1) {
                        cnt++;
                    }
                }
                out_cnt[u] = cnt;

                for (int w : Gr[u]) {
                    if (!marked[w] && target[w] == k + 1) {
                        out_cnt[w]++;
                    }
                }

                if (cnt == 0) {
                    qs[k + 1].push(u);
                }
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        std::cout << smith[v] << " ";
    }
    std::cout << '\n';
}
