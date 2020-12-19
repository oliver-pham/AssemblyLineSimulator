// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 14, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>


class Utilities {
    size_t m_widthField = 1;
    static char m_delimiter;
public:
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    static void setDelimiter(char newDelimiter);
    static char getDelimiter();
};

#endif // SDDS_UTILITIES_H
