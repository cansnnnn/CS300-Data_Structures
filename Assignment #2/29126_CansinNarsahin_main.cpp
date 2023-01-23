//Cansin Narsahin
//29126

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "29126_CansinNarsahin_MPQ.h"
using namespace std;

struct item {
    int x;
    char drc;	// 'l' -> left, 'r'->right
    int y;
    int label;

	item()
	{}
	item(int x_c,int y_c, int l, char d)
		: x(x_c),y(y_c), label(l), drc(d)
	{};
};

//prints list to control
void print_list(vector<item> l)
{
	for (int i=0; i<l.size(); i++)
	{
		cout<<l[i].x<<" ("<<l[i].drc<<" - "<<l[i].label<<" - "<<l[i].y<<" )"<<endl;
	}
}

//partition for quicksort algorithm 
int partition(vector<item> &l, int start, int end)
{
	int pivot = end;
	int store_index= start;
	
	for(int i=start; i<end; i++)
	{
		if(l[i].x <= l[pivot].x)
		{
			if(l[i].x == l[pivot].x) //if x's are same the order is left - right
			{
				if(l[i].drc=='l')
				{
					swap(l[i],l[store_index]);
					store_index++ ;
				}

			}

			else
			{
				swap(l[i],l[store_index]);
				store_index++ ;
			}
		}
	}

	swap(l[store_index],l[pivot]);
	return store_index;
}

//sorts the list
void quicksort(vector<item> &l, int start, int end )
{
	if(start<end)
	{
		int pivot = partition(l, start, end);
		quicksort(l, start, pivot-1);
		quicksort(l, pivot+1, end);
	}
}

//prints if it max and get_max are not same
void max_control(const int & max, const int & get_max, const vector<item> & list, const int & i)
{
	if(max != get_max)
		cout << list[i].x << " " << get_max << endl;
}


int main()
{
	//file opening
    string file_name = "input.txt";
    ifstream f;
	do
    {
		f.open(file_name);
    } while (f.fail());

	//file reading
	int line_ind=0;
    string line;
	int city_num;

	f>>city_num; //reads first line

	MPQ my_mpq(city_num*2);
	vector<item> list;
	int label=0;

	while(getline(f, line))
	{
		if (line_ind > 0) //after the first line
		{
			int x_left = stoi( line.substr(0, line.find(" ")) );
			int y = stoi(line.substr(line.find(" ")+1,line.rfind(" ")));
			int x_right = stoi(line.substr(line.rfind(" ")+1,line.length()));

			//adds inputs to the list
			item i_1(x_left, y, label, 'l');
			item i_2(x_right, y, label, 'r');
			list.push_back(i_1);
			list.push_back(i_2);
		}

		line_ind ++;
		label ++;
	}

    f.close();

	//list sorting using quick sort
	quicksort(list, 0, list.size()-1);

    // until there is a building the first value is 0 0
	if(list[0].x > 0)
	{
		cout<<"0 0"<<endl;
	}

	//iterate over the list
	for (int i=0; i<list.size(); i++)
	{
		int max= my_mpq.GetMax();
		int l= list[i].label;
		int v= list[i].y;

		//if right -> remove it from my_mpq
		//if y changes, print the new y
		if (list[i].drc=='r')
		{
			int get= my_mpq.Remove(l);
	
			//if we add another value to the same x we need to print the biggest and we need to print the last element
			if( (i<list.size()-1 && list[i].x != list[i+1].x) || i==list.size()-1 )
				max_control(max, my_mpq.GetMax(), list, i); //prints if it max and get_max are not same

		}

		//if left -> insert it to my_mpq
		//if y changes, print the new y
		else
		{
			my_mpq.insert(v,l);


			//if we add another value to the same x we need to print the biggest
			if(i<list.size()-1 && list[i].x != list[i+1].x) 
				max_control(max, my_mpq.GetMax(), list, i); //prints if it max and get_max are not same

		}
	}

	return 0;
}
