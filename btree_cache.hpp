#ifndef BTREE_CACHE_HPP
#define BTREE_CACHE_HPP

#include "cache_interface.hpp"
#include <btree_map.h>
#include <optional>
#include <cstddef>

template <typename Key, typename Value, size_t Capacity>
class BTreeCache : public CacheInterface<Key, Value> {
public:
    BTreeCache();
    
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
    btree::btree_map<Key, Value> map_;
    size_t hit_count_;
    size_t miss_count_;
};

#include "btree_cache.tpp"

#endif // BTREE_CACHE_HPP
