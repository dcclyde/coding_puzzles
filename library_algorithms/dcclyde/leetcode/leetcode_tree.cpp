struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
};

TreeNode* parse_tree(string s) {
    assert(s.front() == '[');
    assert(s.back() == ']');

    V<string> dat(1);
    for(int k = 1; k < s.size()-1; ++k) {
        if (s[k] == ',') {dat.emplace_back();}
        else {dat.back().push_back(s[k]);}
    }

    if (dat[0] == "null") {return nullptr;}

    TreeNode* root = new TreeNode(stoi(dat[0]));
    queue<TreeNode*> todo;
    todo.emplace(root);

    for(int k = 1; k < dat.size(); k += 2) {
        // fill in children for the current node.
        TreeNode* curr = todo.front();
        todo.pop();

        if (dat[k] != "null") {
            curr->left = new TreeNode(stoi(dat[k]));
            todo.push(curr->left);
        }
        if (k+1 < dat.size() && dat[k+1] != "null") {
            curr->right = new TreeNode(stoi(dat[k+1]));
            todo.push(curr->right);
        }
    }
    return root;
}

string serialize_tree(TreeNode* root) {
    string out = "[";
    queue<TreeNode*> todo;
    todo.push(root);
    while (!todo.empty()) {
        TreeNode* curr = todo.front(); todo.pop();
        if (out.size() > 1) {out.push_back(',');}
        if (curr == nullptr) {
            out += "null";
        } else {
            out += to_string(curr->val);
            todo.push(curr->left);
            todo.push(curr->right);
        }
    }
    while (out.size() >= 6 && out.substr(out.size()-5, 5) == ",null") {
        out.resize(out.size() - 5);
    }
    if (out == "[null") {return "[]";}
    out.push_back(']');
    return out;
}
