#include "benchmark.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

template <typename Cache>
BenchmarkResult CacheBenchmark::run_benchmark(
    Cache& cache,
    const std::vector<typename Cache::key_type>& keys,
    const std::vector<typename Cache::mapped_type>& values,
    const std::string& test_name) {
    
    if (keys.size() != values.size()) {
        throw std::invalid_argument("Keys and values vectors must have the same size");
    }
    
    cache.clear();
    BenchmarkResult result;
    result.test_name = test_name;
    result.cache_size = cache.size();
    
    const auto start = std::chrono::high_resolution_clock::now();
    
    // Operaciones de inserción
    for (size_t i = 0; i < keys.size(); ++i) {
        cache.insert(keys[i], values[i]);
    }
    
    // Operaciones de búsqueda
    for (size_t i = 0; i < keys.size(); ++i) {
        cache.get(keys[i]);
    }
    
    // Operaciones de eliminación
    for (size_t i = 0; i < keys.size(); ++i) {
        cache.remove(keys[i]);
    }
    
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    
    result.time_seconds = elapsed.count();
    result.ops_per_second = keys.size() * 3 / elapsed.count(); // 3 operaciones por clave
    result.hit_rate = cache.get_hit_rate();
    
    return result;
}

void CacheBenchmark::print_results(const std::vector<BenchmarkResult>& results) {
    std::cout << "\n=== Resultados del Benchmark ===\n";
    std::cout << std::left << std::setw(20) << "Test"
              << std::setw(15) << "Tiempo (s)"
              << std::setw(15) << "Ops/s"
              << std::setw(15) << "Hit Rate"
              << std::setw(15) << "Tamaño Cache"
              << "\n";
    
    for (const auto& res : results) {
        std::cout << std::left << std::setw(20) << res.test_name
                  << std::setw(15) << res.time_seconds
                  << std::setw(15) << res.ops_per_second
                  << std::setw(15) << res.hit_rate
                  << std::setw(15) << res.cache_size
                  << "\n";
    }
}

void CacheBenchmark::save_to_csv(const std::vector<BenchmarkResult>& results, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escribir los resultados");
    }
    
    out << "Test,Tiempo (s),Operaciones/s,Tasa de aciertos,Tamaño cache\n";
    for (const auto& res : results) {
        out << res.test_name << ","
            << res.time_seconds << ","
            << res.ops_per_second << ","
            << res.hit_rate << ","
            << res.cache_size << "\n";
    }
    
    out.close();
}

// Instanciaciones explícitas para los tipos que usaremos
template BenchmarkResult CacheBenchmark::run_benchmark(
    FlatMapCache<int, int, 1000>&,
    const std::vector<int>&,
    const std::vector<int>&,
    const std::string&);

template BenchmarkResult CacheBenchmark::run_benchmark(
    BTreeCache<int, int, 1000>&,
    const std::vector<int>&,
    const std::vector<int>&,
    const std::string&);
