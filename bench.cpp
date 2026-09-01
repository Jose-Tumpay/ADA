#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

long long cubic(const std::vector<int>& a) {
    long long best = std::numeric_limits<long long>::min();
    int n = (int)a.size();
    for (int i=0;i<n;i++) {
        for (int j=i;j<n;j++) {
            long long s=0;
            for (int k=i;k<=j;k++) s += a[k];
            best = std::max(best, s);
        }
    }
    return best;
}
long long quad(const std::vector<int>& a) {
    long long best = std::numeric_limits<long long>::min();
    int n = (int)a.size();
    for (int i=0;i<n;i++) {
        long long s=0;
        for (int j=i;j<n;j++) { s += a[j]; best = std::max(best, s); }
    }
    return best;
}
long long kadane(const std::vector<int>& a) {
    long long cur = a[0], best = a[0];
    for (size_t i=1;i<a.size();i++) { cur = std::max((long long)a[i], cur + a[i]); best = std::max(best, cur); }
    return best;
}
std::vector<int> randArr(int n, std::mt19937& rng) {
    std::uniform_int_distribution<int> d(-1000,1000);
    std::vector<int> a(n);
    for (int i=0;i<n;i++) a[i] = d(rng);
    return a;
}

template<typename F>
double timeFn(F&& f, int n) {
    std::mt19937 rng(123+n);
    auto a = randArr(n, rng);
    auto t0 = std::chrono::high_resolution_clock::now();
    long long x = 0;
    for (int rep=0; rep<3; rep++) x = f(a);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt = t1-t0;
    return dt.count()/3.0;
}

int main(){
    std::vector<int> ns = {1000,2000,4000,8000,16000,32000};
    for (int n: ns){
        double tc = timeFn(cubic, n);
        double tq = timeFn(quad, n);
        double tk = timeFn(kadane, n);
        std::cout << n << " " << tc << " " << tq << " " << tk << "\n";
    }
}
