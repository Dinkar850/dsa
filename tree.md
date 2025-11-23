## Height of a Binary Tree:

- TC: $O{(N)}$, $N$ is number of nodes

```cpp
int height(TreeNode *root) {
    if(!root) return 0;
    return max(height(root -> left), height(root -> right)) + 1;
}
```

## Check whether height balanced:

- App1: for each node calculate left height, right height, check if abs(height(left) - height(right)) > 1, yes return false else return true, traverse right only if left one came true

```cpp
bool isBalanced(TreeNode *root) {
    if(!root) return true;
    if(abs(height(root -> left) - height(root -> right)) > 1) return false;
    return isBalanced(root -> left) && isBalanced(root -> right);
}

//we see that two times height is being calculated so, we can engineer a method that checks during height calculation only
```

- App2: during height calc

```cpp
int height(TreeNode* root) {
    if(!root) return 0;
    int lh = height(root -> left);
    int rh = height(root -> right);
    if(lh == -1 || rh == -1) return -1;
    if(abs(lh - rh) > 1) return -1;
    return max(lh, rh) + 1;
}

bool isBalanced(TreeNode* root) {
    return height(root) != -1;
}
```

## Diameter of a binary tree

```cpp
int calc(TreeNode *root, int &maxi) {
    if(!root) return 0;
    int lh = calc(root -> left, maxi);
    int rh = calc(root -> right, maxi);
    maxi = max(maxi, lh + rh);
    return max(lh, rh) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int maxi = 0;
    calc(root, maxi);
    return maxi;
}
```

## Diameter of a N-ary tree

## Maximum Path Sum

- using concept of diameter, return max(lh, rh) + node_value at a point, the trick is to return max of 0, yet calculated sum from root -> left and same for right as negatively returned value we will not take

```cpp
int calc(TreeNode *root, int &maxi) {
    if(!root) return 0;
    int lh = max(0, calc(root -> left, maxi));
    int rh = max(0, calc(root -> right, maxi));
    maxi = max(maxi, lh + rh + root -> val);
    return max(lh, rh) + root -> val;
}

int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    calc(root, maxi);
    return maxi;
}
```

## Identical Trees

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
   if(!p && !q) return true;
   if((p && !q) || (!p && q)) return false;

   //above two statements can be replaced by one line: if(!p || !q) return p == q;
   if(p -> val != q -> val) return false;
   return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);
}
```

## Symmetrical Trees

- mirror symmetry in the same tree

```cpp
bool solve(TreeNode* leftNode, TreeNode* rightNode) {
    if(!leftNode || !rightNode) return leftNode == rightNode;
    if(leftNode -> val != rightNode -> val) return false;
    return solve(leftNode -> left, rightNode -> right) && solve(leftNode -> right, rightNode -> left);
}

bool isSymmetrical(TreeNode* root) {
    if(!root || solve(root -> left, right -> right)) return true;
    return false;
}
```

## Zig-Zag traversal

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);
    int dir = 0;
    while(!q.empty()) {
        int n = q.size(); //key point, now you know how many exact elements exist in the queue to traverse on without needing to empty the queue first
        vector<int> level;
        for(int i = 0; i < n; i++) {
            TreeNode* node = q.front();
            q.pop();
            if(node -> left) q.push(node -> left);
            if(node -> right) q.push(node -> right);
            level.push_back(node -> val);
        }
        if(dir) reverse(level.begin(), level.end());
        dir ^= 1;
        ans.push_back(level);
    }

    return ans;
}
```

- similar concept is used in [Right/Left view of BT](#rightleft-view-of-bt)

## Vertical Order Traversal

- its not hard, its just visualisation which you did on the first go, bug free
- this concept will be used in `top view` and `bottom view` of a binary tree"
  - [Top View](#top-view-of-bt)
  - [Bottom View](#bottom-view)

```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<vector<int>> ans;
    if(!root) return ans;
    //for storing nodes within same column, [0] -> all nodes of 0 column and stored as {row, node}, later we will sort this to get the min row first, this way we will be accessing row ka level wise

    map<int, vector<pair<int, int>>> mp;
    //queue structure -> {{row, col}, TreeNode}
    queue<pair<pair<int, int>, TreeNode*>> q;
    q.push({{0, 0}, root});
    while(!q.empty()) {
        int row = q.front().first.first;
        int col = q.front().first.second;
        TreeNode* node = q.front().second;
        q.pop();
        int data = node -> val;
        mp[col].push_back({row, data});
        if(node -> left) q.push({{row + 1, col - 1}, node -> left});
        if(node -> right) q.push({{row + 1, col + 1}, node -> right});
    }
    for(auto it: mp) {
        vector<pair<int, int>> temp = it.second;
        //sorting this vector to get the min row first, and min node at same col first
        sort(temp.begin(), temp.end());
        vector<int> toInsert;
        for(auto p: temp) {
            toInsert.push_back(p.second);
        }
        ans.push_back(toInsert);
    }
    return ans;
}
```

## Boundary Traversal

```cpp
void findLeft(Node *root,vector<int>&ans)
    {
        if(root==NULL){
            return;
        }
        if(root->left==NULL && root->right==NULL)
        {
            return;
        }
        ans.push_back(root->data); //add first as in order of traversal
        findLeft(root->left,ans);
        if(root->left==NULL)
        {
            findLeft(root->right,ans);
        }
        return;
    }

void findLeaf(Node *root,vector<int>&ans)
    {
        if(root==NULL)
        {
            return;
        }
        if(root->left==NULL && root->right==NULL)
        {
            ans.push_back(root->data);
            return;
        }
        findLeaf(root->left,ans);
        findLeaf(root->right,ans);
    }

void findRight(Node *root,vector<int>&ans)
    {
        if(root==NULL){
            return;
        }
        if(root->left==NULL && root->right==NULL)
        {
            return;
        }
        findRight(root->right,ans);
        if(root->right==NULL)
        {
            findRight(root->left,ans);
        }
        ans.push_back(root->data); //add at last as in reverse
        return;
}

//left + leaf + reverse right
//for left, keep going left, if no left then take right, if no left and right, simply return
// for right, keep going right, if no right then take left, it no right and left return
vector<int> boundaryTraversal(Node *root)
    {
        vector<int>ans;
        if(root==NULL)
        {
            return ans;
        }
        ans.push_back(root->data);
        findLeft(root->left,ans);
        findLeaf(root->left,ans);
        findLeaf(root->right,ans);
        findRight(root->right,ans);
        return ans;
    }
```

## Top view of BT:

- push back the first node (node of first row) of each column in the vertical order traversal in a vector
- return that vector

- to make it simpler, just add the node in the map if the column is not present in the map otherwise leave, then for each col, print that node simply. use `map of int, int`

```cpp
vector<int> topView(Node *root) {
    vector<int> ans;
    if(!root) return ans;
    //for storing nodes within same column, [0] -> all nodes of 0 column and stored as {row, node},later we will sort this to get the min row first, this way we will be accessing row ka level wise

    map<int, int> mp;
    //queue structure -> {{row, col}, TreeNode}
    queue<pair<pair<int, int>, Node*>> q;
    q.push({{0, 0}, root});
    while(!q.empty()) {
        int row = q.front().first.first;
        int col = q.front().first.second;
        Node* node = q.front().second;
        q.pop();
        int data = node -> data;
        if(!mp.count(col)) mp[col] = node -> data;
        if(node -> left) q.push({{row + 1, col - 1}, node -> left});
        if(node -> right) q.push({{row + 1, col + 1}, node -> right});
    }
    for(auto it: mp) {
        // vector<pair<int, int>> temp = it.second;
        //sorting this vector to get the min row first, and min node at same col first
        // sort(temp.begin(), temp.end());
        ans.push_back(it.second);
    }
    return ans;
    }
```

## Bottom view of BT

- now in the same line, we will be dealing with the last entered value in the map of values for that column, coz we want the last row of each vertical line

- so in line number: 255, just change it to `mp[col] = node -> data`, now we will always be updating it and access the last entered value for each col or vertical line

## Right/Left view of BT

```cpp
vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    if(!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        int n = q.size(); //same concept from zig zag, take the size of each level prior only
        vector<int> level;
        for(int i = 0; i < n; i++) {
            TreeNode* node = q.front();
            q.pop();
            if(node -> left) q.push(node -> left);
            if(node -> right) q.push(node -> right);
            level.push_back(node -> val);
        }
        if(!level.empty()) ans.push_back(level.back()); //for left take the front or first element
    }
    return ans;
}
```
