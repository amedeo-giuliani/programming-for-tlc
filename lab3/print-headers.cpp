#include <iostream>
#include <memory>
#include "headers.h"
#include "phy-header.h"
#include "mac-header.h"
#include "net-header.h"
#include "tran-header.h"
#include "pres-header.h"
#include "sess-header.h"
#include "app-header.h"
#include "packet.h"

using namespace std;

int main(int arcg, char** argv){
	
	shared_ptr<Header> sp1 = make_shared<PHYHeader>(40);
	shared_ptr<Header> sp2 = make_shared<MACHeader>(14);
	shared_ptr<Header> sp3 = make_shared<NETHeader>(20);
	shared_ptr<Header> sp4 = make_shared<TRANHeader>(20);
	shared_ptr<Header> sp5 = make_shared<PRESHeader>(0);
	shared_ptr<Header> sp6 = make_shared<SESSHeader>(0);
	shared_ptr<Header> sp7 = make_shared<APPHeader>(0);
	
	Packet packet1{sp1,sp2,sp3,sp4,sp5,sp6,sp7};
	packet1.print();
	
	cout << "Number of headers in packet1: " << packet1.getNumHeaders() << endl;
	cout << endl << endl;
	
	bool ok = packet1.addHeader(make_shared<PHYHeader>(40));
	
	if(ok)
		cout << "Insertion OK" << endl;
	else
		cout << "Insertion failed" << endl;
	
	return 0;
}
