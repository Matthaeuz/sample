#include "StringUtils.h"

/*
To remove spaces
Example:
" Hello, world! " will be returned as "Hello, world!"
*/
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}
