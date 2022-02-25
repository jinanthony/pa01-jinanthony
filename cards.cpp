//cards.cpp
//Authors: Anthony Jin

#include "cards.h"
#include <iostream>
using namespace std;

bool Card::operator>=(Card c2) {
    string suit1;
    string suit2;
    if (suit == "h") {
        suit1 = "z";
    }
    else {
        suit1 = suit;
    }

    if (c2.suit == "h") {
        suit2 = "z";
    }
    else {
        suit2 = c2.suit;
    }

    if (suit1 > suit2) {
        return true;
    }
    else {
        if (suit1 == suit2) {
            if (value >= c2.value) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        } 
    }
}

bool Card::operator>(Card c2) {
    string suit1;
    string suit2;
    if (suit == "h") {
        suit1 = "z";
    }
    else {
        suit1 = suit;
    }

    if (c2.suit == "h") {
        suit2 = "z";
    }
    else {
        suit2 = c2.suit;
    }

    if (suit1 > suit2) {
        return true;
    }
    else {
        if (suit1 == suit2) {
            if (value > c2.value) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        } 
    }
}

bool Card::operator==(Card c2) {
    if (suit == c2.suit && value == c2.value) {
        return true;
    }
    return false;
}

BST::BST():root(nullptr) {}

void BST::clear(Node* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

BST::~BST() {
    clear(root);
}

void BST::insert(Card car) {
    Node* insert = new Node(car);
    if (!root) {
        root = insert;
        return;
    }
    Node* n = root;
    while (n) {
        if (n->c >= car) {
            if (n->left == nullptr) {
                n->left = insert;
                insert->parent = n;
                return;
            }
            else {
                n = n->left;
            }
        }
        else  {
            if (n->right == nullptr) {
                n->right = insert;
                insert->parent = n;
                return;
            }
            else {
                n = n->right;
            }
        }
    }
}

void BST::printInOrderNode(Node* n) {
    if (!n) {
        return;
    }
    printInOrderNode(n->left);
    n->c.print();
    printInOrderNode(n->right); 
}

void BST::printInOrder() {
    printInOrderNode(root);
}

BST::Node* BST::findNode(Card car, Node* n) {
    if (!n) {
        return nullptr;
    }
    if (n->c == car) {
        return n;
    }
    else if (n->c >= car) {
        return findNode(car, n->left);
    }
    else {
        return findNode(car, n->right);
    }
}

bool BST::ifCardFound(Card car) {
    if (findNode(car, root) == nullptr) {
        return false;
    }
    return true;
}

// pred and succ may have some edge case errors
BST::Node* BST::predecessorNode(Card car) {
    Node* n = findNode(car, root);
    if (!n) {
        return nullptr;
    }
    if (n->left) {
        n = n->left;
        while (n->right) {
            n = n->right;
        }
        return n;
    }
    else {
        while (n->parent && n->c >= car) {
            n = n->parent;
        }
        if (n == root && n->c >= car) {
            return nullptr;
        }
        return n;
    }
}

Card BST::predecessor(Card car) {
    Node* n = predecessorNode(car);
    if (!n) {
        return Card();
    }
    else {
        return n->c;
    }
}

BST::Node* BST::successorNode(Card car) {
    Node* n = findNode(car, root);
    if (n->right) {
        n = n->right;
        while (n->left) {
            n = n->left;
        }
        return n;
    }
    else {
        while (n->parent && !(n->c > car)) {
            n = n->parent;
        }
        if (n == root && !(n->c > car)) {
            return nullptr;
        }
        return n;
    }
}

Card BST::successor(Card car) {
    Node* n = successorNode(car);
    if (!n) {
        return Card();
    }
    else {
        return n->c;
    }
}

void BST::remove(Card car) {
    Node* n = findNode(car, root);
    if (n == nullptr) {
        return;
    }
    if (n->left == nullptr && n->right == nullptr) {
        if (n->parent) {
            if (n->parent->left == n) {
                n->parent->left = nullptr;
                delete n;
            }
            else {
                n->parent->right = nullptr;
                delete n;
            }
        }
        else {
            delete n;
            root = nullptr;
        }
        return;
    }
    else if (n->left && !n->right) {
        if (!n->parent) {
            root = n->left;
            root->parent = nullptr;
            delete n;
        }
        else if (n->parent->left == n) {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            delete n;
        }
        else {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
        }
        return;
    }
    else if (n->right && !n->left) {
        if (!n->parent) {
            root = n->right;
            root->parent = nullptr;
            delete n;
        }
        else if (n->parent->left == n) {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            delete n;
        }
        else {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
        }
        return;
    }
    else {
        Node* p = successorNode(car);
        n->c = p->c;
        if (!p->left && !p->right) {
            if (p->parent->right == p) {
                p->parent->right = nullptr;
            }
            else {
                p->parent->left = nullptr;
            }
            delete p;
        }
        else if (!p->left && p->right) {
            if (p->parent->right == p) {
                p->parent->right = p->right;
                p->right->parent = p->parent;
            }
            else {
                p->parent->left = p->right;
                p->right->parent = p->parent;
            }
            delete p;
        }
        return;
    }
}

Card BST::gameTurnMin(BST& hand2) {
    Node* n = root;
    Card car;
    Card empty;
    if (!n)
        return empty;
    while (n->left) {
        n = n->left;
    }
    while (n) {
        car = n->c;
        if (hand2.ifCardFound(car)) {
            hand2.remove(car);
            this->remove(car);
            return car;
        }
        n = this->successorNode(car);
    }
    return empty;
}

Card BST::gameTurnMax(BST& hand2) {
    Node* n = root;
    Card car;
    Card empty;
    if (!n) 
        return empty;
    while (n->right) {
        n = n->right;
    }
    while (n) {
        car = n->c;
        if (hand2.ifCardFound(car)) {
            hand2.remove(car);
            this->remove(car);
            return car;
        }
        n = this->predecessorNode(car);
    }
    return empty;
}
