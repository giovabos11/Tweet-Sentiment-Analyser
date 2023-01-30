//
// Created by mark on 6/2/2021.
//

#include "DSString.h"

/**
 * Constructors
 **/

DSString::DSString() {
    // Set char pointer to null pointer
    this->s = nullptr;
}
DSString::DSString(const char* arg) {
    // If arg is null pointer
    if (arg == nullptr) {
        // Set char pointer to null pointer too
        s = nullptr;
    }
    // If arg is not a null pointer
    else {
        // Allocate new memory for this char pointer
        s = new char[strlen(arg) + 1];

        // Copy the contents from arg
        strcpy(s, arg);
    }
}
DSString::DSString(const DSString& arg) {
    // Allocate new memory for the char pointer
    s = new char[strlen(arg.s) + 1];

    // Copy the contents from arg
    strcpy(s, arg.s);
}
DSString::~DSString() {
    // If char pointer is not already a null pointer
    if (s != nullptr) {
        // Delete char pointer
        delete[] s;
    }
}

/**
 * Assignment operator
 **/

DSString& DSString::operator= (const char* arg) {
    // Delete char pointer
    delete[] s;
    // Allocate enough new memory for this char pointer
    s = new char[strlen(arg)+1];
    // Copy contents from arg
    strcpy(s, arg);
    // Return this object
    return *this;
}
DSString& DSString::operator= (const DSString& arg) {
    // If this object is not the same as the argument
    if (this != &arg) {
        // Delete char pointer
        delete[] s;
        // Allocate enough new memory for this char pointer
        s = new char[strlen(arg.s)+1];
        // Copy contents from arg
        strcpy(s, arg.s);
    }

    // Return this object
    return *this;
}

/**
 * String concat
 **/

DSString DSString::operator+ (const DSString& arg) {
    // Declare a temporary variable to return it later
    DSString temp;
    // Allocate enough new memory for the temporary variable char pointer
    temp.s = new char[strlen(arg.s)+strlen(this->s)+1];
    // Copy contents from this char pointer to temporary variable
    strcpy(temp.s, this->s);
    // Concatenate contents from arg to temporary variable
    strcat(temp.s, arg.s);
    // Return temporary variable
    return temp;
}

/**
 * Relational operators
 **/

bool DSString::operator== (const char* arg) const {
    bool flag = false;

    // If comparison is 0, the char pointer and this object are equal
    if (strcmp(s, arg) == 0) {
        flag = true;
    }

    // Return boolean value
    return flag;
}
bool DSString::operator== (const DSString& arg) const {
    bool flag = false;

    // If comparison is 0, the DSStrings are equal
    if (strcmp(s, arg.s) == 0) {
        flag = true;
    }

    // Return boolean value
    return flag;
}
bool DSString::operator> (const DSString& arg) const{
    bool flag = false;

    // If comparison is greater than 0, the char pointer
    // is greater than this object
    if (strcmp(s, arg.s) > 0) {
        flag = true;
    }

    // Return boolean value
    return flag;
}
bool DSString::operator> (const char* arg) const {
    bool flag = false;

    // If comparison is greater than 0, the char pointer
    // is greater than the argument
    if (strcmp(s, arg) > 0) {
        flag = true;
    }

    // Return boolean value
    return flag;
}

/**
 * Subscript operator
 **/

char& DSString::operator[] (const int n) {
    // Return char at index n
    return s[n];
}

/**
 * Get string length
 **/

int DSString::getLength() const {
    // Return the length of the char pointer
    return strlen(s);
}

/**
 * Get substring
 **/

DSString DSString::substring(int start, int numChars) {
    // Create a temporary variable to store the substring
    char sub[numChars+1];
    // Declare index of substring
    int i;

    // Strip the substring from the char pointer and store it
    for (i = start; i < numChars + start; i++) {
        sub[i - start] = s[i];
    }

    // Add a null char at the end
    sub[(i - start)] = '\0';

    // Declare a temporary variable to return it later, containing
    // the substring
    DSString temp(sub);

    // Return temporary variable
    return temp;
}

/**
 * Parse to C-String
 **/

char* DSString::c_str() const {
    // Return char pointer
    return s;
}

/**
 * Output string
 **/

ostream& operator<< (ostream& out, const DSString& arg) {
    // Output the contents of the argument
    out << arg.s;
    // Return the output stream
    return out;
}

/**
 * Find
 **/

int DSString::find(const char arg) const {
    // Declare a char pointer which points to the first occurrence
    // of arg (if any)
    char* p = strchr(this->s, arg);
    // Initialize default index (not found)
    int i = -1;

    // If p pointer is not null (arg is found)
    if (p != NULL) {
        // Calculate index position
        i = p - (this->s);
    }

    // Return index
    return i;
}
int DSString::find(const char* arg) const {
    // Declare a char pointer which points to the first occurrence
    // of arg (if any)
    char* p = strstr(this->s, arg);
    // Initialize default index (not found)
    int i = -1;

    // If p pointer is not null (arg is found)
    if (p != NULL) {
        // Calculate index position
        i = p - (this->s);
    }

    // Return index
    return i;
}
int DSString::find(const DSString& arg) const {
    // Declare a char pointer which points to the first occurrence
    // of arg (if any)
    char* p = strstr(this->s, arg.s);
    // Initialize default index (not found)
    int i = -1;

    // If p pointer is not null (arg is found)
    if (p != NULL) {
        // Calculate index position
        i = p - (this->s);
    }

    // Return index
    return i;
}

/**
 * Modifiers
 **/

void DSString::toLower() {
    // For each character in the character pointer
    for (int i = 0; i < getLength(); i++) {
        // Change current character to lower case
        s[i] = tolower(s[i]);
    }
}
void DSString::toUpper() {
    // For each character in the character pointer
    for (int i = 0; i < getLength(); i++) {
        // Change current character to upper case
        s[i] = toupper(s[i]);
    }
}
int DSString::clean() {
    // Allocate enough new memory to store the new cleared char pointer
    char* clear = new char[getLength()+1];
    // Initialize indexes
    int j = 0, i;

    // For every char in this char pointer
    for (i = 0; i < getLength(); i++) {
        // If char is alphanumeric
        if (isalnum(s[i]) || s[i] == ' ') {
            // Check for repeated spaces if index is not 0
            if (j != 0) {
                if (!(s[i] == ' ' && clear[j - 1] == ' ')) {
                    // Add char to clear if no repeated spaces
                    clear[j] = s[i];
                    j++;
                }
            }
            // Otherwise, just add char to clear
            else {
                clear[j] = s[i];
                j++;
            }
        }
    }

    // Add a null char at the end of clear
    clear[j] = '\0';

    // Delete this char pointer
    delete[] s;
    // Set this char pointer to the cleared char pointer
    s = clear;

    // Return length of the cleared char pointer
    return j;
}