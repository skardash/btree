#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class BTree {
public:
	bool leaf;
	int t;
	vector<int> vals;
	vector<BTree*> bt;
	BTree *parent;
	
	typedef vector<int> ints;
	typedef vector<BTree*> trees;
	int insert(ints &cont, int value) {
		ints::iterator it = std::lower_bound( cont.begin(), cont.end(), value, std::less<int>() );
		it = cont.insert(it, value); // insert before iterator it
		return (it - cont.begin());
	}
	
	BTree(int s) {
		t = s;
	}
	
	
	int find_pos(int value) {
		ints::iterator it = std::lower_bound(vals.begin(), vals.end(), value, std::less<int>());
		return (it - cont.begin());
	}
	
	void insert_tree(int elem) {
		/* add element to BTree: reach the leaf and put it there */
		/*
			go to the leaf
			add_element to the leaf
			
			L: check if current BTree is full
				split
				if parent is NULL
					initialize it
				add element to parent BTree
				move to parent BTree
				goto L
			
		*/
		int pos = find_pos(elem);
		if (!leaf) {
			this->bt[pos].insert_tree(elem);
		} else {
			add_element(elem,NULL,NULL);
		}
		if check() {
			vector<BTree*> spl = split();
			is (parent == NULL) {
				BTree *par = spl[1];
			} else {
				// insert node
				parent->add_element(elem,spl[0],spl[2]);
			}
		}
	}
	
	bool check() {
		return (vals.size() >= 2*t-1);
	}
	
	

	void add_element(int elem, BTree *left, BTree *right) {
		/* add element to vals and links to child BTrees to bt, in case it's lead we add NULLS */
		// find ix: vc[ix] < n < vc[ix+1]
		// in case n is equal to some of the elements, don't add it
		int pos = insert(vals,elem);
		bt.insert(next(bt.begin(),pos),left);		
		bt[pos+1] = right;
		if check() {
			vector<BTree*> spl = split();
			is (parent == NULL) {
				BTree *par = spl[1];
			} else {
				// insert node
				parent->add_element(elem,spl[0],spl[2]);
			}
		}
	}
	
	void delete_element(int num) {
		/* delete element from the BTree */
	}
	
	vector<BTree*> split() {
		/* split the tree into 2 Trees and parent */
		vector<BTree*>  btspl;
		int sz = vals.size()/2;
		
		BTree *left, *center, *right;
		left = new BTree(t);
		right = new BTree(t);
		
		// creating top node
		center = new BTree(t);
		center->vals.resize(1);
		center->vals[0] = vals[vals.size()/2];
		center->bt.resize(2);
		center->bt[0] = left;
		center->bt[1] = right;
		
		// filling left
		left->vals.resize(sz);
		copy(vals.begin(), next(vals.begin(),sz), left->vals.begin());
		
		left->bt.resize(sz);
		left->parent = center;
		copy(bt.begin(), next(bt.begin(),sz), left->bt.begin());
		
		// filling right
		right->vals.resize(sz);
		right->parent = center;
		copy(next(vals.begin(),sz+1), vals.end(), right->vals.begin());
		
		right->bt.resize(sz);
		copy(next(bt.begin(),sz+1), bt.end(), right->bt.begin());
		
		
		btspl.resize(3);
		btspl[0] = left;
		btspl[1] = center;
		btspl[2] = right;
		return btspl;
	}
	
	void print(int level) {
		// print list of values
		cout << "level = " << level << endl;
		for (vector<int>::iterator pos = vals.begin(); pos < vals.end(); pos++)
			cout << ' ' << *pos;
		cout << '\n';
		vector<int>::iterator pos_int = vals.begin();
		for (vector<BTree *>::iterator pos = bt.begin(); pos < bt.end(); pos++) {
			if (*pos != NULL) {
				cout << "-> Right value: " << *pos_int << endl;
				(*pos)->print(level + 1);
			} else {
				cout << "-> No children!" << endl;
			}
			pos_int++;
		}
		
		// print each child tree
	}
	
	/*
	void insert(int n) {
		// find ix: vc[ix] < n < vc[ix+1]
		// in case n is equal to some of the elements, don't add it
		
		if (leaf) {
			vals.push_back(n);
 			sort (vals.begin(), vals.end()); 
 			if (vals.size() == 2*t-1) {
 				//split the leaf and modify upper-level node
 				vector<int> lf1(t-1); 
 				vector<int> lf2(t-1);
 				
 				vector<BTree*> bt1;
 				vector<BTree*> bt2;
 				
 				copy(vals, vals+t-1, lf1.begin());
				copy(vals+t, vals+2*t-1, lf2.begin());
				
				copy(bt, bt+t-1, bt1.begin());
				copy(bt+t, bt+2*t-1, bt2.begin());
 			}
		} else {
			int ix = 0;
			while (ix < vals.size()) {
				if (vals[ix] > n) 
					break;
				else
					ix++;
			}
			bt[ix]->insert(n);
			//recursively add element to the subtree
		}
	}
	

	void delete_elem(int n) {
	
	}
	
	template<typename T> vector<list<T>> split_list(list<T> &ls) {
		vector<list<T>> vc;
		list<T> ls1, ls2;
		ls1.splice( ls1.begin(), ls, ls.begin(), next(ls.begin(), ls.size()/2));
		ls2.splice( ls2.begin(), ls, next(ls.begin(), 1), ls.end());
		vc.push_back(ls1); vc.push_back(ls); vc.push_back(ls2); 
		return vc;
	}

	BTree* split() {
		// find the center element of the list in values
		// create 2 lists from the original
		// add 2 Tree* structures to the new node
		int sz = vals.size()/2;
		
		BTree *left, *center, *right;
		left = new BTree(t);
		right = new BTree(t);
		
		// creating top node
		center = new BTree(t);
		center->vals.resize(1);
		center->vals[0] = vv[vals.size()/2];
		center->bt.resize(2);
		center->bt[0] = left;
		center->bt[1] = right;
		
		// filling left
		left->vals.resize(sz);
		copy(vals.begin(), next(vals.begin(),sz), left->vals.begin());
		
		left->bt.resize(sz);
		copy(bt.begin(), next(bt.begin(),sz), left->bt.begin());
		
		// filling right
		right->vals.resize(sz);
		copy(next(vals.begin(),sz+1), vals.end(), right->vals.begin());
		
		right->bt.resize(sz);
		copy(next(bt.begin(),sz+1), bt.end(), right->bt.begin());
		return center;
	}
	
	int insert( ints &cont, int value ) {
		ints::iterator it = std::lower_bound( cont.begin(), cont.end(), value, std::less<int>() );
		it = cont.insert(it, value); // insert before iterator it
		return (it - cont.begin());
	}

	
	void add(int val) {
		int pos = insert(vals,val);
		
	}	
	*/
		
};

/*
	operations:
		insert
			
			
		delete
*/

int main() {
	// construct BTree on my own
	// create child element
	BTree b2(2);
	b2.vals.resize(2);
	b2.vals[0] = -4;
	b2.vals[1] = -3;
	b2.bt.resize(3);
	b2.bt[0] = NULL;
	b2.bt[1] = NULL;
	b2.bt[2] = NULL;
	b2.leaf = true;
	
	// create child element
	BTree b3(2);
	b3.vals.resize(2);
	b3.vals[0] = 4;
	b3.vals[1] = 5;
	b3.bt.resize(3);
	b3.bt[0] = NULL;
	b3.bt[1] = NULL;
	b3.bt[2] = NULL;
	b3.add_element(6,NULL,NULL);
	b3.leaf = true;
	
	// create root element
	BTree b1(2);
	b1.vals.resize(2);
	b1.vals[0] = 0;
	b1.vals[1] = 1;
	b1.bt.resize(3);
	b1.bt[0] = NULL;
	b1.bt[1] = NULL;
	b1.bt[2] = NULL;
	b1.add_element(2,&b2,&b3);
	b1.leaf = false;
	b2.parent = b1;
	b3.parent = b1;
	// b1.print(0);

	//seems like ok!
	
	vector<BTree*> bbb = b1.split();
	bbb[1]->print(0);
	
	//add b2 to b1
	return 0;
}

