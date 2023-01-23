//Cansin Narsahin
//00029126

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "cansinnarsahin_tree.h"

using namespace std;

//functions are in the class cpp file

int main ()
{
    quadtree tree; //creates a quadtree
	int x_max, y_max; //max x and y values



	//file opening for cities
    string file_name = "cities.txt";
    ifstream f1;
	do
    {
		f1.open(file_name);
    } while (f1.fail());

	//file reading
	int line_ind=0;
    string s, line;
	while (getline(f1, line))
    {
        s = line;
		if (line_ind==0) // takes max x and y values
		{
			x_max = stoi(s.substr(0, s.find(" ")));
			y_max = stoi(s.substr(s.find(" ")+1,s.length()));
		}

		else //adds the new node to the tree if appropriate
		{
			string city_name = s.substr(0, s.find(" "));
			int x_val = stoi(s.substr(s.find(" ")+1,s.rfind(" ")));
			int y_val = stoi(s.substr(s.rfind(" ")+1,s.length()));

			if ( !(x_val<x_max && y_val<y_max && x_val>=0 && y_val>=0) )
			{
				cout<<"ERROR: Incorrect x or y value (this node will not be added to the tree)"<<endl;
			}
			else
			{
				node * n = new node (city_name, x_val, y_val, NULL, NULL, NULL, NULL);

				tree.insertNode(n);
			}
		}
		line_ind ++;
    }

	tree.pretty_print(tree.return_root());
    f1.close();



	cout<<endl;



	//file opening for queries
    string file_name_2 = "queries.txt";
    ifstream f2;
	do
    {
		f2.open(file_name_2);
    } while (f2.fail());

	//file reading
    string s2, line2;

	while (getline(f2, line2))
    {
        s2 = line2;
		int q_x = stoi(s2.substr(0, s2.find(", ")));
		int q_y = stoi(s2.substr(s2.find(", ")+1,s2.rfind(", ")));
		int q_r = stoi(s2.substr(s2.rfind(", ")+1,s2.length()));

		tree.search(tree.return_root(), q_x, q_y, q_r);

		tree.print_vectors();
		cout<<endl;

	}

    f2.close();

	return 0;
}