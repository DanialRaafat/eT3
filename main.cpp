#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main(){
    struct  delivery {
        int id;
        string area;
        int priority;
        double weight;
        bool valid;
    };
    vector<delivery> D;
    ifstream input("Data.txt");
    string line;
    getline(input, line);
    while (getline(input, line)) {
        stringstream ss(line);
        string id,area,priority,weight;
        getline(ss, id, ',');
        getline(ss, area, ',');
        getline(ss, priority, ',');
        getline(ss, weight, ',');
        delivery d;
        d.id = stoi(id);
        d.area = area;
        d.priority = stoi(priority);
        d.weight = stod(weight);
        d.valid=true;
        D.push_back(d);
    }

    sort(D.begin(), D.end(), [](const delivery& a, const delivery& b) {
        return a.priority < b.priority;
    });
    map<string, vector<delivery*>> areas;
    for ( delivery& d : D) {
        areas[d.area].push_back(&d);
    }
    int shipmentNumber = 1;
    for (delivery& d : D) {
        if (!d.valid) {
            continue;
        }
        if (d.weight > 10) {
            d.valid = false;
            continue;
        }
        double currentWeight = d.weight;
        cout << "Shipment " << shipmentNumber << ": ";
        cout << d.id << " ";
        d.valid = false;
        for (delivery* other_delivery : areas[d.area]) {
            if (!other_delivery->valid) {
                continue;
            }
            if (currentWeight +other_delivery->weight<=10) {
                currentWeight += other_delivery->weight;
                other_delivery->valid = false;
                cout << other_delivery->id << " ";
            }
        }
        cout << "(Weight: " << currentWeight << " kg)" << endl;

        shipmentNumber++;
    }

}