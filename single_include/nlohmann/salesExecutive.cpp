#include "json.hpp"
#include <bits/stdc++.h>

using namespace std;
using json = nlohmann::json;

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
        cout << "Enter name of motor part:\n";
        cin >> name1;
        cout << "Enter id of motor part:\n";
        cin >> id1;
        cout << "Set price of motor part:\n";
        cin >> price1;
        cout << "Enter number of motor parts to be added initially:\n";
        cin >> num_parts1;
        int x1 = rand() % (10) + 1;
        int y1 = rand() % (20) + 1;
        part.push_back({{"motor_id", id1}, {"number of parts", num_parts1}, {"rack location", {x1, y1}}, {"part-name", name1}, {"price", price1}});
        ofstream file1("parts.json");
        file1 << part.dump(4);
        cout << name1 << " added successfully in the stock\n";
    }
    void getList(bool pr)
    {
        settingThreshold();
        cout << "These are the parts to be restocked:\n";
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
                    cout << mid7 << " " << sname << " " << pt << "\n";
                else
                    vid.insert({mid7, pt});
            }
        }
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
        cout << "stock updated successfully\n";
    }
};
