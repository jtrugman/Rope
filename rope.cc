using namespace std;

class Rope {
private:

public:
    Rope() {}
    Rope(const char str[]) {}
    Rope(const char str[], int len) {}

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