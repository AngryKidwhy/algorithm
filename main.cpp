#include <iostream>

const int N = 100'000;
const int M = 460;

bool dp[N + 1][M + 1];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= std::min(i, M - 1); ++j) {
            if (!dp[i - j][j]) {
                dp[i][j] = 1;
            } else
            if (i - j - 1 >= 0 && !dp[i - j - 1][j + 1]) {
                dp[i][j] = 1;
            }
        }
    }
    int n, t = 0;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }
        ++t;
        if (dp[n - 1][1]) {
            std::cout << "Case #" << t << ": Second player wins.\n";
        } else {
            std::cout << "Case #" << t << ": First player wins.\n";
        }
    }
}
