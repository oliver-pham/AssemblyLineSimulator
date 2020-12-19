// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 20, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"


struct Item {
    std::string m_itemName;
    unsigned int m_serialNumber = 0;
    bool m_isFilled = false;

    explicit Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
    std::string m_name;
    std::string m_product;
    unsigned int m_cntItem = 0u;
    Item** m_lstItem = nullptr;
    static size_t m_widthField;
public:
    CustomerOrder() = default;
    explicit CustomerOrder(const std::string& custOrderInit);
    CustomerOrder(const CustomerOrder& customerOrder);
    CustomerOrder& operator=(const CustomerOrder& customerOrder) = delete;
    CustomerOrder(CustomerOrder&& customerOrder) noexcept;
    CustomerOrder& operator=(CustomerOrder&& customerOrder) noexcept;
    bool isOrderFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
    ~CustomerOrder();
};


#endif // SDDS_CUSTOMERORDER_H
