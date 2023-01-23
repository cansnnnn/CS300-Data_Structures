//Cansin Narsahin
//29126

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MPQ_item
{
	int label;
	int value;

	MPQ_item()
	{}
	MPQ_item(int l, int val)
		: label(l), value(val)
	{};
};

class MPQ
{
public:
	MPQ();						//Constructor
	MPQ(int max_size);			//Constructor with max size
	~MPQ();						//Destructor
	void insert (int v, int l);	//inserts an item with the given value and label into the MPQ
	int Remove(int l);			//removes the value with this label and returns it
	int GetMax();				//returns the maximum value that is currently stored
	bool IsEmpty( );			//check if it is empty
	void print_heap_loc();		//prints heap and locaction 

private:
	int currentSize;			//Number of elements in heap
	vector<MPQ_item> heap;		//The heap array
	vector<int> location;		//The location array

	void percolateUp(int & hole, const int & v);
	void percolateDown( int & hole );

};



