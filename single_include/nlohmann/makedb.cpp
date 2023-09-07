#include "json.hpp"

#include <bits/stdc++.h>
using namespace std;
using json = nlohmann::json;

json salesDetails;
json part;

vector<string> partName = {"Engine block",
                           "Engine Valves",
                           "Oil Pan",
                           "Combustion chamber",
                           "Cylinder Head",
                           "Manifold",
                           "Crank Shaft",
                           "Camshaft",
                           "Timing belt",
                           "Spark Plugs",
                           "Connecting Rod",
                           "Cylinder Liner",
                           "Piston Ring",
                           "Distributor",
                           "Oil filter",
                           "Camshaft pulley",
                           "Head gasket",
                           "Flywheels",
                           "Water pump",
                           "Crank Case"};
vector<pair<int, pair<int, int>>> det;
void makePart()
{
    int n = partName.size();
    int lb = 100000, ub = 500000;
    int rl = 1, rh = 10;
    int cl = 1, ch = 20;
    int lp = 1000, hp = 10000;
    for (int i = 0; i < 200; i++)
    {
        int motor_id = rand() % (ub - lb + 1) + lb;
        int x = rand() % (rh - rl + 1) + rl;
        int y = rand() % (ch - cl + 1) + cl;
        int num_part = rand() % (ch - cl + 1) + cl;
        int price = rand() % (hp - lp + 1) + lp;
        string name = partName[i % n];
        det.push_back({motor_id, {num_part, price}});
        part.push_back({{"motor_id", motor_id}, {"number of parts", num_part}, {"rack location", {x, y}}, {"part-name", name}, {"price", price}});
        ofstream file("parts.json");
        file << part.dump(4);
    }
}

void makeDetails()
{
    for (int i = 0; i < 200; i++)
    {
        int motor_id = det[i].first;
        int num_part = det[i].second.first;
        int price = det[i].second.second;
        int part_sold = rand() % num_part;
        long int totalSales = part_sold * price;
        int weeks = rand() % 4 + 1;
        int current_daySale = (rand() % (num_part) + 1) * price;
        salesDetails.push_back({{"motor_id", motor_id}, {"sold", part_sold}, {"total-sales", totalSales}, {"price per part", price}, {"weeks", weeks}, {"current day sale", current_daySale}});
        ofstream file("sales.json");
        file << salesDetails.dump(4);
    }
}
