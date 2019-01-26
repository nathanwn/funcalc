#pragma once

#include "binary-search-tree.h"

template <typename Key>
struct AVLTreeNode {
    Key key;
    AVLTreeNode* parent;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode() = default;

    AVLTreeNode(Key key) : key(key) {}

    static AVLTreeNode* CreateNil() {
        auto nil = new AVLTreeNode();
        nil->parent = nil;
        nil->left = nil;
        nil->right = nil;
        nil->height = -1;
    }

    void UpdateHeight() {
        height = util::max(left->height, right->height) + 1;
    }
};

template <typename Key, typename Node=AVLTreeNode<Key>>
class AVLTree : public BinarySearchTree<Key, Node> {
protected:
    /**
     * @function rotateLeft: rotate left node x
     *     p -  x                     p -  y
     *        /   \                      /   \
     *      alpha   y        =>         x    gamma
     *            /   \               /    \
     *         beta  gamma         alpha  beta
     * @param x
    **/
    void LeftRotate(Node* x) {
        Node* y = x->right;
        Node* p = x->parent;
        Node* beta = y->left;

        x->right = beta;

        if (beta != this->nil) {
            beta->parent = x;
        }

        y->parent = p;

        if (p == this->nil) {
            this->root = y;
        }
        else if (x == p->left) {
            p->left = y;
        }
        else {
            p->right = y;
        }

        x->parent = y;
        y->left = x;

        x->UpdateHeight();
        y->UpdateHeight();
    }

    /**
     * @function rotateRight: rotate right node y
     *       p -   y              p -  x
     *          /    \               /   \
     *         x    gamma   =>   alpha     y
     *       /   \                       /   \
     *    alpha  beta                  beta  gamma
     * @param y
    **/
    void RightRotate(Node* y) {
        Node* x = y->left;
        Node* p = y->parent;
        Node* beta = x->right;

        y->left = beta;

        if (beta != this->nil) {
            beta->parent = y;
        }

        x->parent = p;

        if (p == this->nil) {
            this->root = x;
        }
        else if (y == p->left) {
            p->left = x;
        }
        else {
            p->right = x;
        }

        y->parent = x;
        x->right = y;

        x->UpdateHeight();
        y->UpdateHeight();
    }

    /**
     * @function Rebalance: rebalance a node and then rebalance upward recursively
     * @param node
    **/
    void Rebalance(Node* node) {
        while (node != this->nil) {
            node->UpdateHeight();

            if (node->left->height >= node->right->height + 2) {
            // LH
                if (node->left->left->height >= node->left->right->height) {
                // LH of LH: 1 rotation
                    RightRotate(node);
                }
                else {
                // RH of LH: 2 rotations
                    LeftRotate(node->left);
                    RightRotate(node);
                }
            }
            else if (node->right->height >= node->left->height + 2) {
            // RH
                if (node->right->right->height >= node->right->left->height) {
                // RH of RH: 1 rotation
                    LeftRotate(node);
                }
                else {
                // LH of RH: 2 rotations
                    RightRotate(node->right);
                    LeftRotate(node);
                }
            }

            node = node->parent;
        }
    }

    void Insert(Node* inode) {
        BinarySearchTree<Key, Node>::Insert(inode);
        this->Rebalance(inode);
    }

    Node* Remove(Node* rnode) {
        Node* rnode_parent = BinarySearchTree<Key, Node>::Remove(rnode);
        this->Rebalance(rnode_parent);
        return this->nil; // this return value is unused
    }
};
