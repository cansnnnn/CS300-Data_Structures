//Cansin Narsahin
//29126

#include <iostream>
#include <string>
#include <fstream>
#include "hash_table.h"
using namespace std;


int main()
{
	char ch;
	string input = "";
	ifstream compin("compin.txt");
	ofstream compout("compout.txt");
	Hash<int,string> my_table;

	//reads compin file into a string called input
	while(!compin.eof()){
		compin.get(ch); 
		input += ch;
	}
	input = input.substr(0, input.length()-1);
	
	//gets out for given input
	compout<<my_table.build(input);


	//close the files
	compin.close();
	compout.close();
   
	return 0;
}

