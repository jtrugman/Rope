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
        
    }

    /*
        Returns value at index i 
    */
    char index(Node* node, int i) {   // like cursor???
        Node* p = node;
        if (p->weight <= i) {
            return index(p->right, i - p->weight);
        } else if (p->left != nullptr) {
            return index(p->left, i);
        }
        return p->data[i];
    }


    void insert(const Cursor& c, const char text[], int len) {}
    void remove(Range r) {}
    void replace(Range r, const char text, int len) {}
    int length () {} // returns size of buffer
    Cursor begin() const;
    Cursor end() const;
    Cursor get(int i) const {} // returns Cursor requested

};