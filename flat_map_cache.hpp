#ifndef FLAT_MAP_CACHE_HPP
#define FLAT_MAP_CACHE_HPP

#include "cache_interface.hpp"
#include <boost/container/flat_map.hpp>
#include <optional>
#include <cstddef>

template <typename Key, typename Value, size_t Capacity>
class FlatMapCache : public CacheInterface<Key, Value> {
public:
    FlatMapCache();
    
    bool insert(const Key& key, const Value& value) override;
    std::optional<Value> get(const Key& key) override;
    bool remove(const Key& key) override;
    size_t size() const override;
    void clear() override;
    
    size_t get_hit_count() const override;
    size_t get_miss_count() const override;
    double get_hit_rate() const override;
    void reset_stats() override;

private:
    boost::container::flat_map<Key, Value> map_;
    size_t hit_count_;
    size_t miss_count_;
};

#include "flat_map_cache.tpp"

#endif // FLAT_MAP_CACHE_HPP
