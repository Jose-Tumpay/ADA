#pragma once

#include <algorithm>
#include <climits>
#include <vector>

long long cubicMaxSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;

    long long best = LLONG_MIN;
    const int n = static_cast<int>(arr.size());

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            long long sum = 0;
            for (int k = i; k <= j; ++k) {
                sum += arr[k];
            }
            best = std::max(best, sum);
        }
    }

    return best;
}

long long quadraticMaxSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;

    long long best = LLONG_MIN;
    const int n = static_cast<int>(arr.size());

    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = i; j < n; ++j) {
            sum += arr[j];
            best = std::max(best, sum);
        }
    }

    return best;
}

long long kadaneMaxSubarray(const std::vector<int>& arr) {
    if (arr.empty()) return 0;

    long long current = arr[0];
    long long best = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        current = std::max(static_cast<long long>(arr[i]), current + arr[i]);
        best = std::max(best, current);
    }
    return best;
}
