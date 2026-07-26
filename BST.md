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
