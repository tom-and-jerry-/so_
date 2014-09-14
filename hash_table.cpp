#include <vector>
#include <cstdio>

using namespace std;

template <class Key, class Value> 
struct hash_node {
  hash_node(Key k, Value v) : key(k), value(v) {}
  Key key;
  Value value;
  hash_node *next;
};


template <typename Key, typename Value> 
class hash_table {
 typedef hash_node<Key, Value> node;

 public:

  class iterator {
   public:
    typedef hash_table<Key, Value> hash_table;
    typedef hash_node<Key, Value> node;
    iterator(node *c, size_t bkn, hash_table* h) : cur(c), bk_num(bkn), ht(h) {}

    iterator& operator++ () {
      printf("%d->", cur == nullptr);
      cur = cur->next; 
      while (cur == nullptr && ++bk_num < ht->buckets.size()) {
        cur = ht->buckets[bk_num];
      }
      return *this;
    }
    iterator operator++(int) {
      iterator *tmp = *this;
      ++(*this);
      return tmp;
    }
    node* operator -> () {
      return cur;
    }

    bool operator != (const iterator &another) const {
      return cur != another.cur;
    }

   private:
    node *cur;
    hash_table *ht;
    size_t bk_num;
  };

  hash_table () {
    size = 997;
    buckets = vector<node*>(size);
  }
  void insert(const Key &k, const Value &v) {
    int bk_num = hash(k);
    node **pos = find_pos(k);
    if (*pos == nullptr) {
      (*pos) = new node(k, v);
    } else {
      (*pos)->value = v;
    }
  }
  bool find(const Key &k, Value &v) {
    int bk_num = hash(k);
    node **pos = find_pos(k);
    if (*pos == nullptr) {
      return false;
    } else {
      v = (*pos)->value;
      return true;
    }
  }

  void remove(const Key &k) {
    int bk_num = hash(k);
    node **pos = find_pos(k);
    if (*pos == nullptr) {
      ;
    } else {
      node *tmp = (*pos);
      *pos = (*pos)->next;
      delete tmp;
    }
  }

  iterator begin() {
    node *cur = nullptr;
    size_t bkn = 0;
    while (cur == nullptr && bkn < buckets.size()) {
      cur = buckets[bkn++];
    }
    return iterator(cur, bkn, this);
  }
  iterator end() {
    return iterator(nullptr, buckets.size(), this);
  }

 private:
   node **find_pos(const Key &k) {
    int bk_num = hash(k);
    node **cur = &buckets[bk_num];
    while (*cur != nullptr && (*cur)->key != k) {
      cur = &((*cur)->next);
    }
    return cur;
  }

  void disp() {
    for (size_t i = 0; i < buckets.size(); ++i) {
      auto cur = buckets[i];
      while (cur) {
        printf("%d:%d->", cur->key, cur->value);
        //cout << ccur->value << " ";
        cur = cur->next;
      }
      printf("\n");
    }
  }
  
  size_t hash(Key k) {
    return k % size; // k.hash() % k
  }
  size_t size;
  vector<node*> buckets;
};
int main() {
  hash_table<int, int> t;
  for (int i = 0; i < 20; ++i) {
    t.insert(i, i+10);
  }
  int a;
  //cout << t.find(1, a) << endl;
  t.remove(10);
  t.insert(1,11);
  t.disp();

  auto it = t.begin();
  while (it != t.end()) {
    ++it;
    printf("%d\n", it->key);
  }

  return 0;
}
