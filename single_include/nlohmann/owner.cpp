#include "json.hpp"
#include <bits/stdc++.h>

using namespace std;
using json = nlohmann::json;
#include "user.cpp"

class owner : public User
{
  public:
    int m_id3;
    int menu()
    {
        cout << "what do you want:\n";
        cout << "1. search motor part\n";
        cout << "2. checking current stock\n";
        cout << "3. setting threshold\n";
        cout << "4. adding a new motor part\n";
        cout << "5. getting list of parts to be restocked\n";
        cout << "6. checking sales for today\n";
        cout << "7. billing of customer\n";
        cout << "8. update stock\n";
        cout << "9. exit\n";
        int choice;
        cin >> choice;
        return choice;
    }
    bool searchPart()
    {
        cout << "Enter motor part id:";
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
                string name = part["part-name"];
                cout << "motor part name : " << name3 << "\n"
                     << "Number of parts left : " << x3 << "\n"
                     << "rack location : "
                     << "row:" << r3 << " "
                     << "column:" << y3 << "\n";
                return true;
            }
        }
        cout<<"Oops no such motor part found\n";
        return false;
    }

    void checkStock()
    {
        ifstream in("parts.json");
        json filee = json::parse(in);
        cout << "Current stocks is as follow:\n\n";
        for (auto& part : filee)
        {
            int x2 = part["number of parts"];
            int m_id2 = part["motor_id"];
            string name2 = part["part-name"];
            cout << "motor part name : " << name2 << "\n"
                 << "Number of parts left : " << x2 << "\n"
                 << "motor part id : " << m_id2 << "\n\n";
        }
    }

    void checkSales(){
        long long ts(0);
        ifstream in("sales.json");
        json filee = json::parse(in);
        json j4=filee;
        cout<<"current day sales is as follow:\n";
        for(int i=0;i<200;i++){
            int cs=j4[i]["current day sale"];
            int mid34=j4[i]["motor_id"];
            if(cs){
                cout<<cs<<" rupees for motor id "<<mid34<<" today\n";
                ts += cs;
            }
        }
        cout<<"Total sales for today : "<<ts<<endl;
    }
};
