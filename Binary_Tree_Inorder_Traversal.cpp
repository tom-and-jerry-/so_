/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        return universalTraversal(root, 1);
        /*
        vector<int> ret;
        
        stack<TreeNode*> s;
        stack<bool> s_expaneded;
        s.push(root);
        s_expaneded.push(false); 
        
        while (!s.empty()) {
            TreeNode *cur = s.top(); s.pop();
            bool state = s_expaneded.top(); s_expaneded.pop();
            
            if (cur != nullptr) {
                if (state == true) 
                    ret.push_back(cur->val);
                else {
                    s.push(cur->right);
                    s_expaneded.push(false);
                    s.push(cur);
                    s_expaneded.push(true);
                    s.push(cur->left);
                    s_expaneded.push(false);
                }
            }
        }
        return ret;*/
    }
private:
    // 0 => state[root, 0] (1)
    // visit(root->left, 0) => state[root->left, 0] (2)
    // 1 => state[root, 1] (3)
    // visit(root->right, 0) => state[root->right, 0] (4)
    // 2  => state[root, 2] (5)
    vector<int> universalTraversal(TreeNode *root, int pos) {
        vector<int> ret;
        
        vector<pair<TreeNode*, int> > s;
        s.push_back({root, 0});
        
        while (!s.empty()) {
            auto state = s.back();
            s.pop_back();
            
            if (state.first != nullptr) {            
                if (state.second == pos) {
                    ret.push_back(state.first->val);
                }
                if (state.second == 0) {
                    s.push_back({state.first, 1});
                    s.push_back({state.first->left, 0});
                } else if (state.second == 1) {
                    s.push_back({state.first, 2});
                    s.push_back({state.first->right, 0});
                }
            }
        }
        return ret;
    }
};


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        auto cur = root;
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                ret.push_back(cur->val);
                cur = cur->right; //!!
            } else {
                TreeNode *prev = cur->left;
                while (prev->right != nullptr && 
                       prev->right != cur) {
                    prev = prev->right;           
                }
                if (prev->right == nullptr) {
                    prev->right = cur;
                    cur = cur->left;
                } else if (prev->right == cur) {
                    ret.push_back(cur->val);
                    prev->right = nullptr;
                    cur = cur->right;
                }
            }
        }
        return ret;
    }
};

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Tree {
 public:
  Tree(TreeNode *r) : root(r) {}
 
  class Iterator {
   public:
    Iterator(TreeNode *root) {
      if (root != nullptr) {
        states.push(make_pair(root, 0));
      }
      cur = root;
      find_valid();
    }
    TreeNode *operator ->() {
      return cur;
    }
    Iterator& operator ++ () {
      advance();
      find_valid();
      return *this;
    }
    bool operator != (Iterator another) {
      return cur != another.cur;
    }
    int operator *() {
      return cur->val;
    }
    Iterator operator ++ (int) {
      Iterator tmp = *this;
      advance();
      find_valid();
      return tmp;
    }
   private:
    void find_valid() {
      while (!states.empty() && states.top().second != 1) {
        advance();
      }
    }
    void advance() {
     if (!states.empty()) {
       auto top = states.top();
       states.pop();
       if (top.second == 0) {
         states.push(make_pair(top.first, 1));
         if (top.first->left != nullptr) {
           states.push(make_pair(top.first->left, 0));
         }
       } else if (top.second == 1) {
         states.push(make_pair(top.first, 2));
         if (top.first->right != nullptr) {
           states.push(make_pair(top.first->right, 0));
         }
       } else if (top.second == 2) {
       }
     }
     if (!states.empty()) {
       cur = states.top().first;
     } else {
       cur = nullptr;
     }
    }
    TreeNode *cur;
    stack<pair<TreeNode*, int> > states;
  };
  Iterator begin() {
    return Iterator(root);
  }
  Iterator end() {
    return Iterator(nullptr);
  }
 private:
  TreeNode *root;
};
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        auto cur = root;
        Tree t = Tree(root);
        Tree::Iterator it = t.begin();
        while (it != t.end()) {
            ret.push_back(*it);
            it++;
        }
        return ret;
    }
};
