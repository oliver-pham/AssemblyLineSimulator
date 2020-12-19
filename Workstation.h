// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"


class Workstation : public Station {
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation;
public:
    explicit Workstation(const std::string& workstationInit);
    Workstation(const Workstation& workstation) = delete;
    Workstation& operator=(const Workstation& workstation) = delete;
    Workstation(Workstation&& workstation) = delete;
    Workstation& operator=(Workstation&& workstation) = delete;
    void runProcess(std::ostream& out);
    bool moveOrder();
    void setNextStation(Station& station);
    const Workstation* getNextStation() const;
    bool getIfCompleted(CustomerOrder& order);
    void display(std::ostream& out) const;
    Workstation& operator+=(CustomerOrder&& order);
};


#endif // SDDS_WORKSTATION_H
