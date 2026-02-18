#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

struct Graph {
    int n, m;
    std::vector<std::vector<int>> G;
    std::vector<std::vector<int>> Gr;
    std::vector<int> g;
    std::vector<int> deg;
    std::vector<bool> is_inf;

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
            int u = q.front(); q.pop();
            std::vector<int>& vals = values[u];
            std::sort(vals.begin(), vals.end());
            vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

            int mex = 0;
            for (int v : vals) {
                if (v == mex) {
                    mex++;
                } else {
                    if (v > mex) break;
                }
            }
            g[u] = mex;
            is_inf[u] = false;

            for (int p : Gr[u]) {
                values[p].push_back(mex);
                delta[p]--;
                if (delta[p] == 0) {
                    q.push(p);
                }
            }
        }
    }
};

Graph G1, G2;

std::map<int, int> mem[2][10009];

int calc(int gid, int u, int K) {
    if (mem[gid][u].find(K) != mem[gid][u].end()) {
        int res = mem[gid][u][K];
        if (res == 1) return 4;
        return res;
    }

    mem[gid][u][K] = 1;
    Graph& GG = (gid == 0) ? G1 : G2;
    bool can = false;
    bool all_win = true;
    bool has = false;

    for (int v : GG.G[u]) {
        has = true;
        int stat;
        if (!GG.is_inf[v]) {
            if (GG.g[v] == K) {
                stat = 3;
            } else {
                stat = 2;
            }
        } else {
            stat = calc(gid, v, K);
        }
        if (stat == 3) {
            can = true;
            break;
        }
        if (stat != 2) {
            all_win = false;
        }
    }

    int res;
    if (!has) {
        res = 3; 
    } else if (can) {
        res = 2;
    } else if (all_win) {
        res = 3;
    } else {
        res = 4;
    }

    mem[gid][u][K] = res;
    return res;
}

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
        } else if (inf1 && !inf2) {
            int res = calc(0, u, G2.g[v]);
            if (res == 2) {
                std::cout << "first\n";
            } else if (res == 3) {
                std::cout << "second\n";
            } else {
                std::cout << "draw\n";
            }
        } else if (!inf1 && inf2) {
            int res = calc(1, v, G1.g[u]);
            if (res == 2) {
                std::cout << "first\n";
            } else if (res == 3) {
                std::cout << "second\n";
            }
            else std::cout << "draw\n";
        } else {
            bool p1_wins = false;

            for (int next_u : G1.G[u]) {
                if (!G1.is_inf[next_u]) {
                    if (calc(1, v, G1.g[next_u]) == 3) {
                        p1_wins = true;
                        break;
                    }
                }
            }

            if (!p1_wins) {
                for (int next_v : G2.G[v]) {
                    if (!G2.is_inf[next_v]) {
                        if (calc(0, u, G2.g[next_v]) == 3) {
                            p1_wins = true;
                            break;
                        }
                    }
                }
            }

            if (p1_wins) {
                std::cout << "first\n";
            } else {
                std::cout << "draw\n";
            }
        }
    }
}
