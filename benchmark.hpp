#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include "cache_interface.hpp"
#include <chrono>
#include <vector>
#include <string>

struct BenchmarkResult {
    std::string test_name;
    double time_seconds;
    double ops_per_second;
    double hit_rate;
    size_t cache_size;
};

class CacheBenchmark {
public:
    template <typename Cache>
    static BenchmarkResult run_benchmark(
        Cache& cache,
        const std::vector<typename Cache::key_type>& keys,
        const std::vector<typename Cache::mapped_type>& values,
        const std::string& test_name);
    
    static void print_results(const std::vector<BenchmarkResult>& results);
    static void save_to_csv(const std::vector<BenchmarkResult>& results, const std::string& filename);
};

#endif // BENCHMARK_HPP
