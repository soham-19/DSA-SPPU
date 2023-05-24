Node* AVL::insert(Node* root, string key, string mean) {
    if (root == NULL) {
        root = new Node(key, mean);
        return root;
    }
    if (key < root->keyword) {
        root->left = insert(root->left, key, mean);
        if (BF(root) == 2) {
            if (key < root->left->keyword) {
                root = LL(root);
            } else {
                root = LR(root);
            }
        }
    } else if (key > root->keyword) {
        root->right = insert(root->right, key, mean);
        if (BF(root) == -2) {
            if (key > root->right->keyword) {
                root = RR(root);
            } else {
                root = RL(root);
            }
        }
    }
    root->ht = height(root);
    return root;
}
