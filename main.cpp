#include "flat_map_cache.hpp"
#include "btree_cache.hpp"
#include "benchmark.hpp"
#include <vector>
#include <random>
#include <string>
#include <algorithm>

std::vector<int> generate_random_int_data(size_t count, int min = 0, int max = 10000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    
    std::vector<int> data(count);
    std::generate(data.begin(), data.end(), [&]() { return distrib(gen); });
    return data;
}

std::vector<std::string> generate_random_string_data(size_t count, size_t length = 10) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, sizeof(alphanum) - 2);
    
    std::vector<std::string> data(count);
    for (auto& s : data) {
        s.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            s += alphanum[distrib(gen)];
        }
    }
    return data;
}

int main() {
    constexpr size_t test_size = 10000;
    constexpr size_t cache_capacity = 1000;
    
    // Generar datos de prueba
    auto int_keys = generate_random_int_data(test_size);
    auto int_values = generate_random_int_data(test_size);
    
    auto str_keys = generate_random_string_data(test_size);
    auto str_values = generate_random_string_data(test_size);
    
    // Crear instancias de caché
    FlatMapCache<int, int, cache_capacity> flat_map_int_cache;
    BTreeCache<int, int, cache_capacity> btree_int_cache;
    
    FlatMapCache<std::string, std::string, cache_capacity> flat_map_str_cache;
    BTreeCache<std::string, std::string, cache_capacity> btree_str_cache;
    
    // Ejecutar benchmarks
    std::vector<BenchmarkResult> results;
    
    results.push_back(CacheBenchmark::run_benchmark(
        flat_map_int_cache, int_keys, int_values, "FlatMap Int Cache"));
    
    results.push_back(CacheBenchmark::run_benchmark(
        btree_int_cache, int_keys, int_values, "BTree Int Cache"));
    
    results.push_back(CacheBenchmark::run_benchmark(
        flat_map_str_cache, str_keys, str_values, "FlatMap Str Cache"));
    
    results.push_back(CacheBenchmark::run_benchmark(
        btree_str_cache, str_keys, str_values, "BTree Str Cache"));
    
    // Mostrar y guardar resultados
    CacheBenchmark::print_results(results);
    CacheBenchmark::save_to_csv(results, "benchmark_results.csv");
    
    return 0;
}
