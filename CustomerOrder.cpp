// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 20, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(const string& orderInit) {
    Utilities orderUtil;
    size_t next_pos = 0;
    bool more = true;

    try {
        m_name = orderUtil.extractToken(orderInit, next_pos, more);
        m_product = orderUtil.extractToken(orderInit, next_pos, more);
        size_t start_of_products = next_pos;
        // Count the number of items
        while (more) {
            if (orderUtil.extractToken(orderInit, next_pos, more).length())
                m_cntItem++;
        }
        // Store all items (if any)
        if (m_cntItem) {
            // Reset the tracker
            next_pos = start_of_products;
            more = true;
            // Allocate an array of pointers
            m_lstItem = new Item*[m_cntItem];
        }
        // Allocate objects of type `Item`
        start_of_products = 0;
        while (more) {
            m_lstItem[start_of_products++] = new Item(orderUtil.extractToken(orderInit, next_pos, more));
        }
        if (m_widthField < orderUtil.getFieldWidth())
            m_widthField = orderUtil.getFieldWidth();
    }
    catch (invalid_argument& tokenError) {
        cout << "Exception: " << tokenError.what() << endl;
    }
    catch (...) {
        cout << "Unhandled Exception!" << endl;
    }
}

CustomerOrder::CustomerOrder(const CustomerOrder& customerOrder) {
    throw "Invalid Operation";
}

CustomerOrder::CustomerOrder(CustomerOrder&& customerOrder) noexcept {
    *this = move(customerOrder);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& customerOrder) noexcept {
    if (this != &customerOrder) {
        // Deallocate existing resources
        for (unsigned int i = 0u; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete [] m_lstItem;
        // Move resources
        m_name = customerOrder.m_name;
        customerOrder.m_name.clear();
        m_product = customerOrder.m_product;
        customerOrder.m_product.clear();
        m_cntItem = customerOrder.m_cntItem;
        customerOrder.m_cntItem = 0u;
        m_lstItem = customerOrder.m_lstItem;
        customerOrder.m_lstItem = nullptr;
    }

    return *this;
}

bool CustomerOrder::isOrderFilled() const {
    bool filled = true;
    for (unsigned int i = 0u; i < m_cntItem && filled; i++) {
        filled = m_lstItem[i]->m_isFilled;
    }

    return filled;
}

bool CustomerOrder::isItemFilled(const string& itemName) const {
    bool filled = true;
    for (unsigned int i = 0u; i < m_cntItem && filled; i++) {
        if (m_lstItem[i]->m_itemName == itemName)
            filled = m_lstItem[i]->m_isFilled;
    }

    return filled;
}

void CustomerOrder::fillItem(Station& station, ostream& os) {
    for (unsigned int i = 0u; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_itemName == station.getItemName()) {
            if (station.getQuantity() > 0) {
                station.updateQuantity();
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name << ", " << m_product;
                os << " [" << m_lstItem[i]->m_itemName << "]";
            }
            else {
                os << "    Unable to fill " << m_name;
                os << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]";
            }
            os << endl;
        }
    }
}

void CustomerOrder::display(ostream& os) const {
    os << m_name << " - " << m_product << endl;
    for (unsigned int i = 0u; i < m_cntItem; i++) {
        os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] " << setfill(' ');
        os << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - ";
        os << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << endl;
    }
}

CustomerOrder::~CustomerOrder() {
    for (unsigned int i = 0u; i < m_cntItem; i++) {
        delete m_lstItem[i];
    }

    delete [] m_lstItem;
}
