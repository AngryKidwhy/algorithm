#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Graph {
    int n, m;
    std::vector<std::vector<int>> G; 
    std::vector<std::vector<int>> Gr;
    std::vector<int> g;
    std::vector<std::vector<int>> S;
    std::vector<bool> is_inf;

    void read() {
        std::cin >> n >> m;
        G.resize(n + 1);
        Gr.resize(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            G[u].push_back(v);
            Gr[v].push_back(u);
        }
    }

    void solve() {
        g.resize(n + 1, -1);
        S.resize(n + 1);
        is_inf.resize(n + 1);

        std::vector<int> cnt(n + 1);
        std::vector<int> layer1;
        std::vector<bool> marked(n + 1, 1);
        std::vector<bool> has(n + 1);

        for (int i = 1; i <= n; ++i) {
            cnt[i] = (int)G[i].size();
            layer1.push_back(i);
        }

        std::vector<int> deg(n + 1);
        std::vector<bool> has_k(n + 1);
        std::vector<bool> is_k(n + 1);

        for (int k = 0; k <= n; ++k) {
            if (layer1.empty()) {
                break;
            }

            if (k > 0) {
                for (int u : layer1) {
                    if (marked[u] && !has[u]) {
                        marked[u] = 0;
                    }
                }
            }

            std::queue<int> q;
            for (int u : layer1) {
                has[u] = 0;
                has_k[u] = 0;
                is_k[u] = 0;
                deg[u] = cnt[u];
                
                if (marked[u] && deg[u] == 0) {
                    is_k[u] = true;
                    q.push(u);
                }
            }

            bool found = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                g[u] = k;
                found = true;

                for (int v : Gr[u]) {
                    has[v] = 1;
                    if (g[v] == -1 && !has_k[v]) {
                        has_k[v] = 1;
                        for (int p : Gr[v]) {
                            if (g[p] == -1) {
                                deg[p]--;
                                if (deg[p] == 0 && marked[p] && !has_k[p] && !is_k[p]) {
                                    is_k[p] = 1;
                                    q.push(p);
                                }
                            }
                        }
                    }
                }
            }

            if (!found) {
                break;
            }

            std::vector<int> layer2;
            for (int u : layer1) {
                if (g[u] == -1) {
                    layer2.push_back(u);
                } else {
                    for (int p : Gr[u]) {
                        cnt[p]--;
                    }
                }
            }
            std::swap(layer1, layer2);
        }

        for (int u = 1; u <= n; ++u) {
            if (g[u] == -1) {
                is_inf[u] = 1;
                for (int v : G[u]) {
                    if (g[v] != -1) {
                        S[u].push_back(g[v]);
                    }
                }
                std::sort(S[u].begin(), S[u].end());
                S[u].erase(std::unique(S[u].begin(), S[u].end()), S[u].end());
            }
        }
    }
};

Graph G1, G2;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    G1.read();

    G1.solve();

    for (int i = 0; i < G1.n; i++) {
        std::cout << G1.g[i + 1] << ' ';
    }
    std::cout << '\n';
}