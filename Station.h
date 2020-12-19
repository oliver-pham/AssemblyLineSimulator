// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 14, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>


class Station {
    unsigned int m_id = 0u;
    std::string m_itemName;
    std::string m_desc;
    unsigned int m_serialNumber = 0u;
    unsigned int m_quantity = 0u;
    static size_t m_widthField;
    static unsigned int id_generator;
public:
    explicit Station(const std::string& orderInit);
    const std::string& getItemName() const;
    unsigned int getNextSerialNumber();
    unsigned int getQuantity() const;
    void updateQuantity();
    virtual void display(std::ostream& os, bool full) const;

};

#endif // SDDS_STATION_H
