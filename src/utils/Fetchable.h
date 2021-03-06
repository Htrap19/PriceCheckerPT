//
// Created by htrap19 on 3/27/22.
//

#ifndef PRICECHECKER_FETCHABLE_H
#define PRICECHECKER_FETCHABLE_H

#include <sstream>
#include <curlpp/Easy.hpp>

namespace PC
{
    class Fetchable
    {
    protected:
        Fetchable() = default;
        virtual ~Fetchable() = default;
        virtual void FetchErrCallback(const std::string& what) = 0;
        virtual std::ostringstream FetchBase(const std::string& url, bool use_encoding = false, const std::string& cookies_file = "");

    private:
        curlpp::Easy m_Request;
    };
}

#endif //PRICECHECKER_FETCHABLE_H
