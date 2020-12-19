// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "LineManager.h"


using namespace std;

LineManager::LineManager(const string& filename, vector<Workstation*>& stations, vector<CustomerOrder>& orders) {
    ifstream file(filename);
    string workstationInit;

    if (!file)
        throw std::string("Cannot open file for assembly line");

    // Record each workstation that has a preceding workstation in the assembly line
    vector<bool> hasPrecedingStation(stations.size(), false);

    // Link each `Workstation` object together to form the assembly line
    while (getline(file, workstationInit)) {
        Utilities workstationUtil;
        size_t next_pos = 0;
        bool more = true;
        string stationToken = workstationUtil.extractToken(workstationInit, next_pos, more);
        string next_stationToken = workstationUtil.extractToken(workstationInit, next_pos, more);

        if (!stationToken.empty() && !next_stationToken.empty()) {
            auto workstation = find_if(stations.begin(), stations.end(), [stationToken](Workstation* pWorkstation) {
               return pWorkstation->getItemName() == stationToken;
            });
            // Find the next workstation
            bool found = false;
            Workstation* next_workstation = nullptr;
            for (size_t i = 0; i < stations.size() && !found; i++) {
                if (stations[i]->getItemName() == next_stationToken) {
                    // This workstation has a preceding workstation
                    hasPrecedingStation[i] = true;
                    next_workstation = stations[i];
                    found = true;
                }
            }
            // Set the next workstation for the current one
            if (workstation != stations.end() && next_workstation != nullptr) {
                (*workstation)->setNextStation((*next_workstation));
            }
        }
    }
    // Move `CustomerOrder` objects to `ToBeFilled` queue
    move(orders.begin(), orders.end(), back_inserter(ToBeFilled));
    // Copy all the `Workstation` objects into the `AssemblyLine` container
    copy(stations.begin(), stations.end(), back_inserter(AssemblyLine));
    // Track the original number of orders
    m_cntCustomerOrder = static_cast<unsigned int>(ToBeFilled.size());
    // Find the start of the assembly line
    bool found = false;
    for (size_t i = 0; i < hasPrecedingStation.size() && !found; i++) {
        if (!hasPrecedingStation[i]) {
            m_firstStationIndex = static_cast<unsigned int>(i);
            found = true;
        }
    }
}

bool LineManager::run(ostream& os) {
    static unsigned int count = 1;

    os << "Line Manager Iteration: " << count++ << endl;

    // Move the `CustomerOrder` at the front of the queue onto the starting point of the `AssemblyLine`
    if (!ToBeFilled.empty()) {
        (*AssemblyLine[m_firstStationIndex]) += move(ToBeFilled.front());
        ToBeFilled.pop_front();
    }
    // Run one cycle of the station's process
    for (Workstation* ws : AssemblyLine) {
        ws->runProcess(os);
    }
    // Move the `CustomerOrder` objects down the line
    for (Workstation* ws : AssemblyLine) {
        CustomerOrder order;
        // If the order at the front of the queue is completed, move it into `Completed` queue
        if (ws->getIfCompleted(order))
            Completed.push_back(move(order));
        else
            ws->moveOrder();
    }
    // Check if all customer orders have been filled
    if (Completed.size() == m_cntCustomerOrder)
        return true;
    else
        return false;
}

void LineManager::displayCompletedOrders(ostream& os) const {
    for (auto& order : Completed) {
        order.display(os);
    }
}

void LineManager::displayStations() const {
    for (auto workstation : AssemblyLine) {
        workstation->display(cout);
    }
}

void LineManager::displayStationsSorted() const {
    Workstation* ws = AssemblyLine[m_firstStationIndex];
    while (ws) {
        ws->display(cout);
        ws = const_cast<Workstation*>(ws->getNextStation());
    }
}