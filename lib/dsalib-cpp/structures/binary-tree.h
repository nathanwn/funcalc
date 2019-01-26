#pragma once

#include <iostream>

template <typename Key>
struct BinaryTreeNode {
    Key key;
    BinaryTreeNode* parent;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode() = default;

    static BinaryTreeNode* CreateNil() {
        auto nil = new BinaryTreeNode();
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
    }

    explicit BinaryTreeNode(Key key) : key(key) {}
};

template <typename Key, typename Node=BinaryTreeNode<Key>>
class BinaryTree {
protected:
    Node* root;
    Node* nil;

    BinaryTree() {
        nil = Node::CreateNil();
        root = nil;
    }

    virtual void Insert(Node*) = 0;
    virtual Node* Remove(Node*) = 0;

    virtual void Push(Key key) = 0;
    virtual void Pop(Key key) = 0;

    void GetNodeString(Node* node, std::string& res, const std::string& pad) const {
        if (node == nil) return;
        res += pad + ' ' + std::to_string(node->key) + ' ';
        if (node->left == nil && node->right == nil) {
            return;
        }
        res += "( ";
        GetNodeString(node->left, res, "L");
        GetNodeString(node->right, res, "R");
        res += ") ";
    }

    std::string GetString() const {
        std::string res;
        GetNodeString(root, res, "");
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree) {
        os << "Binary Tree[";
        os << tree.GetString();
        os << " ]";
        return os;
    }

    void Destroy(Node* node) {
        if (node == nil) return;
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }

    virtual ~BinaryTree() {
        Destroy(root);
        delete nil;
    }
};
