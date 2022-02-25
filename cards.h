//cards.h
//Author: Anthony Jin

#ifndef CARDS_H
#define CARDS_H

#include <iostream>
using namespace std;

class Card {
    private: 
        string suit;
        int value;
    public:
        Card(string s = "none", int v = 0): suit(s), value(v) {}
        string getSuit() const {return suit;}
        int getValue() const {return value;}
        void setSuit(string s) {suit = s;}
        void setValue(int v) {value = v;}
        void print() {
            cout << suit << " ";
            if (value == 1) cout << "a" << endl;
            else if (value == 11) cout << "j" << endl;
            else if (value == 12) cout << "q" << endl;
            else if (value == 13) cout << "k" << endl;
            else cout << value << endl;
        }
        bool operator >=(Card c2);
        bool operator >(Card c2);
        bool operator==(Card c2);
};

class BST{
    private:
        struct Node {
            Card c;
            Node*left;
            Node* right;
            Node* parent;

            Node() {
                c = Card();
                left = nullptr;
                right = nullptr;
                parent = nullptr;
            }

            Node (Card car): c(car), left(nullptr), right(nullptr), parent(nullptr){}
        };
        
        Node* root;

        void clear(Node*n);
        void printInOrderNode(Node*n);
        void printPreOrderNode(Node*n);
        Node* findNode(Card car, Node* n);
        Node* predecessorNode(Card car);
        Node*successorNode(Card car);
    
    public:
        BST();
        ~BST();

        void remove(Card car);
        void insert(Card car);
        Card predecessor(Card car);
        Card successor(Card car);
        void printInOrder();
        void printPreOrder();
        bool ifCardFound(Card car);
        Card gameTurnMin(BST& hand2);
        Card gameTurnMax(BST& hand2);
};

#endif
        
            
