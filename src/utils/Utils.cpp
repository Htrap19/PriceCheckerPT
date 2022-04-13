//
// Created by htrap19 on 4/13/22.
//

#include "Utils.h"
#include <algorithm>

namespace PC
{
    void Utils::RemoveEmptySpace(std::string& str)
    {
        str.erase(std::remove_if(str.begin(),
                                 str.end(),
                                 [](unsigned char x) { return std::isspace(x) || x == '(' || x == ')'; }), str.end());
    }
}