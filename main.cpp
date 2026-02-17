#include <iostream>
#include <vector>
#include <cmath>

const int N = 2'000'001;
int p[N];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int i = 2, prost = 0; i < N; ++i) if (p[i] == 0) {
        p[i] = ++prost;
        for (int64_t j = 1LL * i * i; j < N; j += i)
           p[j] = 1;
    }

    int64_t n;
    std::cin >> n;
    int nim_sum = 0;
    for (int i = 2; i <= sqrtl(n); ++i) {
        while (n % i == 0) {
            nim_sum ^= p[i];
            n /= i;
        }
    }
    if (n > 1) {
        if (n >= N) {
            nim_sum = 1;
        } else {
            nim_sum ^= p[n];
        }
    }
    std::cout << (nim_sum == 0 ? "Vasya" : "David");
}