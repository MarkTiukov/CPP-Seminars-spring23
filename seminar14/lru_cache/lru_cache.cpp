#include <iostream>

/// https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU

#include <list>
#include <unordered_map>

class LRUCache {
 public:
  LRUCache(size_t capacity) : capacity_(capacity) {}

  int get(int key) {
    if (cache_.find(key) == cache_.end())
      return -1;
    use_timeline_.splice(use_timeline_.begin(), use_timeline_, cache_[key]);
    return cache_[key]->second;
  }

  void put(int key, int value) {
    if (cache_.find(key) != cache_.end()) {
      use_timeline_.splice(use_timeline_.begin(), use_timeline_, cache_[key]);
      cache_[key]->second = value;
      return;
    }
    if (use_timeline_.size() == capacity_) {
      auto d_key = use_timeline_.back().first;
      use_timeline_.pop_back();
      cache_.erase(d_key);
    }
    use_timeline_.push_front({key, value});
    cache_[key] = use_timeline_.begin();

  }

 private:
  const size_t capacity_;
  std::list<std::pair<int, int>> use_timeline_;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_;
};