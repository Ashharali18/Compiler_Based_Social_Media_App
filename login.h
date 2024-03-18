#include "User.h"
#include<string>
#include<fstream>
#include<iostream>
#include <iomanip>
using namespace std;
class Login {
private:
    string Username;
    string Password;
    string Role;
    User* current_user = new User;
    
public:
 
  
    Login() {
        Username = "";
        Password = "";
        Role = " ";
        current_user->loadDataFromFile();
       
    }
    Login(string U, string P, string R) {
        Username = U;
        Password = P;
        Role = R;

    }
    void setUsername(string U) {
        Username = U;
    }
    string getUsername() {
        return Username;
    }
    void setPassword(string P) {
        Password = P;
    }
    string getPassword() {
        return Password;
    }

  
    bool  signIn(string un, string pw)
    {
        ifstream Log;
        Log.open("logindata.txt", ios::in);
        
        while (1)
        {
            if (Log >> Username >> Password) {
                cout << Username << endl;
                if (un == Username && pw == Password)
                {
                    cout << "Welcome User!" << endl;
                   
                    return 1;
                }
            }
            else {
                break;
            }
        }
        Log.close();
        cout << "Invalid Username or Password!" << endl;
        return 0;
    }

  

    int menu() {
        int op;
        string username, password;
        

        do {
        
            cout << endl;
            cout << "----------------LOGIN MENU----------------" << endl;
            cout << endl;
            cout << "     Press 1 to Sign up." << endl;
            cout << "     Press 2 to Sign in." << endl;
            cout << "     Press 0 to exit." << endl;
            cout << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Your choice :";
            cin >> op;
            switch (op) {
            case 1:
                current_user->createAccount();

                break;
            case 2:
             
              
                if (current_user->login()) {
                    current_user->menu();
                 
                }
               

                break;


            }
        } while (op != 0);
        return 0;
    }

    ~Login(){
        delete current_user;
    }
};
