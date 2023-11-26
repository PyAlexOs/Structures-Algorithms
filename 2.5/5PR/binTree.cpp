#include "binTree.h"

Node* binTree::search(string key) {
    return searchFrom(key, this->root);
}

Node* binTree::searchFrom(string key, Node* current) {
    if (current == nullptr || key == current->data.key) {
        return current;
    }
    else {
        if (key < current->data.key) {
            return searchFrom(key, current->left);
        }
        else {
            return searchFrom(key, current->right);
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

bool binTree::add(string _key, int _position) {
    if (this->root == nullptr) {
        this->root = new Node(_key, _position, nullptr);
        return true;
    }
    else {
        return addTo(this->root, new Node(_key, _position, nullptr));
    }
}

bool binTree::addTo(Node* current, Node* new_node) {
    if (new_node->data.key < current->data.key) {
        if (current->left == nullptr) {
            current->left = new_node;
            new_node->parent = current;
            return true;
        }
        else {
            return addTo(current->left, new_node);
        }
    }
    else if (new_node->data.key > current->data.key) {
        if (current->right == nullptr) {
            current->right = new_node;
            new_node->parent = current;
            return true;
        }
        else {
            return addTo(current->right, new_node);
        }
    }
    else {
        return false;
    }
}

int binTree::erase(string key) {
    Node* found = search(key);
    if (found == nullptr) {
        return -1;
    }
    int position = found->data.position;

    if (found->left == nullptr && found->right == nullptr) {
        if (found->parent != nullptr) {
            found->parent->left == found ? found->parent->left = nullptr : found->parent->right = nullptr;
        }
        else {
            this->root = nullptr;
        }
        delete found;
    }

    else if (found->left == nullptr) {
        if (found->parent != nullptr) {
            found->parent->left == found ? found->parent->left = found->right : found->parent->right = found->right;
            found->right->parent = found->parent;
        }
        else {
            this->root = found->right;
            root->parent = nullptr;
        }
        delete found;
    }

    else if (found->right == nullptr) {
        if (found->parent != nullptr) {
            found->parent->left == found ? found->parent->left = found->left : found->parent->right = found->left;
            found->left->parent = found->parent;
        }
        else {
            this->root = found->left;
            root->parent = nullptr;
        }
        delete found;
    }

    else {
        Node* leftMax = getMax(found->left);
        Node* rightMin = getMin(found->right);

        if (found->isNeightbor(leftMax, rightMin)) {
            record copy = leftMax->data;
            erase(leftMax->data.key);
            found->data = copy;
        }
        else {
            record copy = rightMin->data;
            erase(rightMin->data.key);
            found->data = copy;
        }
    }
    return position;
}

Node* binTree::getMax(Node* from) {
    if (from->right == nullptr) {
        return from;
    }
    else {
        return getMax(from->right);
    }
}

Node* binTree::getMin(Node* from) {
    if (from->left == nullptr) {
        return from;
    }
    else {
        return getMin(from->left);
    }
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
    clear(this->root);
}