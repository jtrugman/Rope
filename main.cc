/*
Authors: Justin Trugman, David Lehman, Kirk Vasilas

Rope Project: We are using the Rope data structure in order to create an ultra high performance text editior
*/
using namespace std;

class Rope {   // Rope data structure
private:

    class RopeNode {
    private:
        char data[];
        int weight;
        RopeNode* right;
        RopeNode* left;
    }

public:
    Rope() {}
    Rope(const char str[]) {}
    Rope(const char str[], int len) {}

    /*
        Returns value at index i 
    */
    char index(const RopeNode& node, int i) {   // like cursor???
        if (node.weight <= i) {
            return index(node.right, i - node.weight);
        } else if (node.left != nullptr) {
            return index(node.left, i);
        }
        return node.data[i];
    }


    void insert(const Cursor& c, const char text[], int len) {}
    void remove(Range r) {}
    void replace(Range r, const char text, int len) {}
    int length () {} // returns size of buffer
    Cursor begin() const;
    Cursor end() const;
    Cursor get(int i) const {} // returns Cursor requested

};

class Cursor {  // Determines spot to insert, select
public:
    Cursor() {}
    Cursor(int offset) {} 
    Cursor(const Cursor& c, int offset) {}
};

class Range {   // Range of selection 
private:
    Cursor start, end;
public:
    Range(const Cursor& start, const Cursor& end) : start(start), end(end) {}
    int length() const {}   // returns length of the range

};

class Window {  // window of text a user is viewing and able to edit

};