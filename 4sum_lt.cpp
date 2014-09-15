#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct node {
  int sum;
  int left;
  int right;
};

void build_tree(vector<node> &tree, int id, int left, int right) {
  tree[id].left = left;
  tree[id].right = right;
  tree[id].sum = 0;
  if (right - left > 1) {
    int mid = left + (right-left) / 2;
    build_tree(tree, (id << 1),   left, mid);
    build_tree(tree, (id << 1) + 1, mid, right);
  }
}

void insert(vector<node> &tree, int id, int value) {
  auto &cur = tree[id];
  if (cur.right - cur.left == 1) {
    cur.sum += 1;
  } else {
    int mid = cur.left + (cur.right - cur.left) / 2;
    if (value < mid) {
      insert(tree, (id << 1), value);
    } else {
      insert(tree, (id << 1) + 1, value);
    }
    cur.sum += 1;
  }
}

int query(vector<node> &tree, int id, int start, int end) {
  auto &cur = tree[id];
  if (cur.left == start && cur.right == end) {
    return cur.sum;
  } else {
    int mid = cur.left + (cur.right - cur.left) / 2;
    if (end <= mid) 
      return query(tree, id << 1, start, end);
    else if (start >= mid) 
      return query(tree, (id << 1) + 1, start, end);
    else 
      return query(tree, (id << 1), start, mid) + query(tree, (id << 1) + 1, mid, end);
  }
  return 0;
}

int four_sum(const vector<int> &num, int target) {
  auto num2 = num;
  int cnt = 0;

  struct {
    bool operator () (const vector<int> &a, const vector<int> &b) const {
      if (a[1] != b[1]) return a[1] < b[1];
      return a[2] < b[2];
    }
  } cmp;

  vector<vector<int> > pairs; 

  for (int i = 0; i < num.size()-1; ++i) {
    for (int j = i+1; j < num.size(); ++j)  {
      pairs.push_back({j, num[i]+num[j], 0});
      pairs.push_back({i, target - (num[i]+num[j]), 1}); 
    }
  }

  sort(pairs.begin(), pairs.end(), cmp);

  vector<node> tree(2*(pairs.size()+1));
  build_tree(tree, 1, 0, pairs.size()/2);

  int r = 0;
  for (auto p : pairs) {
    if (p[2] == 0) {
      insert(tree, 1, p[0]);
    } else {
      int ret = query(tree, 1, 0, p[0]);
      r += ret;
    }
  }
  
  return r;
}

int main() {
  vector<int> num = {1,2,2,3,4};
  int target = 9;

  cout << four_sum(num, target) << endl;

  return 0;
}
