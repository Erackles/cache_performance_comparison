#include "btree_cache.hpp"
#include <stdexcept>

template <typename Key, typename Value, size_t Capacity>
BTreeCache<Key, Value, Capacity>::BTreeCache() 
    : hit_count_(0), miss_count_(0) {}

template <typename Key, typename Value, size_t Capacity>
bool BTreeCache<Key, Value, Capacity>::insert(const Key& key, const Value& value) {
    if (map_.size() >= Capacity) {
        return false;
    }
    
    map_[key] = value;
    return true;
}

template <typename Key, typename Value, size_t Capacity>
std::optional<Value> BTreeCache<Key, Value, Capacity>::get(const Key& key) {
    auto it = map_.find(key);
    if (it != map_.end()) {
        ++hit_count_;
        return it->second;
    }
    ++miss_count_;
    return std::nullopt;
}

template <typename Key, typename Value, size_t Capacity>
bool BTreeCache<Key, Value, Capacity>::remove(const Key& key) {
    return map_.erase(key) > 0;
}

template <typename Key, typename Value, size_t Capacity>
size_t BTreeCache<Key, Value, Capacity>::size() const {
    return map_.size();
}

template <typename Key, typename Value, size_t Capacity>
void BTreeCache<Key, Value, Capacity>::clear() {
    map_.clear();
    reset_stats();
}

template <typename Key, typename Value, size_t Capacity>
size_t BTreeCache<Key, Value, Capacity>::get_hit_count() const {
    return hit_count_;
}

template <typename Key, typename Value, size_t Capacity>
size_t BTreeCache<Key, Value, Capacity>::get_miss_count() const {
    return miss_count_;
}

template <typename Key, typename Value, size_t Capacity>
double BTreeCache<Key, Value, Capacity>::get_hit_rate() const {
    const size_t total = hit_count_ + miss_count_;
    return total > 0 ? static_cast<double>(hit_count_) / total : 0.0;
}

template <typename Key, typename Value, size_t Capacity>
void BTreeCache<Key, Value, Capacity>::reset_stats() {
    hit_count_ = 0;
    miss_count_ = 0;
}

// Instanciaciones explícitas para los tipos que usaremos
template class BTreeCache<int, int, 1000>;
template class BTreeCache<std::string, std::string, 1000>;
