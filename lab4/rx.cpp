#include "mac-hdr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char** argv){

	mac_hdr hdr2;
	
	char buf[sizeof(hdr2)+1] = {};
	size_t rx_off;
	
	string fn = "data.txt";
	string line;
	
	ifstream fin(fn.c_str());
	if(!fin){
		cout << "Error while opening file " << fn << endl;
		exit(127);
	}
	
	if(!getline(fin,line)){
		cout << "Error while reading file " << fn << endl;
		exit(-1);
	}
	fin.close();
	strcpy(buf,line.c_str());
	
	if(!hdr2.deserialize(buf,rx_off)){
		cout << "Deserialization failed." << endl;
		exit(-2);
	}
	
	cout << "hdr2. sn = " << (int)hdr2.sn << " hdr2.src = " << (int)hdr2.src << " hdr2.dest = " << (int)hdr2.dest << endl;
	
	return 0;
	
}
