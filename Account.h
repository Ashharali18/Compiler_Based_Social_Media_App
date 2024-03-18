#include<iostream>
#include<string>
using namespace std;

class Account  { //Class for the node of the accounmt
public:
	Account* next;
	string name;
	int age;
	string email;
	string gender;
	string username;
	string password;
	string contactNum;

	Account() {
		next= NULL;
		age = 0;
	}

	~Account() {
		
	}
};