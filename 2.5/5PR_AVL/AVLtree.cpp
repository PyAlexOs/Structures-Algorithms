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
    return current != nullptr ? current->height : 0;
}

void AVLtree::updateHeight(Node* current) {
    current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
}

int AVLtree::getBalance(Node* current) {
    return getHeight(current->right) - getHeight(current->left);
}

void AVLtree::add(string _key, int _position) {
    if (this->root == nullptr) {
        this->root = new Node(_key, _position, nullptr);
    }
    else {
        addTo(this->root, new Node(_key, _position, nullptr));
    }
}

Node* AVLtree::addTo(Node* current, Node* new_node) {
    if (current == nullptr) {
        return new_node;
    }

    if (new_node->data.key < current->data.key) {
        current->left = addTo(current->left, new_node);
        current->left->parent = current;
    }
    else {
        current->right = addTo(current->right, new_node);
        current->right->parent = current;
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
    if (current->parent == nullptr) {
        this->root = current->left;
    }

    Node* center = current->left;
    center->parent = current->parent;

    current->left = center->right;
    if (current->left != nullptr) {
        current->left->parent = current;
    }

    center->right = current;
    center->right->parent = center;

    updateHeight(current);
    updateHeight(center);
    return center;
}

Node* AVLtree::fixLeft(Node* current) { // Right node in Right subtree
    if (current->parent == nullptr) {
        this->root = current->right;
    }

    Node* center = current->right;
    center->parent = current->parent;

    current->right = center->left;
    if (current->right != nullptr) {
        current->right->parent = current;
    }

    center->left = current;
    center->left->parent = center;

    updateHeight(current);
    updateHeight(center);
    return center;
}

int AVLtree::erase(string key) {
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
}

Node* remove(Node* rubbish) {
    return nullptr;
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
        cout << " (b=" << getBalance(current) << ") " << (current->parent ? "p='" + current->parent->data.key + "'" : "root") << endl;

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
    clear(this->root);
}