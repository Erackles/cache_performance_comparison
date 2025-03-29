#ifndef CACHE_INTERFACE_HPP
#define CACHE_INTERFACE_HPP

#include <cstddef>
#include <optional>

template <typename Key, typename Value>
class CacheInterface {
public:
    virtual ~CacheInterface() = default;
    
    virtual bool insert(const Key& key, const Value& value) = 0;
    virtual std::optional<Value> get(const Key& key) = 0;
    virtual bool remove(const Key& key) = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;
    
    // Estadísticas de rendimiento
    virtual size_t get_hit_count() const = 0;
    virtual size_t get_miss_count() const = 0;
    virtual double get_hit_rate() const = 0;
    virtual void reset_stats() = 0;
};

#endif // CACHE_INTERFACE_HPP
