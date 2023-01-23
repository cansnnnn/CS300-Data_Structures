//Cansin Narsahin
//00029126

#include "cansinnarsahin_tree.h"

quadtree:: quadtree()
{
	root=NULL;
}

node* quadtree:: return_root()
{
	return root;
}

void quadtree:: pretty_print (node * root)
{
	if (root != NULL) // if the tree is not empty
	{
		cout<< root->name<<endl;
		pretty_print(root->se); 
		pretty_print(root->sw);
		pretty_print(root->ne);
		pretty_print(root->nw);
	}
}

node* quadtree:: pt_compare (node*p, node*r) const
{
	if (p->x <= r->x && p->y <= r->y)
	{
		return p->ne;
	}
	else if (p->x <= r->x)
	{
		return p->se;
	}
	else if ( p->y <= r->y)
	{
		return p->nw;
	}

	else
	{
		return p->sw;
	}
}

string quadtree:: pt_compare_string (node*p, node*r) const
{
	if (p->x <= r->x && p->y <= r->y)
	{
		return "ne";
	}
	else if (p->x <= r->x)
	{
		return "se";
	}
	else if ( p->y <= r->y)
	{
		return "nw";
	}

	else
	{
		return "sw";
	}
}

void quadtree::linker(string direction, node* & nodePtr, node* & p)
{
	if (direction == "nw")
	{
		nodePtr->nw = p;
	}

	else if (direction == "sw")
	{
		nodePtr->sw = p;
	}

	else if (direction == "se")
	{
		nodePtr->se = p;
	}

	else if (direction == "ne")
	{
		nodePtr->ne = p;
	}
}

void quadtree:: insertNode(node*p)
{
	if (root==NULL)	
	{
		root=p;
	}

	else //we have a root, need to find the location fornext item
	{
		node* nodePtr= root;
		node* parent;
		while ( nodePtr != NULL)
		{
			parent = nodePtr;
			nodePtr = pt_compare(nodePtr,p);
		}

		if ( nodePtr == NULL)
		{
			string direction = pt_compare_string(parent, p);
			linker(direction, parent, p);
			//cout<<"inserted: "<<p->name<<" to "<<direction<<" of "<<parent->name<<endl;
		}
	}
}

void quadtree:: print_vectors()
{
	string cities_r = "";
	if ( cities_in_r.size() == 0)
	{
		cities_r = "<None>";
	}

	else
	{
		for (int i = 0; i < cities_in_r.size(); i++)
		{
			cities_r = cities_r + cities_in_r[i] + ", ";
		}
		cities_r = cities_r.substr(0, cities_r.size()-2);
	}
	cout<<cities_r<<endl;
	cities_in_r.clear();
	

	string visited_string = "";
	for (int i = 0; i < visited.size(); i++)
	{
		visited_string = visited_string + visited[i] + ", ";
    }
	visited_string = visited_string.substr(0, visited_string.size()-2);
	cout<<visited_string<<endl;
	visited.clear();
}

void quadtree:: search(node* p, const int & c_x, const int & c_y,const int & r)
{
	if(p!= NULL)
	{
		visited.push_back(p->name);
		bool in_c=false;

		if ( pow(p->x - c_x, 2) + pow(p->y - c_y, 2) <= pow(r,2))
		{
			cities_in_r.push_back(p->name);
		}

		if ( pow(p->x - c_x, 2) + pow(p->y - c_y, 2) < pow(r,2))
		{
			in_c = true;
		}

		if (in_c || (p->x < c_x && p->y > (c_y -r) ) || (p->x <= (c_x + r) && p->y >= c_y) )
		{
			search(p->se, c_x, c_y, r); //se 
		}

		if ( in_c || (p->x > (c_x-r) && p->y >= c_y) || (p->x > c_x && p->y > (c_y -r)) ) 
		{
			search(p->sw, c_x, c_y, r); //sw 
		}
		
		if ( in_c || (p->x < c_x && p->y <= (c_y +r) ) || (p->x <= (c_x+r) && p->y < c_y) )
		{

			search(p->ne, c_x, c_y, r); //ne
		}

		if ( in_c || (p->x > (c_x-r) && p->y <= c_y) || ( p->x > c_x && p->y <= (c_y+r)) )
		{
			search(p->nw, c_x, c_y, r); //nw
		}

	}

}