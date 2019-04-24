 // char val;
        // Rope* r;

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


             // void printCursor() {
        //     cout << "index: " << index << '\t' << "Value: " << val << '\n';
        // }