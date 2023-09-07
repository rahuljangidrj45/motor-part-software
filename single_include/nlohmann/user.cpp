#include "json.hpp"
#include <bits/stdc++.h>
#include "project.cpp"
using namespace std;
using json = nlohmann::json;

class User
{
    string password;

  public:
    string username, usertype;

    void signUp()
    {
        cout << "please enter your sign-up criteria:\nusername : ";
        cin >> username;
        cout << "password : ";
        cin >> password;
        cout << "usertype (owner,shopkeeper,sales executive-select any one) : ";
        cin >> usertype;
        id = rand();
        data.push_back({{"user_id", id}, {"username", username}, {"password", password}, {"usertype", usertype}});
        ofstream file("details.json");
        file << data.dump(4);
    }
    pair<string, bool> authentication(string s)
    {
        cout << "please enter your " << s << "sign-in criteria:\nusername : ";
        cin >> username;
        cout << "password : ";
        cin >> password;
        ifstream in("details.json");
        json filee = json::parse(in);
        string utyp;
        for (auto& user : filee)
        {
            if (user["username"] == username && user["password"] == password)
            {
                cout << "Welcome, " << username << "!\n";
                utyp = user["usertype"];
                cout << utyp;
                return {utyp, true};
            }
        }
        return {utyp, false};
    }
};
