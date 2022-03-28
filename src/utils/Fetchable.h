//
// Created by htrap19 on 3/27/22.
//

#ifndef PRICECHECKER_FETCHABLE_H
#define PRICECHECKER_FETCHABLE_H

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

namespace ps
{
    class Fetchable
    {
    protected:
        virtual ~Fetchable() = default;
        virtual void FetchErrCallback(const std::string& what) = 0;
        virtual std::ostringstream FetchBase(const std::string& url)
        {
            std::ostringstream os;
            try
            {
                curlpp::Cleanup cleanup;
                curlpp::Easy request;
                request.setOpt<curlpp::options::Url>(url);
                request.setOpt<curlpp::options::Verbose>(true);
                os << request;
            }
            catch(curlpp::LogicError& e)
            {
                FetchErrCallback(e.what());
            }
            catch(curlpp::RuntimeError& e)
            {
                FetchErrCallback(e.what());
            }

            return os;
        }
    };
}

#endif //PRICECHECKER_FETCHABLE_H
