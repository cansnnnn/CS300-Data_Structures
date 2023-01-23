//Cansin Narsahin
//29126

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//return true if given þndex and list contains
bool is_in(int i , int myCode, const vector<int> & v)
{
	if(v[i] >= myCode)
		return false;
	return true;
}


int main()
{
    
    vector<int> arr;		//to hold the codes
    vector<string> table;	//to hold the corresponding strings
	string out="";			//out value for decompout
    
	//creates table
	for (int i=0; i<4096;i++)
	{
		if(i<256)
			table.push_back(string(1,char(i)));

		else
			table.push_back("");
	}

    
    // read the file
    int code;
    ifstream compout("compout.txt");
    ofstream decompout("decompout.txt");
    
    while (!compout.eof()) {
        compout >> code;
        arr.push_back(code);
    }

	arr.pop_back(); //for extra endl at the end
	
    out += table[arr[0]]; 
    int myCode=256; //start from
    int i =1;
	while(i < arr.size()) {
		 string pre = table[arr[i-1]];
		 string c="";
        // not in table
		 if (!is_in(i,myCode,arr)) {
            table[myCode] = pre+ pre[0];
            out += (pre + pre[0]);
        }
        else {
            c = table[arr[i]];
            table[myCode] = pre + c[0];
            out+= c;
        }
		myCode++;
		i++;
    }
	decompout<<out;
	return 0;
}
