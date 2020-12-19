// Name: Phu Thong Pham
// Seneca Student ID: 106455199
// Seneca email: ptpham4@myseneca.ca
// Date of completion: Nov 14, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include <string>
#include <exception>
#include "Utilities.h"

using namespace std;


char Utilities::m_delimiter = '\0';

string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
    string whitespace = " \f\n\r\t\v";
    string token;

    if (more) {
        auto pos = str.find(m_delimiter, next_pos);
        if (pos != string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            // Move to the next token
            next_pos = pos + 1;
            // Allow to extract the next field
            more = true;
        }
        else {
            token = str.substr(next_pos);
            // Signal end of record
            more = false;
        }
        // Remove leading white space
        pos = token.find_first_not_of(whitespace);
        if (pos != string::npos)
            token.erase(0, pos);
        else
            throw invalid_argument("Token Not Found");
        // Remove trailing white space
        pos = token.find_last_not_of(whitespace);
        if (token.length() - pos - 1 > 0)
            token.erase(pos + 1, token.length() - pos - 1);
        if (token.length() > m_widthField)
            m_widthField = token.length();
    }

    return token;
}

void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
    return m_widthField;
}

void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
    return m_delimiter;
}