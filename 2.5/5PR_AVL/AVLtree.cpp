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

bool AVLtree::add(string _key, int _position) {
    if (this->root == nullptr) {
        this->root = new Node(_key, _position, nullptr);
        return true;
    }
    else {
        Node* current = addTo(this->root, new Node(_key, _position, nullptr));
        if (current != nullptr) {
            updateBalance(current);
            return true;
        }
        return false;
    }
}

Node* AVLtree::addTo(Node* current, Node* new_node) {
    if (new_node->data.key < current->data.key) {
        if (current->left == nullptr) {
            current->left = new_node;
            new_node->parent = current;
            return new_node;
        }
        else {
            return addTo(current->left, new_node);
        }
    }
    else if (new_node->data.key > current->data.key) {
        if (current->right == nullptr) {
            current->right = new_node;
            new_node->parent = current;
            return new_node;
        }
        else {
            return addTo(current->right, new_node);
        }
    }
    else {
        return nullptr;
    }
}

void AVLtree::updateBalance(Node* current) {
    if (abs(current->balance) > 1) {
        saveBalance(current);
        return;
    }

    if (current->parent != nullptr){
        current->parent->left == current ? current->parent->balance-- : current->parent->balance++;

        if (current->parent->balance != 0) {
            updateBalance(current->parent);
        }
    }
}

void AVLtree::saveBalance(Node* current) {
    if (current->balance == 2) {
        if (current->right->balance > 0) {
            fixRR(current);
        }
        else {
            
        }
    }
    else {
        if (current->left->balance < 0) {
            fixLL(current);
        }
        else {

        }
    }
}

void AVLtree::fixRR(Node* current) {
    if (current->parent == nullptr) {
        this->root = current->right;
    }

    Node* head = current->parent;
    current->parent = current->right;
    current->right = current->right->left;
    current->right->parent = current;
    current->parent->left = current;
    current->parent->parent = head;
}

void AVLtree::fixLL(Node* current) {
    if (current->parent == nullptr) {
        this->root = current->left;
    }

    Node* head = current->parent;
    current->parent = current->left;
    current->left = current->left->right;
    current->left->parent = current;
    current->parent->right = current;
    current->parent->parent = head;
}

void AVLtree::fixRL(Node* current) {

}

void AVLtree::fixLR(Node* current) {

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

void AVLtree::print() {
    if (this->root == nullptr) {
        cout << "The tree is empty!" << endl;
    }
    printSubTree(this->root);
}

void AVLtree::printSubTree(Node* current, char from, size_t from_size, size_t level) {
    if (current != nullptr) {
        printSubTree(current->right, '/', from_size + current->data.key.size(), level + 1);

        cout << (level > 0 ? (level > 1 ? string(from_size + (level - 1) * 5, ' ') : string(from_size, ' ')) + from + "----" : "");
        cout << current->data.key;
        cout << " (" << current->balance << ") " << (current->parent ? current->parent->data.key + " " : "~") << endl;

        printSubTree(current->left, '\\', from_size + current->data.key.size(), level + 1);
    }
}