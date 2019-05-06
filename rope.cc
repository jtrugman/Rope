/*
Questions to Ask Professor Kruger:
1. Split function --> Very confused on how it works
*/

#include <iostream>
using namespace std;
class Rope {   
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

    void concatRope(const Rope& r2){ // concats 2 ropes
        Node *newRoot = new Node();
        newRoot->left = root;
        newRoot->right = r2.root;
        newRoot->weight = newRoot->left->weight;
        if (newRoot->left->right != nullptr){
            newRoot->weight += newRoot->left->right->weight;
        }
        root = newRoot;
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

    int length () {
        return root->weight;
    }


    char returnValByIndex(int i) { 
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

    //#if 0

    void findSplit(int n) {
        Node *temp = root;
        int sum = temp->weight;
        int base = 0;
        if (temp->weight > n){
            base = temp->weight;
            temp = temp->left;
            sum += temp->weight;
        } else if(temp->weight < n) {
            temp = temp-> right;
        } 
    }
    Rope split(int n) { // splits orig rope and returns the second half of the rope

    }

    void insert(int index, char *val) {
        Rope temp = split(index);
        concat(val);
        concatRope(temp); // r1 is the r1.insert(Cursor, value)
    }

    void deleteItem(int index) {
        Rope r2 = split(index);
        Rope r3 = split(index-1);
        concatRope(r2); // r1.ConcatRope(r2);
        r3.makeEmpty();
    }
   // #endif

    

    // void remove(Range r) {} // KC
    // void replace(Range r, const char text, int len) {} //KC

};

// class data with list of observers 
// method of i changed 
// publish and subscribe
// subscribe
// unsubscribe
// changed
// node is data
// window and range is observers

# if 0
class Cursor { // publish, subscribe datamodel for node --> model view controller
    private:
        int index;
       
    public:
        Cursor(int index) : index(index){}
   
};
# endif

int main() {
    Rope a;
    Rope b;
    Rope c;
    a.concat("hello");
    a.printRope();
    b.concat("Goodbye");
    b.printRope();
    c.concat("working");
    c.printRope();
    cout << '\n';
    cout <<'\n';

    a.concatRope(b);
    a.printRope();
    a.concatRope(c);
    
    a.printRope();
    cout <<'\n';


}