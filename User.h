#include<iostream>
#include<fstream>
#include<iomanip>
#include<limits>
#include<string>
#include<cstring>
#include"Account.h"
#include"Post.h"
using namespace std;

class User /*:public Biodata */{
private:
	
	Account* head;
	Account* tail;
	post* Head;
	post* Tail;
	string Name;
	int Age;
	string ContactNum;
	string Username;
	string Password;
	string username1;
	string username2;
	string message;
	string uid;
	string isloginuser;
	int count;
	
public:
	User() {
		head = NULL;
		tail = NULL;
		Head = NULL;
		Tail = NULL;
		count = 0;
		isloginuser = " ";
		
		
	}

	void createAccount() {  //Creates a new account in the file as well as in the list.
		Account* temp = new Account;
		temp->next = NULL;
		fstream fin;
		cout << "Enter your name :" << endl;
		cin.ignore();
		getline(cin, temp->name);
		g5:
		cout << "Enter your age :" << endl;
		cin >> temp->age;
		
			if (temp->age<=0) {
				cout << "Invalid age!" << endl;
				goto g5;

			}
		g2:
		cout << "Enter your contact number(03xx-xxxxxxx) :" << endl;
		cin >> temp->contactNum;
		const char* x = (temp->contactNum).c_str();
		if (strlen(x) > 12) {
			cout << "Contact number can have maximum 11 characters!" << endl;
			goto g2;
		}
		g1:
		cout << "Please create a username :" << endl;
		cin >> temp->username;
		if (ifExist(temp->username)) {
			cout << "Usernam already taken! Please try other username." << endl;
			goto g1;
		}
		g3:
		cout << "Please create a password(Max 6 characters) :" << endl;
		cin >> temp->password;
		const char* y = (temp->password).c_str();
		if (strlen(y) > 6) {
			cout << "Password can have 6 maximum characters!" << endl;
			goto g3;
		}

		if (head == NULL) {
			head = tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	
		fstream myfile;
		myfile.open("Accounts.txt", ios::app);
		if (myfile.is_open()) {
			myfile << left << setw(20) << temp->name;
			myfile << left << setw(6) << temp->age;
			myfile << left << setw(15) << temp->contactNum;
			myfile << left << temp->username << endl;
			myfile.close();
		}
		
		string filename = temp->username + "_Inbox.txt";
		fstream fout;
		fout.open(filename, ios::out);
		if (fout.is_open()) {
			fout << "_ID_ _Username_     _Message_" << endl;
			fout.close();
		}
		string Filename = temp->username + "_Posts.txt";
		fstream Fout;
		Fout.open(Filename, ios::out);
		if (Fout.is_open()) {
			Fout << "_Sr._  _Location_  _Caption_" << endl;
			Fout.close();
		}
		fstream Log;
		Log.open("logindata.txt", ios::app);
		if (Log.is_open()) {

			Log << left << setw(10) << temp->username;
			Log << left << setw(6) << temp->password << endl;
			Log.close();
			cout << endl;
		}

		cout << "New Account created!" << endl;
		count++;
		
	}
	
	void deleteAccount( string password1) { //Deletes the account from the list.
		Account* p = head;
		Account* q=head->next;
		
		while (q->next != NULL && q->username!=isloginuser) {
			p = p->next;
			q = q->next;
		}
		do {
			if (q->username == isloginuser || q->password == password1) {
				p->next = q->next;
				free(q);
			}
			else {
				cout << "Invalid username or password!" << endl;
				break;
			}
		
			count--;
			
		
		} while (false);


		
	}

	void deleteFromFile( ) {  //Deletes the account from the file.
		
			fstream f("Accounts.txt", ios::out | ios::in);
			f.ignore(51);
			fstream out("tempp.txt", ios::out);
			out << "___Name___          _Age_ _ContactNum_   _Username_" << endl;
			while (1) {
				if (f >> Name >> Age >> ContactNum >> Username) {


					if (Username != isloginuser) {

						out << Name << "              " << Age << "    " << ContactNum << "    " << Username << '\n';

					}
					continue;
				}
				else {
					break;
				}
			}
			remove("Accounts.txt");
			rename("tempp.txt", "Accounts.txt");
			cout << "Account deleted successfully!" << endl;
			f.close();
			out.close();
	
	}

	void display() { //Displays all the accounts.
		int x = 1;
		cout << endl;
		Account* temp = head;
		while (temp != NULL) {
			cout << "---Account " << x << "---" << endl;
			cout << "Name :" << temp->name << endl;
			cout << "Username :" << temp->username<< endl;
			cout << "Age :" << temp->age << endl;
			temp = temp->next;
			x++;
		}
	}

	void printAll() {  //Prints all the data of the file
		fstream myfile;
		string data;
		myfile.open("Accounts.txt");
		if (myfile.is_open()) {
			while (getline(myfile, data)) {
				cout << data << endl;
			}
			myfile.close();
		}
		

	}

	void sendMessage() { //Sends message to the other user
		fstream fin;
		string username2;
		cout << "Who do you want to message?" << endl;
		cin >> username2;
		if(ifExist(username2)) {
			if (isloginuser != " ") {
				cout << "Type your message :";
				cin.ignore();
				getline(cin, message);
				int i = ((rand() % 1000) + 10);
				string filename1 = isloginuser + "_Inbox.txt";
				fstream f1;
				f1.open(filename1, ios::app);
				if (f1.is_open()) {
					f1 << left << setw(5) << i;
					f1 << left << setw(15) << isloginuser;
					f1 << left << message << endl;
					f1.close();
				}
				string filename2 = username2 + "_Inbox.txt";
				fstream f2;
				f2.open(filename2, ios::app);
				if (f2.is_open()) {
					f2 << left << setw(5) << i;
					f2 << left << setw(15) << isloginuser;
					f2 << left << message << endl;
					f2.close();
				}

				cout << "Message sent succesfully!" << endl;
			}
			else {
				cout << "No one is logged in at this time !" << endl;
			}

		}
		else {
			cout << "Account not present!" << endl;
		}
	}

	void deleteMessageS(string Uid) { //Unsends the message 
		string filename1;
		string fileid1, Username1, Message1 ;
		filename1 = isloginuser + "_Inbox.txt";
		fstream f1(filename1, ios::out | ios::in);
		fstream out1("temp1.txt", ios::out);

			while (1) {
				if (f1 >> fileid1 >> Username1 && getline(f1, Message1)) {

					if (fileid1 != Uid) {

						out1 << fileid1 << "  " << Username1 << Message1 << '\n';

					}
					continue;
				}
				else {
					break;
				}


			}
			f1.close();
			out1.close();

			remove(filename1.c_str());
			rename("temp1.txt", filename1.c_str());
		}

	void deleteMessageR(string Uid, string username2) { //unsends the message
		string filename2;
		string data;
		string  fileid2, Username2, Message2;
		filename2 = username2 + "_Inbox.txt";
		fstream f2(filename2, ios::out | ios::in);
		fstream out2("temp2.txt", ios::out);

		while (1) {
			
			if (f2 >> fileid2 >> Username2 && getline(f2, Message2)) {

				if (fileid2 != Uid) {

					out2 << fileid2 << "  " << Username2 << Message2 << '\n';

				}
				continue;
			}
			else {
				break;
			}

		}
	
		f2.close();
		out2.close();
		remove(filename2.c_str());
		rename("temp2.txt", filename2.c_str());

		cout << "Message deleted successfully!" << endl;
	}

	void loadDataFromFile() { //Load data from filr onto a linkedlist
		
		string Name, ContactNum, Username;
		int Age;
		fstream myfile;
		myfile.open("Accounts.txt", ios::in);
		if (myfile.is_open()) {
			myfile.ignore(51);
		
			while (1) {
				
				if (myfile >> Name >> Age >> ContactNum >> Username) {
					
					string filename = Username + "_Inbox.txt";
					fstream fout;
					fout.open(filename, ios::out);
					if (fout.is_open()) {
						fout << "_ID_ _Username_     _Message_" << endl;
						fout.close();
					}
					Account* temp = new Account;
					temp->next = NULL;
					temp->name = Name;
					temp->age = Age;
					temp->contactNum = ContactNum;
					temp->username = Username;
					if (head == NULL) {
						head = tail = temp;
					}
					else {

						tail->next = temp;
						tail = temp;
					}

				}
				else {
					break;
				}
			}
			myfile.close();
		}
		

	}

	bool ifExist(string username1) { //Tells if a particular account exists or not.
		
		fstream fin;
		fin.open("Accounts.txt", ios::in);
		fin.ignore(51);
		if (fin.is_open()) {
			while (1) {
				if (fin >> Name >> Age >> ContactNum >> Username) {
					
					if (username1 == Username) {
					
						return true;
					}

				}
				else {
					break;
				}

			}

		}
		fin.close();
		
		return false;


	}

	void mid_Node(Account* start, Account** ref_One, Account** ref_Two) { //Merge sort to sort users bu age
		Account* s;
		Account* f;
		s = start;
		f = s->next;
		while (f != nullptr) {
			f = f->next;


			if (f != nullptr)
			{
				s = s->next;
				f = f->next;
			}
		}

		*ref_One = start;
		*ref_Two = s->next;
		s->next = nullptr;
	}

	Account* merge(Account* x, Account* y) {//Merge sort to sort users bu age
		Account* temp = new Account;
		temp->age = 0;
		temp->next = nullptr;
		Account* last = temp;
		while (x != nullptr && y != nullptr)
		{
			if (x->age < y->age)
			{
				last->next = x;
				x = x->next;
				last = last->next;
			}
			else
			{
				last->next = y;
				y = y->next;
				last = last->next;
			}
		}
		if (x != nullptr) {
			last->next = x;
		}
		if (y != nullptr) {
			last->next = y;
		}
		return temp->next;

	}

	void merge_sort(Account** headref) { //Merge sort to sort users bu age
		Account* head = *headref;
		Account* a;
		Account* b;
		if ((head == nullptr) || (head->next == nullptr)) {

			return;

		}

		mid_Node(head, &a, &b);
		merge_sort(&a);
		merge_sort(&b);
		*headref = merge(a, b);

	}

	bool login() { //Logs in the user on the app
		
		cout << "Enter your username :" << endl;
		cin >> Username;
		cout << "Enter your password :" << endl;
		cin >> Password;
		Account* temp = head;
		while (temp != NULL) {
			if (temp->username == Username /*&& temp->password == Password*/) {
				 isloginuser=temp->username ;
				cout << "Logged in successfuly!" << endl;
				return true;
			}
			
			temp = temp->next;
		}
		
		cout << "Invalid Account info!" << endl;
		isloginuser = " ";
		return false;
			
	}
	
	void createPost() { //Uploads a post
		post* temp = new post;
	
		string filename;
		cout << "Please enter a caption :" << endl;
		cin.ignore();
		getline(cin, temp->caption);
		cout << "Please enter a location :" << endl;
		cin >> temp->location;
		if (Head == NULL) {
			Head = Tail = temp;
		}
		else {
			Tail->next = temp;
			Tail = temp;
		}
		filename = isloginuser + "_Posts.txt";
		fstream myfile;
		myfile.open(filename, ios::app);
		if (myfile.is_open()) {
			myfile << left << setw(7) << ((rand() % 1000) + 10);
			myfile << left << setw(12) << temp->location;
			myfile << left << temp->caption << endl;
			myfile.close();
		}
		
		cout << "New post created !" << endl;
    }

	void postsDisplay() { //Displays current posts
		int x = 1;
		cout << endl;
		post* temp = Head;
		while (temp != NULL) {
			cout << "---Post " << x << "---" << endl;
			cout << "Location :" << temp->location << endl;
			cout << "Caption :" << temp->caption << endl;
			temp = temp->next;
			x++;
		}
	}

	int menu() {
	int option=0;
	int count = 1;
	string filename1 = isloginuser + "_Inbox.txt";
	string filename2 = isloginuser + "_Posts.txt";
	string username, password, username1, username2, Uid;
	int x;
	fstream fin;

	do {
		
		
		cout << endl;
		cout << "----------------User MENU----------------" << endl;
		cout << endl;
		cout << "     Press 1 to delete account." << endl;
		cout << "     Press 2 to display." << endl;
		cout << "     Press 3 to send message." << endl;
		cout << "     Press 4 to delete message." << endl;
		cout << "     Press 5 to sort users by age." << endl;
		cout << "     Press 6 to create post." << endl;
		cout << "     Press 0 to exit." << endl;
		cout << endl;
		cout << "------------------------------------------" << endl;
		cout << endl;
		cout << "Your choice :";
		cin >> option;
		cout << endl;
		switch (option)
		{
		case 1:
			if(ifExist(isloginuser)) {
				cout << "Enter the password :" << endl;
				cin >> password;
				deleteAccount(password);
				deleteFromFile();
				remove(filename1.c_str());
				remove(filename2.c_str());
				Head = NULL;
			}
			else {
				cout << "Account not present" << endl;
			}
			break;
		case 2:
			display();
			break;
		
		case 3:
			sendMessage();
			break;

		case 4:
			cout << "Enter reciever's username :" << endl;
			cin >> username2;
			cout << "Please enter the Unique id to be delted : ";
			cin >> Uid;

			if(ifExist(isloginuser) && ifExist(username2)) {
				
				deleteMessageS(Uid);
				deleteMessageR(Uid, username2);
			}
			else {
				cout << "Invalid Account!" << endl;
			}
			break;
		
	
		case 5:
			merge_sort(&head);
			cout << "Accounts sorted by age!" << endl;
			break;
		case 6:
			
			createPost();
			
			break;
		
		}
	} while (option != 0);

	return 0;
}
	
	~User() {
		
	}
};