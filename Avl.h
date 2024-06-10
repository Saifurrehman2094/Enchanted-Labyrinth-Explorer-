#pragma once
#include"Libraries.h"
using namespace std;
template<class T>
class Item {
public:
    T value;
    string name;
    Item<T>* left;
    Item<T>* right;
    int height;
    Item(T val) : value(val), left(nullptr), right(nullptr), height(1),name("") {}
    Item(T val,string s) : value(val), left(nullptr), right(nullptr), height(1), name(s) {}
};
template<class T>
class BalancedTree {
public:
    Item<T>* root;

    BalancedTree() {
        root = nullptr;
    }

    int Height(Item<T>* P) {
        if (P == nullptr)
            return -1;
        else
            return P->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Item<T>* leftRotate(Item<T>* k1) {
        Item<T>* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(Height(k1->left), Height(k1->right)) + 1;
        k2->height = max(Height(k2->right), k1->height) + 1;
        return k2;
    }

    Item<T>* rightRotate(Item<T>* k1) {
        Item<T>* k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;
        k1->height = max(Height(k1->left), Height(k1->right)) + 1;
        k2->height = max(Height(k2->right), k1->height) + 1;
        return k2;
    }

    Item<T>* leftRight(Item<T>* k1) {
        k1->right = rightRotate(k1->right);
        return leftRotate(k1);
    }

    Item<T>* rightLeft(Item<T>* k1) {
        k1->left = leftRotate(k1->left);
        return rightRotate(k1);
    }

    int balanceFactor(Item<T>* node) {
        return (Height(node->left) - Height(node->right));
    }

    void inorder(Item<T>* node) {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << "Value: " << node->value << " Height: " << node->height << " Balance Factor: " << balanceFactor(node) << std::endl;
            inorder(node->right);
        }
    }

    Item<T>* insertItem(T val, Item<T>* node) {
        if (node == nullptr) {
            node = new Item<T>(val);
        }
        else {
            if (val < node->value) {
                node->left = insertItem(val, node->left);
                if (Height(node->left) - Height(node->right) == 2)
                    if (val < node->left->value)
                        node = rightRotate(node); // RR rotation
                    else
                        node = rightLeft(node); // RL rotation
            }
            else if (val > node->value) {
                node->right = insertItem(val, node->right);
                if (Height(node->right) - Height(node->left) == 2)
                    if (val > node->right->value)
                        node = leftRotate(node); // LL rotation
                    else
                        node = leftRight(node); // LR rotation
            }
        }
        node->height = max(Height(node->left), Height(node->right)) + 1;
        return node;
    }
    //Item<T>* deleteItem(T val, const std::string& name, Item<T>* node) {
    //    if (node == nullptr)
    //        return node;

    //    if (val < node->value)
    //        node->left = deleteItem(val, name, node->left);
    //    else if (val > node->value)
    //        node->right = deleteItem(val, name, node->right);
    //    else {
    //        if (node->name == name) { // Check if the names match
    //            // Names match, delete this node
    //            if (node->left == nullptr || node->right == nullptr) {
    //                Item<T>* temp = node->left ? node->left : node->right;
    //                if (temp == nullptr) {
    //                    temp = node;
    //                    node = nullptr;
    //                }
    //                else
    //                    *node = *temp;
    //                delete temp;
    //            }
    //            else {
    //                Item<T>* temp = minValueNode(node->right);
    //                node->value = temp->value;
    //                node->right = deleteItem(temp->value, temp->name, node->right);
    //            }
    //        }
    //        else {
    //            // Names don't match, continue searching
    //            if (val < node->value)
    //                node->left = deleteItem(val, name, node->left);
    //            else
    //                node->right = deleteItem(val, name, node->right);
    //        }
    //    }

    //    if (node == nullptr)
    //        return node;
    //    node->height = max(Height(node->left), Height(node->right)) + 1;
    //    int balance = balanceFactor(node);

    //    // Perform rotations if necessary
    //    if (balance > 1 && balanceFactor(node->left) >= 0)
    //        return rightRotate(node); // LL rotation
    //    if (balance > 1 && balanceFactor(node->left) < 0) {
    //        node->left = leftRotate(node->left);
    //        return rightRotate(node); // LR rotation
    //    }
    //    if (balance < -1 && balanceFactor(node->right) <= 0)
    //        return leftRotate(node); // RR rotation
    //    if (balance < -1 && balanceFactor(node->right) > 0) {
    //        node->right = rightRotate(node->right);
    //        return leftRotate(node); // RL rotation
    //    }

    //    return node;
    //}

    Item<T>* deleteItem(T val, Item<T>* &node) {
        if (node == nullptr)
            return node;

        if (val < node->value)
            node->left = deleteItem(val, node->left);
        else if (val > node->value)
            node->right = deleteItem(val, node->right);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Item<T>* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {
                Item<T>* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = deleteItem(temp->value, node->right);
            }
        }

        if (node == nullptr)
            return node;
        node->height = max(Height(node->left), Height(node->right)) + 1;
        int balance = balanceFactor(node);

        // Perform rotations if necessary
        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node); // LL rotation
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node); // LR rotation
        }
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node); // RR rotation
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node); // RL rotation
        }

        return node;
    }

    Item<T>* minValueNode(Item<T>* node) {
        Item<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    bool searchItem(T value) {
        Item<T>* current = root;
        while (current != nullptr) {
            if (value>current->value) {
                current = current->right;
            }
            else if (value < current->value) {
                current = current->left;
            }
            else {
                return true;
            }
        }
        return false; // Return nullptr if not found
    }
};
