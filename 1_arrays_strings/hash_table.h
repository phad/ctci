#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>

template<typename T>
class HashTable {
 public:
  explicit HashTable(int initial_capacity);
  ~HashTable();

  void put(const std::string& key, const T& value);
  bool has_key(const std::string& key) const;
  const T& get(const std::string& key) const;
  void remove(const std::string& key);
  int size() const;

 private:
  struct Node {
    std::string key_;
    T value_;
    Node* next_;
    Node(const std::string& key, const T& value)
        : key_(key), value_(value), next_(NULL) { }
  };

  HashTable(const HashTable&);
  HashTable& operator=(const HashTable&);
  int hash(const std::string& key) const;
  const Node* lookup(const std::string& key) const;

  typedef Node* NodePtr;
  NodePtr* table_;
  int table_size_;
  int capacity_;
  int size_;
};

class NotFoundException {};

#endif  // HASH_TABLE_H

