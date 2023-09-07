
#include <bits/stdc++.h>

using namespace std;
using json = nlohmann::json;


class shopKeeper : public owner
{
  public:
    int m_id11;
    map<int, int> th;
    int nos;
    void billing(int mid)
    {
        cout << "Enter number of parts to be sold with id " << mid << " : ";
        cin >> nos;
        ifstream in("sales.json");
        json filee = json::parse(in);
        json j67 = filee;
        ifstream inn("parts.json");
        json filee1 = json::parse(inn);
        json j68 = filee1;
        for (int i=0;i<200;i++)
        {
            int m_id = j67[i]["motor_id"];
            if (m_id11 == m_id)
            {
                int sd = j67[i]["sold"];
                int cps = j68[i]["number of parts"];
                j68[i]["number of parts"]=cps-nos;
                nos += sd;
                j67[i]["sold"]=nos;
                int price = j67[i]["price per part"];
                int sl = j67[i]["total-sales"];
                int newSale = sl + nos * price;
                j67[i]["total-sales"]=newSale;
                j67[i]["current day sale"]=nos * price;
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
