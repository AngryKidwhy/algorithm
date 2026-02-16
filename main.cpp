#include <iostream>
#include <vector>
#include <functional>

enum GameResult {
    Win,
    Lost,
    Draw
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n;
    while (std::cin >> n) {
        int m;
        std::cin >> m;
        std::vector<std::vector<int>> G(n);
        std::vector<std::vector<int>> Gr(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            std::cin >> a >> b;
            --a; --b;
            G[a].push_back(b);
            Gr[b].push_back(a);
        }
        std::vector<int> out(n);
        for (int i = 0; i < n; ++i) {
            out[i] = (int)G[i].size();
        }
        std::vector<int>result(n, Draw);
        std::vector<bool> marked(n);
        std::vector<int> layer1, layer2;
        for (int i = 0; i < n; ++i) {
            if (out[i] > 0) {
                continue;
            }
            result[i] = Lost;
            layer1.push_back(i);
        }
        int type_of_layer = Lost;
        while (layer1.size() > 0) {
            std::function<bool(int)> condition;
            layer2.clear();
            int res = type_of_layer;
            if (type_of_layer == Lost) {
                condition = [&](int v) { return false; };
                type_of_layer = Win;
            } else {
                condition = [&](int v) { return out[v] > 0; };
                type_of_layer = Lost;
            }
            for (auto v : layer1) {
                result[v] = res;
                for (auto u : Gr[v]) {
                    --out[u];
                    if (marked[u]) continue;
                    if (condition(u)) continue;
                    marked[u] = true;
                    layer2.push_back(u);
                }
            }
            std::swap(layer1, layer2);
        }
        for (int i = 0; i < n; ++i) {
            if (result[i] == Win) {
                std::cout << "FIRST\n";
            }
            if (result[i] == Lost) {
                std::cout << "SECOND\n";
            }
            if (result[i] == Draw) {
                std::cout << "DRAW\n"; 
            }
        }
        std::cout << "\n";
    }
}