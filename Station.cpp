// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 14, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#include "Utilities.h"
#include "Station.h"

using namespace std;

size_t Station::m_widthField = 0u;
unsigned int Station::id_generator = 0u;

Station::Station(const string& stationInit) {
    Utilities stationUtil;
    size_t next_pos = 0;
    bool more = true;

    try {
        m_itemName = stationUtil.extractToken(stationInit, next_pos, more);
        m_serialNumber = stoi(stationUtil.extractToken(stationInit, next_pos, more));
        m_quantity = stoi(stationUtil.extractToken(stationInit, next_pos, more));
        if (m_widthField < stationUtil.getFieldWidth())
            m_widthField = stationUtil.getFieldWidth();
        m_desc = stationUtil.extractToken(stationInit, next_pos, more);
        m_id = ++id_generator;
    }
    catch (invalid_argument& tokenError) {
        cout << "Exception: " << tokenError.what() << endl;
    }
    catch (...) {
        cout << "Unhandled Exception!" << endl;
    }

}

const string& Station::getItemName() const {
    return m_itemName;
}

unsigned int Station::getNextSerialNumber() {
    return m_serialNumber++;
}

unsigned int Station::getQuantity() const {
    return m_quantity;
}

void Station::updateQuantity() {
    if (m_quantity > 0)
        m_quantity--;
}

void Station::display(ostream& os, bool full) const {
    os << "[" << setw(3) << setfill('0') << right << m_id << "] " << setfill(' ');
    os << "Item: " << setw(m_widthField) << left << (m_itemName.empty() ? "" : m_itemName) << " ";
    os << "[" << setw(6) << setfill('0') << right << m_serialNumber << "]" << setfill(' ');
    if (full) {
        os << " Quantity: " << setw(m_widthField) << left << m_quantity;
        os << " Description: " << left << (m_desc.empty() ? "" : m_desc);
    }
    os << endl;
}