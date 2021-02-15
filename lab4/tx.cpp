#include "mac-hdr.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){

	mac_hdr hdr1;
	hdr1.sn = 1;
	hdr1.src = 4;
	hdr1.dest = 2;
	
	char buf[sizeof(hdr1)+1] = {};
	size_t tx_off;
	
	string fn = "data.txt";
	
	if(!hdr1.serialize(buf,tx_off)){
		cout << "Serialization failed." << endl;
		exit(-1);
	}
	
	ofstream fout(fn.c_str());
	if(!fout){
		cout << "Error while opening file " << fn << endl;
		exit(127);
	}
	
	for(int i = 0; i < sizeof(buf); i++){
		fout << buf[i];
	}
	
	fout.close();

	return 0;
	
}
