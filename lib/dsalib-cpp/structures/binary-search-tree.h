#pragma once

#include "array-list.h"
#include "binary-tree.h"
#include "../util/util.h"

template <typename Key, typename Node=BinaryTreeNode<Key>>
class BinarySearchTree : public BinaryTree<Key, Node> {
protected:
    virtual void Insert(Node* inode) {
        auto parent = this->nil;
        auto curr = this->root;

        while (curr != this->nil) {
            parent = curr;

            if (inode->key < curr->key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }

        inode->parent = parent;

        if (parent == this->nil) {
            this->root = inode;
        }
        else {
            if (inode->key < parent->key) {
                parent->left = inode;
            }
            else {
                parent->right = inode;
            }
        }
    }

    virtual Node* Remove(Node* rnode) {
        if (rnode == this->nil) return this->nil;

        Node* rnode_parent = rnode->parent;

        // Case 1: rnode has only one child
        if (rnode->left == this->nil || rnode->right == this->nil) {
            if (rnode->left != this->nil) {
                if (rnode_parent == this->nil) {
                    this->root = rnode->left;
                }
                else if (rnode == rnode_parent->left) {
                    rnode_parent->left = rnode->left;
                }
                else {
                    rnode_parent->right = rnode->left;
                }

                rnode->left->parent = rnode_parent;
            }
            else {
                if (rnode->parent == this->nil) {
                    this->root = rnode->right;
                }
                else if (rnode == rnode_parent->left) {
                    rnode_parent->left = rnode->right;
                }
                else {
                    rnode_parent->right = rnode->right;
                }

                rnode->right->parent = rnode_parent;
            }

            delete rnode;
            return rnode_parent;
        }

        // Case 2: rnode has both children
        Node* next_larger = this->MinNode(rnode->right);
        Node* next_larger_parent = next_larger->parent;

        if (next_larger_parent != rnode) {
            next_larger_parent->left = next_larger->right;
            next_larger->right->parent = next_larger_parent;
            util::swap(rnode->key, next_larger->key);

            delete next_larger;
            return next_larger_parent;
        }

        util::swap(rnode->key, next_larger->key);
        rnode->right = next_larger->right;
        next_larger->right->parent = rnode;

        delete next_larger;
        return rnode;
    }

    Node* Search(Key key) const {
        Node* curr = this->root;

        while (curr != this->nil && curr->key != key) {
            if (key < curr->key) {
                curr = curr->left;
            }
            else {
               curr = curr->right;
            }
        }

        return curr;
    }

    Node* MinNode(Node* root) const {
        Node* curr = root;

        while (curr->left != this->nil) {
            curr = curr->left;
        }

        return curr;
    }

    Node* MaxNode(Node* root) const {
        Node* curr = root;

        while (curr->right != this->nil) {
            curr = curr->right;
        }

        return curr;
    }

public:
    virtual void Push(Key key) {
        auto inode = new Node(key);
        inode->left = this->nil;
        inode->right = this->nil;
        inode->parent = this->nil;
        this->Insert(inode);
    }

    virtual void Pop(Key key) {
        this->Remove(this->Search(key));
    }

    bool Has(Key key) const {
        return this->Search(key) != this->nil;
    }

    Key Get(Key key) const {
        return this->Search(key)->key;
    }

    Key Min() const {
        return MinNode(this->root)->key;
    }

    Key Max() const {
        return MaxNode(this->root)->key;
    }

    void InOrderGetKey(Node* node, ArrayList<Key>& list) {
        if (node == this->nil) return;
        InOrderGetKey(node->left, list);
        list.PushBack(node->key);
        InOrderGetKey(node->right, list);
    }

    ArrayList<Key> GetArrayList() {
        ArrayList<Key> list;
        InOrderGetKey(this->root, list);
        return list;
    }
};