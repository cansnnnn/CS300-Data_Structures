//Cansin Narsahin
//29126

#include "29126_CansinNarsahin_MPQ.h"

MPQ::MPQ() { }

MPQ::~MPQ() 
{
	heap.resize(0);
	location.resize(0);
	currentSize=0;
}

MPQ::MPQ(int s)
{
	currentSize=0;
	heap.resize(s+3);
    location.resize(s+3);
	fill(location.begin(), location.end(), -1);
}

void MPQ::print_heap_loc()
{
	if (currentSize==0)
	{
		cout<<"Currently empty."<<endl;
		return;
	}

	cout<<"Heap:"<<endl;
	for(int i=0;i<currentSize;i++)
	{
		cout<<i<<") "<<"v="<<heap[i].value<<" , l="<<heap[i].label<<endl;
	}

	cout<<endl<<"Location:"<<endl;

	for (int i=0; i<location.size();i++)
	{
		cout<< i<<") "<<location[i]<<"  ";
	}
	cout<<endl;
}


bool MPQ:: IsEmpty()
{
	if ( currentSize == 0)
		return true;
	return false;
}
 
void MPQ::percolateUp(int & hole, const int & v)
{
	for( ; hole > 1 && v < heap[ hole / 2 ].value; hole /= 2 )
	{
		heap[ hole ] = heap[ hole / 2 ];
		location[heap[hole].label] = hole;
	}
	hole --;
}

//modified version of "void BinaryHeap<Comparable>::percolateDown( int hole )" from lecture notes (10-Heaps)
void MPQ::percolateDown(int & hole)
{
	int c=0;
	MPQ_item temp = heap[hole];

	for( ; hole * 2 <= currentSize; hole = c )
	{
		c = hole * 2;
		if( c != currentSize && heap[ c + 1 ].value < heap[ c ].value )
			c++;
		if( heap[ c ].value < temp.value )
			heap[ hole ] = heap[ c ];
        else
			break;
	}

	heap[ hole ] = temp;
	location[heap[hole].label] = hole;
    hole = c;

}

//modified version of "void BinaryHeap<Comparable>::insert( const Comparable & x )" from lecture notes (10-Heaps)
void MPQ::insert (int v, int l)
{
	//print_heap_loc();

	MPQ_item i(l, v);
	heap[currentSize]=i;
	location[l]= currentSize;
	
	// Percolate up
    int hole = ++currentSize;
	percolateUp(hole, v);

    heap[ hole ] = i;
	location[l] = hole;
}

int MPQ::GetMax()
{
	int max=0;
	if (currentSize!= 0)	
	{
		for (int i=0; i<currentSize; i++)
		{
			if(max<heap[i].value)
				max=heap[i].value;
		}
	}
	return max;
}

int MPQ::Remove(int l) 
{
	int hole= location[l]; //finds from locations
	int v = heap[hole].value;
	
	location[heap[hole].label] = hole;
	heap[hole] = heap[currentSize - 1];
	currentSize-=1;

	MPQ_item t = heap[hole];

	if (heap[hole].value < heap[2 * hole + 1].value || heap[hole].value < heap[2 * hole + 2].value) //smaller than children
		percolateDown(hole);

	if (heap[hole].value > heap[(hole - 1) / 2].value) //greater than parent
		percolateUp(hole, v);

    heap[hole] = t;
    location[heap[hole].label] = hole;

	return v;
}

