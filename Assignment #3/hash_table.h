//Cansin Narsahin
//29126

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;


// template for generic type
template <typename K, typename V>
class Hash {
	private:

		enum EntryType {ACTIVE, EMPTY, DELETED};

		struct HashItem //hash table items
		{
			K code;                                               
			V value;                                            
			EntryType info;                                         

			HashItem(K c = K(), const V & v = V(), EntryType i = EMPTY)
				: code(c), value(v), info(i){}
		};

		vector<HashItem> dict;	//hash table
		int size;				//current size
		K ITEM_NOT_FOUND;

		//finds position
		int findPos( V & val) 
		{
			int index = hashCode(val);
			while(dict[index].info != EMPTY && dict[index].value != val) {
				index++;
				index = index % 4096;
			}
			return index;
		}

	public:

		Hash() //constructor
		{
			size = 256;
			dict.resize(4096);
			ITEM_NOT_FOUND=-1;

 
			// Initialise all elements of dict
			for (int i = 0; i < 4096; i++)
			{
				if ( i< 256)
				{
					dict[i].code = i;
					dict[i].value = char(i);
					dict[i].info = ACTIVE;
				}
				else
					dict[i].info = EMPTY;
			}         
        
		}

		//hash function
		int hashCode(V & v){
    
			int h = 0;
  			for (unsigned char ch: v)
				h = 19 * h + ch;
			h = h % 4096;
			if (h > 0) 
				return h;
		   return h + 4096;
		}

		// add keys and values 
		void insert(K key, V value)
		{
			int currentPos = findPos(value);

			if (dict[currentPos].info==ACTIVE) 
				return;

			dict[currentPos] = HashItem(key, value, ACTIVE);
		}

		// displays the stored dict
		void print()
		{
			for (int i = 0; i < 4096; i++) 
			{
				if (dict[i].info != EMPTY && dict[i].code != -1)
					cout << "key = " << dict[i].code << "  value = "<< dict[i].value << endl;
			}
		}

		//finds position
		K find(V & val) {
			int c = findPos(val);
			if (dict[c].info==ACTIVE) 
				return dict[c].code;   
			return ITEM_NOT_FOUND;
		}

		//builds the table for given value from main and return out
		string build(string input)
		{
			string out="";
			string p = "", c = "";
			p += input[0];
			int currentSize=256;
			for (int i = 0; i < input.length(); i++) {
				//if(i == input.length() - 1)
					//cout << input[i] << endl;
				if (i != input.length() - 1)
					c += input[i + 1];

				//if p+c is not in the dict
				if (find(p + c) == ITEM_NOT_FOUND ){
					out = out + to_string(find(p)) + " ";
					insert(currentSize++, p+c);
					p = c;  
				} 
				else {
					p = p + c;
				}
				
				c = "";
			}
			//cout << p + c << endl;
			out = out + to_string(find(p )) + " ";
			return out;
		}

};