#include "hash_table.h"

const int kMaxListSize = 4;

using std::string;

template<typename T>
HashTable<T>::HashTable(int initial_capacity)
    : capacity_(initial_capacity),
      table_size_(initial_capacity / kMaxListSize), size_(0) {
  table_ = new NodePtr[table_size_];
  for (int idx = 0; idx < table_size_; ++idx) {
    table_[idx] = NULL;
  }
}

template<typename T>
HashTable<T>::~HashTable() {
  for (int idx = 0; idx < table_size_; ++idx) {
    Node* head = table_[idx];
    while (head) {
      Node* next = head->next_;
      delete head;
      head = next;
    }
  }
  delete [] table_;
}

template<typename T>
void HashTable<T>::put(const string& key, const T& value) {
  Node* element = new Node(key, value);
  int h = hash(key);
  Node* head = table_[h];
  if (head) {
    while (head->next_) { head = head->next_; }
    head->next_ = element;
  } else {
    table_[h] = element;
  }
  ++size_;
}

template<typename T>
bool HashTable<T>::has_key(const string& key) const {
  return (lookup(key) != NULL);
}

template<typename T>
const T& HashTable<T>::get(const string& key) const {
  const Node* element = lookup(key);
  if (element) { return element->value_; }
  throw new NotFoundException;
}

template<typename T>
void HashTable<T>::remove(const string& key) {
  int h = hash(key);
  Node* head = table_[h];
  Node* prev = NULL;
  while (head) {
    if (head->key_ == key) {
      if (prev) {
        prev->next_ = head->next_;
      } else {
        table_[h] = head->next_;
      }
      delete head;
      return;
    }
    prev = head;
    head = head->next_;
  }
  throw new NotFoundException;
}

template<typename T>
int HashTable<T>::size() const {
  return size_;
}

template<typename T>
int HashTable<T>::hash(const string& key) const {
  int h = 3;
  for (string::const_iterator it = key.begin(); it != key.end(); ++it) {
    h *= 17;
    h += (unsigned short)(*it);
  }
  return h % table_size_;
}

template<typename T>
const typename HashTable<T>::Node* HashTable<T>::lookup(const string& key) const {
  const Node* head = table_[hash(key)];
  while (head) {
    if (head->key_ == key) { return head; }
    head = head->next_;
  }
  return NULL;
}

