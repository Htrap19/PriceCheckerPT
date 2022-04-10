//
// Created by htrap19 on 4/10/22.
//

#include "Fetchable.h"
#include <curlpp/Options.hpp>

namespace PC
{
    curlpp::Easy Fetchable::m_Request;
    std::mutex Fetchable::m_RequestMutex;

    std::ostringstream Fetchable::FetchBase(const std::string &url)
    {
        std::lock_guard guard(m_RequestMutex);
        std::ostringstream os;
        try
        {
            m_Request.setOpt<curlpp::options::Url>(url);
#ifdef PC_DEBUG
            m_Request.setOpt<curlpp::options::Verbose>(true);
#endif
            os << m_Request;
        }
        catch(std::exception& e)
        {
            FetchErrCallback(e.what());
        }

        return os;
    }
}