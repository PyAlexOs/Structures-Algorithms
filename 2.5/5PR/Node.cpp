#include "Node.h"

bool Node::isNeightbor(Node* first, Node* second) {
    string s1 = first->data.key, s2 = second->data.key, self = this->data.key;
    size_t length = min({s1.size(), s2.size(), self.size()}), i = 0;
    while (i < length) {
        if (abs(abs(self[i]) - abs(s1[i])) < abs(abs(self[i]) - abs(s2[i]))) {
            return true;
        }
        else if (abs(abs(self[i]) - abs(s1[i])) > abs(abs(self[i]) - abs(s2[i]))) {
            return false;
        }
        ++i;
    }

    return true;
}