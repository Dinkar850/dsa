## 5.10.2026

## Search in BST

```cpp
// go left if need smaller else go right like in BS
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(!root) return nullptr;
        if(root -> val == val) return root;
        if(val > root -> val) return searchBST(root -> right, val);
        return searchBST(root -> left, val);
    }
};
```

## Ceil in BST

```cpp
class Solution {
    void solve(Node* root, int x, int& res) {
        if(!root) return;
        // save if found better root->data
        if(root -> data >= x) {
            res = root -> data; //when you go left you'll automatically find a lesser value greater than equal to x, like in BS
            solve(root -> left, x, res);
            return;
        }
        // go right for finding a greater value
        solve(root -> right, x, res);
        return;
    }
  public:
    int findCeil(Node* root, int x) {
        // code here
        int res = INT_MAX;
        solve(root, x, res);
        if (res == INT_MAX) return -1;
        return res;
    }
};
```

## Min and Max in a BST

- left most is min
- right most is max

```cpp
class Solution {
  public:
    int minValue(Node* root) {
        // code here
        while(root -> left) {
            root = root -> left;
        }

        return root -> data;
    }
};
```

## 26th July26

## Kth smallest node in BST

- BF: traverse -> sort -> find kth smallest or largest
- Optimise: inorder -> kth smallest
- Most optimal: use this snippet below in any order traversal / morris traversal (when you traverse the node after or before left / right traversals)

```cpp
 cnt++;
if(cnt == k) {
    res = root -> val;
    return;
}
```

- Solution: https://leetcode.com/submissions/detail/2082275485/
- for kth largest, use n - kth smallest :D
