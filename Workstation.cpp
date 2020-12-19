// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Workstation.h"


using namespace std;

Workstation::Workstation(const std::string& workstationInit) : Station(workstationInit) {
    m_pNextStation = nullptr;
}

void Workstation::runProcess(ostream& out) {
    if (!m_orders.empty()) {
        m_orders.front().fillItem(*this, out);
    }
}

bool Workstation::moveOrder() {
    if (!m_orders.empty()) {
        if (m_orders.front().isItemFilled(getItemName())) {
            *m_pNextStation += move(m_orders.front());
            m_orders.pop_front();
            return true;
        }
    }

    return false;
}

void Workstation::setNextStation(Station& station) {
    m_pNextStation = dynamic_cast<Workstation*>(addressof(station));
}

const Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
    if (!m_orders.empty()) {
        if (m_orders.front().isOrderFilled()) {
            order = move(m_orders.front());
            m_orders.pop_front();
            return true;
        }
    }

    return false;
}

void Workstation::display(ostream& out) const {
    out << getItemName() << " --> ";
    if (m_pNextStation != nullptr)
        out << m_pNextStation->getItemName();
    else
        out << "END OF LINE";
    out << endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& order) {
    m_orders.push_back(move(order));

    return *this;
}