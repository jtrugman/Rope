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

    void concat(char *str) {    // concats string and rope
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

    void concatRope(const Rope& r1, const Rope& r2){ // concats 2 ropes
        Node *newRoot = new Node();
        newRoot->left = r1.root;
        newRoot->right = r2.root;
        newRoot->weight = newRoot->left->weight;
        if (newRoot->left->right != nullptr){
            newRoot->weight += newRoot->left->right->weight;
        }
        root = newRoot;
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
        printRope(root);
        cout << '\n';
    }

    void printRope(Node *node) {
        // cout << "Node here. \n";
        if (node != nullptr) {
            printRope(node->left);
            if (node->data != nullptr){
                cout << node->data;
            }
            printRope(node->right);
        }
    }

    #if 0
    void insert(int index, char *val) {
        split(index);
        r2.concat(val);
        concatRope(r1, r2);
    }
    #endif

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
    // b.printRope();
    c.concat("working");
    // c.printRope();
    cout << '\n';

    a.concatRope(a,b);
    cout <<'\n';

    a.printRope();
    a.concatRope(a,c);
    
    a.printRope();
    cout <<'\n';

}