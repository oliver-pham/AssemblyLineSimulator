// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include "CustomerOrder.h"
#include "Workstation.h"


class LineManager {
    std::vector<Workstation*> AssemblyLine;
    std::deque<CustomerOrder> ToBeFilled;
    std::deque<CustomerOrder> Completed;
    unsigned int m_cntCustomerOrder = 0u;
    unsigned int m_firstStationIndex = 0u;
public:
    LineManager(const std::string& filename, std::vector<Workstation*>& assemblyLine, std::vector<CustomerOrder>& toBeFilled);
    bool run(std::ostream& os);
    void displayCompletedOrders(std::ostream& os) const;
    void displayStations() const;
    void displayStationsSorted() const;
};


#endif // SDDS_LINEMANAGER_H
