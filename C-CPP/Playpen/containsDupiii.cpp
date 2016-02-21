#include <iostream>
#include <vector>

using namespace std;

class Solution {

    struct TreeNode {
        int val;
        int index;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x, int i) : val(x), index(i), left(NULL), right(NULL) {}
    };
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        bool dup = false;
        int n = nums.size();
        if (n == 0) return false;
        TreeNode *root = new TreeNode(nums[0], 0);
        for (int i = 1; i < n; i++) {
            if (dup) return true;
            cout << "root val = " << root->val << endl;
            insert(root, nums[i], i, k, t, dup);
        }
        return dup;
    }
    
private:
    TreeNode* insert(TreeNode *root, int val, int index, int k, int t, bool & dup) {
        if (root == nullptr) return new TreeNode(val, index);
        int diff = val > root->val ? val - root->val : root->val - val;
        cout << "index diff == " << index - root->index << " and diff = " << diff << endl;
        if (index - root->index <= k && diff >= 0 && diff <= t) { // diff >=0 to check overflow case
            cout << "dup is true" << endl;
            dup = true;
        } else if (val < root->val) root->left = insert(root->left, val, index, k, t, dup);
        else if (val > root->val) root->right = insert(root->right, val, index, k, t, dup);
        else root->index = index;
        return root;
    }
};

int main() {
    vector<int> nums = {10, 100, 11, 9};
    Solution sol;
    cout << sol.containsNearbyAlmostDuplicate(nums, 1, 2) << endl;
}