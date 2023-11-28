#include "AVLtree.h"

Node* AVLtree::search(string key) {
    return searchFrom(key, this->root);
}

Node* AVLtree::searchFrom(string key, Node* current) {
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

int AVLtree::getIndex(string key) {
    Node* found = search(key);
    if (found == nullptr) {
        return -1;
    }
    return found->data.position;
}

size_t AVLtree::getHeight(Node* current) {
    if (current == nullptr) {
        return 0;
    }
    return current->height;
}

void AVLtree::updateHeight(Node* current) {
    current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
}

int AVLtree::getBalance(Node* current) {
    return getHeight(current->right) - getHeight(current->left);
}

void AVLtree::add(string _key, int _position) {
    if (this->root == nullptr) {
        this->root = new Node(_key, _position);
    }
    else {
        addTo(this->root, new Node(_key, _position));
    }
}

Node* AVLtree::addTo(Node* current, Node* new_node) {
    if (current == nullptr) {
        return new_node;
    }

    if (new_node->data.key < current->data.key) {
        current->left = addTo(current->left, new_node);
    }
    else {
        current->right = addTo(current->right, new_node);
    }
    return saveBalance(current);
}

Node* AVLtree::saveBalance(Node* current) {
    updateHeight(current);
    if (getBalance(current) == 2) {
        if (getBalance(current->right) < 0) {
            current->right = fixRight(current->right);
        }
        return fixLeft(current);
    }
    else if (getBalance(current) == -2) {
        if (getBalance(current->left) > 0) {
            current->left = fixLeft(current->left);
        }
        return fixRight(current);
    }
    return current;
}

Node* AVLtree::fixRight(Node* current) { // Left node in Left subtree
    if (current == root) {
        this->root = current->left;
    }

    Node* center = current->left;
    current->left = center->right;
    center->right = current;

    updateHeight(current);
    updateHeight(center);
    return center;
}

Node* AVLtree::fixLeft(Node* current) { // Right node in Right subtree
    if (current == root) {
        this->root = current->right;
    }

    Node* center = current->right;
    current->right = center->left;
    center->left = current;

    updateHeight(current);
    updateHeight(center);
    return center;
}

int AVLtree::erase(string key) {
    int position = -1;
    remove(this->root, key, position);
    return position;
}

Node* AVLtree::remove(Node* current, string key, int& position) {
    if (current == nullptr) {
        return nullptr;
    }

    if (key < current->data.key) {
        current->left = remove(current->left, key, position);
    }
    else if (key > current->data.key) {
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
        return saveBalance(auxiliary);
    }
    return saveBalance(current);
}

Node* AVLtree::removeMin(Node* current) {
    if (current->left == nullptr) {
        return current->right;
    }
    current->left = removeMin(current->left);
    return saveBalance(current);
}

Node* AVLtree::getMin(Node* from) {
    if (from->left == nullptr) {
        return from;
    }
    return getMin(from->left);
}

void AVLtree::print() {
    if (this->root == nullptr) {
        cout << "The tree is empty!" << endl;
    }
    else {
        printSubTree(this->root);
    }
}

void AVLtree::printSubTree(Node* current, char from, size_t from_size, size_t level) {
    if (current != nullptr) {
        printSubTree(current->right, '/', from_size + current->data.key.size(), level + 1);

        cout << (level > 0 ? (level > 1 ? string(from_size + (level - 1) * 5, ' ') : string(from_size, ' ')) + from + "----" : "");
        cout << current->data.key;
        cout << " (b=" << getBalance(current) << ") " << endl;

        printSubTree(current->left, '\\', from_size + current->data.key.size(), level + 1);
    }
}

void AVLtree::clear(Node* current) {
    if (current->left != nullptr) {
        clear(current->left);
    }

    if (current->right != nullptr) {
        clear(current->right);
    }

    delete current;
};

AVLtree::~AVLtree() {
    if (this->root != nullptr) {
        clear(this->root);
    }
}
