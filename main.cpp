#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "max_subarray.hpp"

namespace {

using ResultFn = long long (*)(const std::vector<int>&);

std::vector<int> makeRandomArray(int length, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(-1000, 1000);
    std::vector<int> arr(length);
    for (int i = 0; i < length; ++i) {
        arr[i] = dist(rng);
    }
    return arr;
}

bool validateRandomCases() {
    std::mt19937 rng(123456);
    const int trials = 200;

    for (int t = 0; t < trials; ++t) {
        const int length = 1 + (rng() % 80);
        auto arr = makeRandomArray(length, rng);

        const long long c = cubicMaxSubarray(arr);
        const long long q = quadraticMaxSubarray(arr);
        const long long k = kadaneMaxSubarray(arr);

        if (c != q || q != k) {
            std::cerr << "Los resultados no coinciden para el caso " << t << '\n';
            std::cerr << "Longitud: " << length << '\n';
            for (int x : arr) {
                std::cerr << x << ' ';
            }
            std::cerr << '\n';
            std::cerr << "Cubic: " << c << '\n';
            std::cerr << "Quadratic: " << q << '\n';
            std::cerr << "Kadane: " << k << '\n';
            return false;
        }
    }

    return true;
}

double benchmarkOne(ResultFn fn, int n, int repeats = 3) {
    std::mt19937 rng(2024 + n);
    std::vector<int> arr = makeRandomArray(n, rng);

    const auto start = std::chrono::high_resolution_clock::now();
    long long result = 0;
    for (int rep = 0; rep < repeats; ++rep) {
        result = fn(arr);
    }
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> elapsed = end - start;
    return elapsed.count() / repeats;
}

void printBenchmarkTable(const std::string& name, const std::vector<int>& ns, const std::vector<double>& times) {
    std::cout << "\nAlgoritmo: " << name << '\n';
    std::cout << std::left << std::setw(12) << "n"
              << std::setw(18) << "tiempo (s)"
              << std::setw(16) << "razon"
              << '\n';
    std::cout << std::string(46, '-') << '\n';

    for (size_t i = 0; i < ns.size(); ++i) {
        const double ratio = (i == 0) ? 0.0 : times[i] / times[i - 1];
        std::cout << std::left << std::setw(12) << ns[i]
                  << std::setw(18) << std::fixed << std::setprecision(6) << times[i]
                  << std::setw(16) << (i == 0 ? "-" : std::to_string(ratio))
                  << '\n';
    }
}

std::vector<int> buildNs(int maxN) {
    std::vector<int> ns = {1000, 2000, 4000, 8000};
    int current = 16000;
    while (current <= maxN) {
        ns.push_back(current);
        current *= 2;
    }
    return ns;
}

std::vector<double> benchmarkSeries(ResultFn fn, const std::vector<int>& ns, int repeatsForSmall = 3) {
    std::vector<double> times;
    for (int n : ns) {
        const int repeats = (n <= 4000) ? repeatsForSmall : 3;
        times.push_back(benchmarkOne(fn, n, repeats));
    }
    return times;
}

void benchmarkAll() {
    const std::vector<int> cubicNs = {1000, 2000, 4000, 8000};
    const std::vector<int> quadraticNs = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};
    const std::vector<int> kadaneNs = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};

    const auto cubicTimes = benchmarkSeries(cubicMaxSubarray, cubicNs, 1);
    printBenchmarkTable("Cubic", cubicNs, cubicTimes);

    const auto quadraticTimes = benchmarkSeries(quadraticMaxSubarray, quadraticNs, 3);
    printBenchmarkTable("Quadratic", quadraticNs, quadraticTimes);

    const auto kadaneTimes = benchmarkSeries(kadaneMaxSubarray, kadaneNs, 8);
    printBenchmarkTable("Kadane", kadaneNs, kadaneTimes);
}

void predictKadaneForOneHundredMillion() {
    const std::vector<int> kadaneNs = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    const auto kadaneTimes = benchmarkSeries(kadaneMaxSubarray, kadaneNs, 8);
    const double lastTime = kadaneTimes.back();
    const double lastN = static_cast<double>(kadaneNs.back());
    const double predicted = lastTime * (100'000'000.0 / lastN);

    std::cout << "\nPrediccion para n = 10^8 con Kadane: " << predicted << " s\n";
    std::cout << "Se ejecuta solo Kadane porque su crecimiento estimado es O(n), mucho menor que O(n^2) y O(n^3).\n";
}

}  // namespace

int main() {
    std::cout << "== Validacion ==\n";
    const bool ok = validateRandomCases();
    if (!ok) {
        return 1;
    }
    std::cout << "Las tres soluciones coinciden en 200 arreglos aleatorios con enteros positivos y negativos.\n\n";

    std::cout << "== Medicion de tiempo ==\n";
    benchmarkAll();

    predictKadaneForOneHundredMillion();

    std::cout << "\n== Ejecucion de la version elegida ==\n";
    std::mt19937 rng(2025);
    const int n = 100'000'000;
    std::vector<int> arr = makeRandomArray(n, rng);

    const auto start = std::chrono::high_resolution_clock::now();
    const long long result = kadaneMaxSubarray(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;

    std::cout << "Kadane para n = " << n << " -> suma maxima = " << result
              << ", tiempo real = " << elapsed.count() << " s\n";

    return 0;
}
