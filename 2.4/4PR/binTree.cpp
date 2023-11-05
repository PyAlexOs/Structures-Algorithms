#include "binTree.h"

bool binTree::addNode(Node* new_node) {
    if (root == nullptr) {
        root = new_node;
        return true;
    }

    bool status = true;
    Node* current = root;

    while (status && current->left != new_node && current->right != new_node) {
        if (new_node->value < current->value) {
            if (current->left != nullptr) {
                current = current->left;
            }
            else {
                current->left = new_node;
            }
        }
        else if (new_node->value > current->value) {
            if (current->right != nullptr) {
                current = current->right;
            }
            else {
                current->right = new_node;
            }
        }
        else {
            status = false;
        }
    }
    return status;
}

void binTree::print(Node* current, char from, size_t level) {
    if (current != nullptr) {
        print(current->right, '/', level + 1);

        cout << (level > 0 ? (level > 1 ? string((level - 1) * 6, ' ') : "") + " " + from + "----" : "");
        cout << current->value << endl;

        print(current->left, '\\', level + 1);
    }
}

double binTree::mean() {
    size_t count = 0, sum = 0;
    queue <Node*> tree;
    tree.push(root);

    while (!tree.empty()) {
        Node* current = tree.front();
        tree.pop();

        if (current != nullptr) {
            tree.push(current->left);
            tree.push(current->right);

            count++;
            sum += current->value;
        }
    }
    return (double)sum / ((count != 0) ? count : 1);
}

size_t binTree::count(Node* current) {
    if (current == nullptr) {
        return 0;
    }
    return 1 + count(current->left) + count(current->right);
}

void binTree::deleteLeft() {
    if (root == nullptr) {
        return;
    }

    Node* current = root, * previous = root;
    while (current->left != nullptr || current->right != nullptr) {
        previous = current;
        if (current->left != nullptr) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (previous->left != nullptr) {
        previous->left = nullptr;
    }
    else {
        previous->right = nullptr;
    }
    delete current;
}

int binTree::getLevel(Node* current, int value, int level) {
    if (current == nullptr) {
        return -1;
    }

    if (current->value == value) {
        return ++level;
    }

    int left = getLevel(current->left, value, level + 1);
    if (left != -1) {
        return left;
    }
    return getLevel(current->right, value, level + 1);
}
