#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Graph {
    int n, m;
    std::vector<std::vector<int>> G;
    std::vector<std::vector<int>> Gr;
    std::vector<int> g;
    std::vector<int> deg;
    std::vector<bool> is_inf;
    std::vector<std::vector<int>> S;

    void read() {
        std::cin >> n >> m;
        G.resize(n + 1);
        Gr.resize(n + 1);
        deg.resize(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            std::cin >> u >> v;
            G[u].push_back(v);
            Gr[v].push_back(u);
            deg[u]++;
        }
    }

    void solve() {
        g.resize(n + 1, -1);
        is_inf.resize(n + 1, true);
        
        std::vector<int> delta = deg;
        std::vector<std::vector<int>> values(n + 1);

        std::queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front(); 
            q.pop();

            std::vector<int>& vals = values[u];
            std::sort(vals.begin(), vals.end());
            vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

            int mex = 0;
            for (int v : vals) {
                if (v == mex) {
                    mex++;
                } else 
                if (v > mex) {
                    break;
                }
            }
            g[u] = mex;
            is_inf[u] = false;

            for (int p : Gr[u]) {
                values[p].push_back(mex);
                --delta[p];
                if (delta[p] == 0) {
                    q.push(p);
                }
            }
        }

        S.resize(n + 1);
        for (int u = 1; u <= n; ++u) {
            if (is_inf[u]) {
                for (int v : G[u]) {
                    if (!is_inf[v]) {
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
    G2.read();

    G1.solve();
    G2.solve();

    int tt;
    std::cin >> tt;
    while (tt--) {
        int u, v;
        std::cin >> u >> v;

        bool inf1 = G1.is_inf[u];
        bool inf2 = G2.is_inf[v];

        if (!inf1 && !inf2) {
            if ((G1.g[u] ^ G2.g[v]) != 0) {
                std::cout << "first\n";
            } else {
                std::cout << "second\n";
            }
        } 
        else if (inf1 && !inf2) {
            int K = G2.g[v];
            auto it = std::lower_bound(G1.S[u].begin(), G1.S[u].end(), K);
            if (it != G1.S[u].end() && *it == K) {
                std::cout << "first\n";
            } else {
                std::cout << "draw\n";
            }
        } 
        else if (!inf1 && inf2) {
            int K = G1.g[u];
            auto it = std::lower_bound(G2.S[v].begin(), G2.S[v].end(), K);
            if (it != G2.S[v].end() && *it == K) {
                std::cout << "first\n";
            } else {
                std::cout << "draw\n";
            }
        } 
        else {
            std::cout << "draw\n";
        }
    }
}
