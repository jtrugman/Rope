#include <iostream>
using namespace std;
class Rope {   // Rope data structure
private:

    class Node {
    public:
        char *data;
        int weight;
        Node *left, *right;
        Node(char *data) : data(data), weight(sizeof(data)/sizeof(char)), left(nullptr), right(nullptr){}
        Node() : data(nullptr), weight(0), left(nullptr), right(nullptr){}
    };

    Node* root;

public:
    Rope() : root(new Node()) {}

    // Rope(const char str[]) {}
    // Rope(const char str[], int len) {}

    void makeEmpty () {
        root = new Node();
    }

    void concat(char *str) {
        Node *temp = new Node(str);
        Node *newRoot = new Node();
        newRoot->left = root;
        newRoot->right = temp;
        newRoot->weight = newRoot->left->weight;
        if (newRoot->left->right != nullptr) {
            newRoot->weight += newRoot->left->right->weight;
        }
        root = newRoot;   
    }

    void concatRope(Rope r1, Rope r2){
        Node *newRoot = new Node();
        newRoot->left = r1.root;
        newRoot->right = r2.root;
        newRoot->weight = newRoot->left->weight;
        if (newRoot->left->right != nullptr){
            newRoot->weight += newRoot->left->right->weight;
        }
        r1.root = newRoot;
        r2.root = newRoot;
    }


    char index(int i) { 
        Node *temp = root;
        if (i > temp->weight) {
            i -= temp->weight;
            return temp->right->data[i];
        }
        while (i < temp->weight) {
            temp = temp->left;
        }
        i -= temp->weight;
        return temp->right->data[i];
    }

    void printRope() {
        printRopeNode(root);
        cout << '\n';
    }

    void printRopeNode(Node *node) {
        if (node != nullptr) {
            printRopeNode(node->left);
            if (node->data != nullptr){
                cout << node->data;
            }
            printRopeNode(node->right);
        }
    }

    // void split(int i) {
    //     if (i < weight) {

    //     }
    // }

    // void insert(const Cursor& c, const char text[], int len) {}
    // void remove(Range r) {}
    // void replace(Range r, const char text, int len) {}
    // int length () {} // returns size of buffer
    // Cursor begin() const;
    // Cursor end() const;
    // Cursor get(int i) const {} // returns Cursor requested

};

int main() {
    Rope a;
    Rope b;
    Rope c;
    a.concat("hello");
    a.printRope();
    b.concat("Goodbye");
    b.printRope();
    c.concatRope(a,b);
    c.printRope();
}