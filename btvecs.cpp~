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
		// vals.resize(0); bt.resize(0);
		t = s;
		leaf = true;
	}
	
	
	int find_pos(int value) {
		ints::iterator it = std::lower_bound(vals.begin(), vals.end(), value, std::less<int>());
		return (it - vals.begin());
	}
	
	BTree* insert_tree(int elem) {
		cout << "------------insert_tree report------------" << endl;
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
		
		
		cout << "insert start" << endl;
		BTree* curr = this;
		cout << "leaf = " << leaf << endl;
		while (!curr->leaf) {
			int pos = curr->find_pos(elem);
			cout << "going to " << pos << " element" << endl;
			curr = curr->bt[pos];
		}
		cout << "reached the leaf" << endl;
		//reached the leaf
		curr->add_element(elem,NULL,NULL);
		//moving up and adding the elements
		while (curr->check()) {
			cout << "going to split" << endl;
			vector<BTree*> spl = split();
			cout << "split done successfully" << endl;
			if (parent == NULL) {
				cout << "parent == NULL" << endl;
				// we are on the very top 
				BTree *par = spl[1];
				cout << "bt[2] = " << bt[2] << endl;
				cout << "bt[3] = " << bt[3] << endl;
				cout << "spl[2]->bt[0] = " << spl[2]->bt[0]  << endl;
				cout << "spl[2]->bt[1] = " << spl[2]->bt[1]  << endl;
				cout << "we are returning par" << endl;
				cout << "par->vals.size() = " << par->vals.size() << endl;
				cout << "par->bt.size() = " << par->bt.size() << endl;
				cout << "par->bt[1]->bt[0] = " << par->bt[1]->bt[0] << endl;
				cout << "par->bt[1]->bt[1] = " << par->bt[1]->bt[1] << endl;
				cout << "par->bt[1]->leaf = " << par->bt[1]->leaf << endl;
				cout << "spl[2]->leaf = " << spl[2]->leaf << endl;
				cout << "------------/insert_tree report------------" << endl;
				return par;
			} else {
				// we go to parent and add the new value to it
				curr = parent;
				curr->add_element(spl[1]->vals[0],spl[0],spl[2]);
			}
		}
		cout << "------------/insert_tree report------------" << endl;
		return this;
	}
	
	bool check() {
	//	cout << "check(): " << vals.size() << endl;
		return (vals.size() >= 2*t-1);
	}
	
	void add_element(int elem, BTree *left, BTree *right) {
		/* add element to vals and links to child BTrees to bt, in case it's lead we add NULLS */
		// find ix: vc[ix] < n < vc[ix+1]
		// in case n is equal to some of the elements, don't add it
		cout << "------------add_element report------------" << endl;
		cout << "array before adding:" << endl;
		for (int i=0;i<vals.size();i++) {
			cout << vals[i] << " ";
		}
		cout << endl;

		cout << "links array content before adding: " << endl;
		for (int i=0;i<bt.size();i++) {
			cout << bt[i] << " ";
		}
		cout << endl;

		cout << "child links size: " << bt.size() << endl;

		int pos = insert(vals,elem);
		cout << "pos = " << pos << endl;
		bt.insert(next(bt.begin(),pos),left);		
		bt[pos+1] = right;
		

		cout << "new link was placed to " << pos << " position" << endl;
		cout << "array after adding:" << endl;
		for (int i=0;i<vals.size();i++) {
			cout << vals[i] << " ";
		}

		cout << "links array content: " << endl;
		for (int i=0;i<bt.size();i++) {
			cout << bt[i] << " ";
		}
		cout << endl;
		/*
		cout << "right content: " << endl;
		for (int i=0;i<right->bt.size();i++) {
			cout << right->bt[i] << " ";
		}
		cout << endl;
		*/
		cout << "------------/add_element report------------" << endl;
	}
	
	void delete_element(int num) {
		/* delete element from the BTree */
	}
	
	void print_node() {
		cout << "------------print_node------------" << endl;
		cout << "vals.size() = " << endl;	
//		cout << "vals empty check: " << endl;	
		cout << this->bt.empty() << endl;		

		cout << vals.empty() << endl;		
		// cout  << vals.size() << endl; 
		for (int cnt=0; cnt<vals.size(); cnt++)
			cout << vals[cnt] << ' ';
		cout << '\n';
		cout << "bt: ";
		for (int cnt=0; cnt<bt.size(); cnt++)
			cout << bt[cnt] << ' ';
		cout << '\n';
		cout << "------------/print_node------------" << endl;
	}
	
	vector<BTree*> split() {
		/* split the tree into 2 Trees and parent */
//		cout << "Tree is splitted" << endl;
		cout << "-----------------split-------------" << endl;
		cout << "info about the node to be splitted: " << endl;
		cout << "bt.size() = " << bt.size() << endl;
		vector<BTree*>  btspl;
		int sz = vals.size()/2;
		
		BTree *left, *center, *right;
		left = new BTree(t);
		right = new BTree(t);
		
		cout << "inside split 1" << endl;
		// creating top node
		center = new BTree(t);
		center->vals.resize(1);
		center->vals[0] = vals[vals.size()/2];
		center->bt.resize(2);
		center->bt[0] = left;
		center->bt[1] = right;
		center->leaf = false;
		
		cout << "inside split 2" << endl;
		// filling left
		left->vals.resize(sz);
		copy(vals.begin(), next(vals.begin(),sz), left->vals.begin());
		
		left->bt.resize(sz+1);
		left->parent = center;
		left->leaf = this->leaf;
		copy(bt.begin(), next(bt.begin(),sz), left->bt.begin());
		
		cout << "inside split 3" << endl;
		// filling right
		right->vals.resize(sz);
		right->parent = center;
		right->leaf = this->leaf;
		cout << "right->leaf = " << right->leaf << endl;
		copy(next(vals.begin(),sz+1), vals.end(), right->vals.begin());
		
		right->bt.resize(sz+1);
		cout << "we start from " << next(bt.begin(),sz+1) - bt.begin() << endl;
		cout << "we finish at " << bt.end() - bt.begin() << endl;
		cout << "bt[2] = " << bt[2] << endl;
		cout << "bt[3] = " << bt[3] << endl;
		cout << "vals.size() = " << vals.size() << endl;
		cout << "bt.size() = " << bt.size() << endl;
		// this is smth stange
		copy(next(bt.begin(),sz+1), bt.end(), (right->bt).begin());
		cout << "right->bt[0] = " << right->bt[0] << endl;
		cout << "right->bt[1] = " << right->bt[1] << endl;

		cout << "inside split 4" << endl;
		btspl.resize(3);
		btspl[0] = left;
		btspl[1] = center;
		btspl[2] = right;

		cout << "inside split 5" << endl;
		cout << "-----------------/split-------------" << endl;
		return btspl;
	}
	
	void print(int level) {
		// print list of values
		cout << "-----------------print-------------" << endl;
		cout << "level = " << level << endl;
		print_node();
		if (!leaf) {
			for (int cnt=0; cnt<bt.size(); cnt++)
				bt[cnt]->print(level+1);
		}
		cout << "---------------/print---------------" << endl;
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
	/*
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

	BTree *b1 = new BTree(2);
	b1->vals.resize(2);
	b1->vals[0] = 0;
	b1->vals[1] = 1;
	b1->bt.resize(3);
	b1->bt[0] = NULL;
	b1->bt[1] = NULL;
	b1->bt[2] = NULL;

	// b1.add_element(2,&b2,&b3);
	
// 	b1.leaf = false;
	b1->leaf = true;	
	b1->parent = NULL;

//	b2.parent = &b1;
//	b3.parent = &b1;
	// b1.print(0);

	//seems like ok! 
	
	// vector<BTree*> bbb = b1.split();
	// bbb[1]->print(0);
	
	
	cout << "b1->leaf = " << b1->bt[1] << endl;
		
	b1 = b1->insert_tree(2);
	b1->print(0);	
		
	cout << "b1.bt[1]->leaf = " << b1->bt[1]->leaf << endl;
	b1 = b1->insert_tree(3);
	b1->print(0);	
	
	b1 = b1->insert_tree(4);
	b1->print(0);	
*/
	// create b1
	// add  elements to it
	
	BTree *b1 = new BTree(2);
	b1 = b1->insert_tree(0);
	
	b1 = b1->insert_tree(1);
	
	
	b1 = b1->insert_tree(2);
	cout << "b1->bt[1]->bt.size() = " << b1->bt[1]->bt.size() << endl;
	
	b1 = b1->insert_tree(3);
	cout << "b1->bt[1]->bt.size() = " << b1->bt[1]->bt.size() << endl;
	// b1->print(0);

	b1 = b1->insert_tree(4);
	b1->print(0);

			
	//add b2 to b1
	return 0;
}

