#include <memory.h>
#include <iostream>

using namespace std;

/**
	 @author: Dov Kruger
	 Attempt at designing a replacement for Rope from scratch.
	 Each text leaf is a line.
	 Lines are hierarchically arranged into blocks of up to capacity lines (defined as a template)
	 This means that instead of a binary tree, we have an n-degree tree, and when inserting into a line
	 nothing changes except that particular line.

	 I am starting by defining addEnd(const char s[]) because this
	 should be supremely efficient. appending to the end of a buffer is
	 one critical operation. Then it remains to be seen what we can do for insert, remove, etc.
 */
template<int capacity>
class LineRope {

	//TODO: eventually perhaps use int instead of Node*, relative pointing into a block
	// 32-bit would be smaller, and we could use a high-performance memory allocator to allocate
	// strings of same size into pools.

	class RelString {
	public:
		uint32_t len; // length of the string (up to 4Gb per line, overkill)
	private:
		uint32_t offset; // offset relative to base block
	public:
		RelString(const char* baseptr, const char* s, uint32_t len) : len(len), offset(s - baseptr) {}
		const char* relTo(const char* baseptr) const { return baseptr + offset; }
	};
	
	class Node {
	public:
		//TODO: vector<Iterator> notifyUs;  // data-observer to notify
		//TODO: uint32_t size;
		bool leaf;              // if true then the children are char*
		Node* parent;
		void* child[capacity];  // either char* or Node*
		uint32_t used;          // how many of the above child[] array is used

		Node(bool isLeaf, Node* parent) : leaf(isLeaf), parent(parent), used(0) {
		}

		Node(Node* parent, const char s[], uint32_t len) : leaf(true), parent(parent), used(1) {
			child[0] = new char[len];
			memcpy(child[0], s, len);
		}
		

		~Node() {
			if (leaf)
				for (int i = 0; i < used; i++)
					delete (char*)child[i];
			else
				for (int i = 0; i < used; i++)
					delete (Node*)child[i];
		}
		
		//TODO: does copying nodes make sense? I am using it right now.
		// be very careful, this is stealing all the pointers
		//		Node(const Node& orig) = delete;
		Node& operator =(const Node& orig) = delete;

#if 0
		//TODO: this might have to be manually named steal
		Node(const Node&& orig) : leaf(orig.leaf), parent(orig.parent), used(orig.used) {
			for (int i = 0; i < used; i++)
				child[i] = orig.child[i];
			orig.used = 0;
		}
#endif
		char* allocLine(const char s[], uint32_t len) {
			char* line = new char[len];
			memcpy(line, s, len);
			return line;
		}

		
		void addEnd(const char s[], uint32_t len) {
			if (leaf) {
				if (used >= capacity) {
					parent->addEnd(s, len);
					return;
				}
				child[used++] = allocLine(s, len);
				return;
			}
			// not a leaf
			if (parent == nullptr) { // special case for root, clone root and reparent
				if (used >= capacity) {
					Node* newFirstChild = new Node(*this); // clone this node
					child[0] = newFirstChild;
					child[1] = new Node(this, s, len);
					used = 2;
					return;
				}
        //TODO: go to next child if there is one, or add one
				//Wrong:				child[used++] = allocLine(s, len);
				return;
			}
			parent->addEnd(s, len);
		}

		friend ostream& operator<<(ostream& s, const Node& n) {
			if (n.leaf) {
				for (int i = 0; i < n.used; i++)
					s << (const char*)n.child[i];
			} else {
				for (int i = 0; i < n.used; i++)
					s << *(Node*)n.child[i];
			}
			return s;
		}
#if 0
		void addEnd(const string& s);
		void addStart(const char s[]);
		void addStart(const char s[], uint32_t len);
		void addStart(const string& s);
		void insert(uint32_t line, uint32_t offset, const char s[]);
		void insert(uint32_t offset, const char s[]);
		void remove(uint32_t offset, uint32_t len);
#endif
		
	};

#if 0
	// implement operator new locally for higher performance
	// for now this is just for debugging and can call ::new
	void *operator new(size_t size) {
		cerr << "allocating: " << size << '\n';
		//		return ::new(size);
	}
#endif
	Node root; // one built in root node, no allocation required
	uint64_t size; // total size of buffer
public:
	LineRope() : root(false, nullptr), // start with the root is a leaf node?
							 size(0)
	{
		root.child[0] = new Node(true, &root);
	}
  void addEnd(const char s[], uint32_t len) {
		root.addEnd(s, len);
	}
	void addEnd(const string& s) {
		addEnd(s.c_str(), s.length());
	}

	
	friend ostream& operator <<(ostream& s, const LineRope& r) {
		for (int i = 0; i < r.root.used; i++) {
			s << *(Node*)r.root.child[i];
		}
		return s;
	}
	class Iterator {
	private:
		Node* current;
		uint32_t line; // line within the node
		uint32_t offset; // within the string of the line		
	public:
		Iterator(LineRope& r) {
			Node* p;
			for (p = &r.root; p->leaf == false; p = (Node*)p->child[0])
				;
			current = p; // current points to first leaf node
			line = 0; // first line in the node
			offset = 0; // first character in the line
		}
		char operator [](int delta);
	};
	void insert(const Iterator& i, const char s[], uint32_t len);
	void remove(const Iterator& i, uint32_t len);
	//	void insert(const Iterator& i, LineRope& r);
	//TODO:	Iterator find(const char s[], uint32_t len);
};

int main() {
	LineRope<4> rope;

	const int n = 20;
	for (int i = 0; i < n; i++) {
		string s = "test" + to_string(i);
		rope.addEnd(s);
	}
	//	cout << rope << '\n';
}
