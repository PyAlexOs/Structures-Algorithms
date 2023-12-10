#include "binTree.h"

Node* binTree::search(string key) {
    return searchFrom(this->root, key);
}

Node* binTree::searchFrom(Node* current, string key) {
    if (current == nullptr || key == current->data.key) {
        return current;
    }
    else {
        if (key < current->data.key) {
            return searchFrom(current->left, key);
        }
        else {
            return searchFrom(current->right, key);
        }
    }
}

int binTree::getIndex(string key) {
    Node* found = search(key);
    if (found == nullptr) {
        return -1;
    }
    return found->data.position;
}

void binTree::add(string _key, int _position) {
    this->root = addTo(this->root, new Node(_key, _position));
}

Node* binTree::addTo(Node* current, Node* new_node) {
    if (current == nullptr) {
        return new_node;
    }

    if (new_node->data.key < current->data.key) {
        current->left = addTo(current->left, new_node);
    }
    else {
        current->right = addTo(current->right, new_node);
    }
    return current;
}

int binTree::erase(string key) {
    int position = -1;
    this->root = remove(this->root, key, position);
    return position;
}

Node* binTree::remove(Node* current, string key, int& position) {
    if (current == nullptr) {
        return nullptr;
    }

    if (key < current->data.key) {
        current->left = remove(current->left, key, position);
    }
    else if (key > current->data.key){
        current->right = remove(current->right, key, position);
    }
    else {
        Node* right = current->right, * left = current->left;
        position = current->data.position;
        delete current;

        if (right == nullptr) {
            return left;
        }

        Node* auxiliary = getMin(right);
        auxiliary->right = removeMin(right);
        auxiliary->left = left;
        return auxiliary;
    }
    return current;
}

Node* binTree::removeMin(Node* current) {
    if (current->left == nullptr) {
        return current->right;
    }
    current->left = removeMin(current->left);
    return current;
}

Node* binTree::getMin(Node* from) {
    if (from->left == nullptr) {
        return from;
    }
    return getMin(from->left);
}

void binTree::print() {
    if (this->root == nullptr) {
        cout << "The tree is empty!" << endl;
    }
    printSubTree(this->root);
}

void binTree::printSubTree(Node* current, char from, size_t from_size, size_t level) {
    if (current != nullptr) {
        printSubTree(current->right, '/', from_size + current->data.key.size(), level + 1);

        cout << (level > 0 ? (level > 1 ? string(from_size + (level - 1) * 5, ' ') : string(from_size, ' ')) + from + "----" : "");
        cout << current->data.key << endl;

        printSubTree(current->left, '\\', from_size + current->data.key.size(), level + 1);
    }
}

void binTree::clear(Node* current) {
    if (current->left != nullptr) {
        clear(current->left);
    }

    if (current->right != nullptr) {
        clear(current->right);
    }

    delete current;
};

binTree::~binTree() {
    if (this->root != nullptr) {
        clear(this->root);
    }
}
