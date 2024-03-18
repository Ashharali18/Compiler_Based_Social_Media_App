#include<iostream>
#include<string>
using namespace std;

class post {  //Class for the node of the post 
public:
	
	string caption;
	string location;
	post* next;
	post(){
		next = NULL;
		caption = " ";
		location = " ";
	
	}

	~post() {

	}
};