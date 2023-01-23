//Cansin Narsahin
//00029126

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node 
{ 
	string name; 
	int x;
	int y;
	node *sw; 
	node *se; 
	node *nw; 
	node *ne; 

	node()
	{}
	node(string n, int x_val, int y_val, node* p, node*q, node * k, node*l)
		: name(n), x(x_val), y(y_val), nw(p), ne(q), sw(k), se(l)
	{};
};

class quadtree
{
		private:

		node * root;												//a pointer to the root node of the tree
		vector<string> visited;										//cities visited during pueries search
		vector<string> cities_in_r;									//cities in the r
		
		public:

		quadtree();																// constructs a root pointer for the whole tree

		node* pt_compare(node* p, node* r) const;								// returns the quadrant of the point quadtree rooted at node r in which node p belongs

		string pt_compare_string(node* p, node* r) const;						//like pt_compare but returns string values "nw"/"ne"/"se"/"sw"

		void insertNode(node*p);												//inserts given node to the tree
		
		void pretty_print (node* root);											//prints the tree

		node* return_root();													//return root

		void linker(string direction, node* & nodePtr, node* & p);				//linkes given nodes to their given direction

		void search(node* p, const int & c_x, const int & c_y,const int & r);	//seaches for the cities in the given circle and add them to visited and cities_in_r vectors

		void print_vectors();													//prints and clears the vectors

};