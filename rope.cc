using namespace std;

class Rope {
private:

public:
    Rope() {}
    Rope(const char str[]) {}
    Rope(const char str[], int len) {}
    void insert(const Cursor& c, const char text[], int len) {}
    void remove(Range r) {}
    void replace(Range r, const char text, int len) {}
    int length () {} // returns size of buffer
    Cursor begin() const;
    Cursor end() const;
    Cursor get(int i) const {} // returns Cursor requested

};

class Cursor {
public:
    Cursor() {}
    Cursor(int offset) {} 
    Cursor(const Cursor& c, int offset) {}
};

class Range {
private:
    Cursor start, end;
public:
    Range(const Cursor& start, const Cursor& end) : start(start), end(end) {}
    int length() const {}   // returns length of the range

};

class Window {

};