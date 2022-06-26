//
// Created by htrap19 on 4/13/22.
//

#ifndef PRICECHECKER_UTILS_H
#define PRICECHECKER_UTILS_H

#include <string>

namespace PC
{
#define CHECK_EMPTY_STRING(str) ((str).empty() ? "-" : (str))

#define PANGO_STRIKETHROUGH(text) ("<span strikethrough='true'>" + (text) + "</span>")
#define PANGO_SMALL(text) ("<small>" + (text) + "</small>")
#define PANGO_BOLD(text) ("<b>" + (text) + "</b>")

    class Utils
    {
    public:
        static void RemoveEmptySpace(std::string& str);
    };
}

#define SINGLE_TON(className) className(className&) = delete; \
    className(className&&) = delete;                          \
    className& operator=(className&) = delete;                \
    className& operator=(className&&) = delete;               \
    inline static className& _() { static className instance; return instance; }

#endif //PRICECHECKER_UTILS_H
