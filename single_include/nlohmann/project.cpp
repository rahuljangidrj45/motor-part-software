#include "json.hpp"
#include <bits/stdc++.h>
#include "makedb.cpp"

using namespace std;
using json = nlohmann::json;


json data;
int id;

class User
{
    string password;

  public:
    string username, usertype;

    void signUp()
    {
        cout << "\t\t\t\t\t\t\t\tplease enter your sign-up criteria:\n\t\t\t\t\t\t\t\tusername : ";
        cin >> username;
        cout << "\t\t\t\t\t\t\t\tpassword : ";
        cin >> password;
        cout << "\t\t\t\t\t\t\t\tusertype (owner,shopkeeper,sales executive-select any one) : ";
        cin >> usertype;
        id = rand();
        data.push_back({{"user_id", id}, {"username", username}, {"password", password}, {"usertype", usertype}});
        ofstream file("details.json");
        file << data.dump(4);
    }
    pair<string, bool> authentication(string s)
    {
        cout << "\t\t\t\t\t\t\t\tplease enter your " << s << "sign-in criteria:\n\t\t\t\t\t\t\t\tusername : ";
        cin >> username;
        cout << "\t\t\t\t\t\t\t\tpassword : ";
        cin >> password;
        ifstream in("details.json");
        json filee = json::parse(in);
        string utyp;
        for (auto& user : filee)
        {
            if (user["username"] == username && user["password"] == password)
            {
                cout << "\t\t\t\t\t\t\t\tWelcome, " << username << "!\n";
                utyp = user["usertype"];
                return {utyp, true};
            }
        }
        return {utyp, false};
    }
};

class owner : public User
{
  public:
    int m_id3;
    int menu()
    {
        cout << "\t\t\t\t\t\t\t\twhat do you want:\n\n";
        cout << "\t\t\t\t\t\t\t\t1. search motor part\n";
        cout << "\t\t\t\t\t\t\t\t2. checking current stock\n";
        cout << "\t\t\t\t\t\t\t\t3. setting threshold\n";
        cout << "\t\t\t\t\t\t\t\t4. adding a new motor part\n";
        cout << "\t\t\t\t\t\t\t\t5. getting list of parts to be restocked\n";
        cout << "\t\t\t\t\t\t\t\t6. checking sales for today\n";
        cout << "\t\t\t\t\t\t\t\t7. billing of customer\n";
        cout << "\t\t\t\t\t\t\t\t8. update stock\n";
        cout << "\t\t\t\t\t\t\t\t9. exit\n";
        int choice;
        cin >> choice;
        return choice;
    }
    bool searchPart()
    {
        cout << "\t\t\t\t\t\t\t\tEnter motor part id:";
        cin >> m_id3;
        ifstream in("parts.json");
        json filee = json::parse(in);
        for (auto& part : filee)
        {
            if (part["motor_id"] == m_id3)
            {
                int x3 = part["number of parts"];
                int r3 = part["rack location"][0];
                int y3 = part["rack location"][1];
                string name3 = part["part-name"];
                cout << "\t\t\t\t\t\t\t\tmotor part name : " << name3 << "\n"
                     << "\t\t\t\t\t\t\t\tNumber of parts left : " << x3 << "\n"
                     << "\t\t\t\t\t\t\t\track location : "
                     << "row:" << r3 << "   "
                     << "column:" << y3 << "\n\n";
                return true;
            }
        }
        cout<<"\t\t\t\t\t\t\t\tOops no such motor part found\n\n";
        return false;
    }

    void checkStock()
    {
        ifstream in("parts.json");
        json filee = json::parse(in);
        cout << "\t\t\t\t\t\t\t\tCurrent stocks is as follow:\n\n";
        cout << "\t\t\t\t\t\t\t\tPart-Name\t\tParts left\t\tPart-ID\n\n";
        for (auto& part : filee)
        {
            int x2 = part["number of parts"];
            int m_id2 = part["motor_id"];
            string name2 = part["part-name"];
            cout <<"\t\t\t\t\t\t\t\t";
            cout << name2 << "\t\t"
                 << x2 << "\t\t"
                 << m_id2 << "\n";
        }
        cout<<"\n";
    }

    void checkSales(){
        long long ts(0);
        ifstream in("sales.json");
        json filee = json::parse(in);
        json j4=filee;
        cout<<"\t\t\t\t\t\t\t\tcurrent day sales is as follow:\n\n";
        for(int i=0;i<200;i++){
            int cs=j4[i]["current day sale"];
            int mid34=j4[i]["motor_id"];
            if(cs){
                cout<<"\t\t\t\t\t\t\t\t"<<cs<<" rupees for motor id "<<mid34<<" today\n";
                ts += cs;
            }
        }
        cout<<"\n";
        cout<<"Total sales for today : "<<ts<<endl<<endl;
    }
};

class shopKeeper : public owner
{
  public:
    int m_id11;
    map<int, int> th;
    int nos34;
    void billing(int mid)
    {
        cout << "\t\t\t\t\t\t\t\tEnter number of parts to be sold with id " << mid << " : ";
        cin >> nos34;
        ifstream in("sales.json");
        json filee = json::parse(in);
        json j67 = filee;
        ifstream inn("parts.json");
        json filee1 = json::parse(inn);
        json j68 = filee1;
        for (int i=0;i<200;i++)
        {
            int m_id = j67[i]["motor_id"];
            if (m_id == mid)
            {
                
                int sd = j67[i]["sold"];
                int cps = j68[i]["number of parts"];
                int pnos=nos34;
                j68[i]["number of parts"]=cps-nos34;
                nos34 += sd;
                j67[i]["sold"]=nos34;
                int price = j67[i]["price per part"];
                int sl = j67[i]["total-sales"];
                int newSale = sl + nos34 * price;
                j67[i]["total-sales"]=newSale;
                int cdsp=j67[i]["current day sale"];
                cdsp += pnos * price;
                j67[i]["current day sale"]=cdsp;
                cout<<"\t\t\t\t\t\t\t\tyour total bill is : "<<pnos*price<<"\n";
                ofstream out("sales.json");
                out << std::setw(4) << j67 << std::endl;
                ofstream out1("parts.json");
                out1 << std::setw(4) << j68 << std::endl;
                break;
            }
                
        }
    }
    void settingThreshold()
    {
        ifstream in("sales.json");
        json filee = json::parse(in);
        for (auto& part : filee)
        {
            int x4 = part["sold"];
            int wks = part["weeks"];
            int m_id32 = part["motor_id"];
            th.insert({m_id32, x4/wks});
        }
    }
};

class salesExecutive : public shopKeeper
{
  public:
    string name1;
    int id1;
    int price1;
    int num_parts1;
    int total_parts = 0;
    map<int, int> vid;
    void addMotorpart()
    {
        cout << "\t\t\t\t\t\t\t\tEnter name of motor part:";
        cin >> name1;
        cout << "\t\t\t\t\t\t\t\tEnter id of motor part:";
        cin >> id1;
        cout << "\t\t\t\t\t\t\t\tSet price of motor part:";
        cin >> price1;
        cout << "\t\t\t\t\t\t\t\tEnter number of motor parts to be added initially:";
        cin >> num_parts1;
        int x1 = rand() % (10) + 1;
        int y1 = rand() % (20) + 1;
        part.push_back({{"motor_id", id1}, {"number of parts", num_parts1}, {"rack location", {x1, y1}}, {"part-name", name1}, {"price", price1}});
        ofstream file1("parts.json");
        file1 << part.dump(4);
        cout << "\t\t\t\t\t\t\t\t"<<name1 << " added successfully in the stock\n\n";
    }
    void getList(bool pr)
    {
        settingThreshold();
        if(pr){
           cout << "\t\t\t\t\t\t\t\tThese are the parts to be restocked:\n\n";
           cout << "\t\t\t\t\t\t\t\tMotor-ID\t\tMotor-PartName\n\n";
        } 
        ifstream in("parts.json");
        json filee = json::parse(in);
        for (auto& part : filee)
        {
            int pt = part["number of parts"];
            int mid7 = part["motor_id"];
            string sname = part["part-name"];
            auto itr = th.find(mid7);
            if (itr != th.end() && itr->second > pt)
            {
                if (pr)
                    cout << mid7 << "\t\t" << sname << "\t\t" << pt << "\n";
                else
                    vid.insert({mid7, pt});
            }
        }
        cout<<"\n";
    }
    void updateStock()
    {
        getList(false);
        ifstream in("parts.json");
        json filee = json::parse(in);
        json j1 = filee;
        for (int i = 0; i < 200; i++)
        {
            int mid8 = j1[i]["motor_id"];
            auto it = vid.find(mid8);
            if (it != vid.end())
            {
                int left = it->second;
                j1[i]["number of parts"] = left + 10;
            }
            ofstream out("parts.json");
            out << std::setw(4) << part << std::endl;
        }
        cout << "\t\t\t\t\t\t\t\tstock updated successfully\n";
    }
};

int main()
{
    makePart();
    makeDetails();
    cout << "\t\t\t\t\t\t\t\t|--------------------------|\n";
    cout << "\t\t\t\t\t\t\t\t| MOTOR PART SHOP SOFTWARE | \n";
    cout << "\t\t\t\t\t\t\t\t|--------------------------|\n";
    while (1)
    {
        cout << "\t\t\t\t\t\t\t\t\t1. Sign up\n";
        cout << "\t\t\t\t\t\t\t\t\t2. Sign in\n";
        cout << "\t\t\t\t\t\t\t\t\t3. Exit\n\n";
        int choice;
        cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            User obj;
            obj.signUp();
            cout << "\t\t\t\t\t\t\t\t\nUser created successfully!\n\n";
        }
        else if (choice == 2)
        {
            User obj;
            pair<string, bool> p = obj.authentication("");
            bool f = p.second;
            string utyp = p.first;
            if (!f)
            {
                while (!f)
                {
                    cout << "\t\t\t\t\t\t\t\t\nInvalid username or password.\n\n";
                    f = obj.authentication("correct ").second;
                }
            }

            if (utyp == "owner")
            {
                owner obj;
                while (choice != 9)
                {
                    choice = obj.menu();
                    if (choice == 1)
                    {
                        bool f = obj.searchPart();
                        if (!f)
                        {
                            cout << "Oops!parts finished\n\n";
                        }
                    }
                    else if (choice == 2)
                    {
                        obj.checkStock();
                    }
                    
                    else if (choice == 6)
                    {
                        obj.checkSales();
                    }
                }
            }
            else if (utyp == "shop-keeper")
            {
                shopKeeper obj;
                while (choice != 9)
                {
                    choice = obj.menu();
                    if (choice == 1)
                    {
                        bool f = obj.searchPart();
                        if (!f)
                        {
                            cout << "Oops!parts finished\n\n";
                        }
                    }
                    else if (choice == 2)
                    {
                        obj.checkStock();
                    }
                    else if (choice == 3)
                    {
                        obj.settingThreshold();
                    }
                    else if (choice == 6)
                    {
                        obj.checkSales();
                    }
                    else if (choice == 7)
                    {
                        int idb;
                        cout<<"\t\t\t\t\t\t\t\tEnter id of motor part for billing:";
                        cin>>idb;
                        obj.billing(idb);
                    }
                }
            }
            else
            {
                salesExecutive obj;
                while (choice != 9)
                {
                    choice = obj.menu();
                    if (choice == 4)
                    {
                        obj.addMotorpart();
                    }
                    else if (choice == 5)
                    {
                        obj.getList(true);
                    }
                    else if (choice == 2)
                    {
                        obj.checkStock();
                    }
                    else if (choice == 8)
                    {
                        obj.updateStock();
                    }
                    else if (choice == 6)
                    {
                        obj.checkSales();
                    }
                }
            }
        }
        else if (choice == 3)
            break;
        else
        {
            cout << "Invalid choice.\n\n";
        }
    }
}
