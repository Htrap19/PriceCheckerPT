//
// Created by Htrap19 on 3/23/2022.
//

#ifndef PRICECHECKER_SEARCHABLE_H
#define PRICECHECKER_SEARCHABLE_H

#include <iostream>
#include <sstream>
#include <gtkmm/widget.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <gumbo.h>
#include "components/ProductComponent.h"

namespace ps
{
    class Searchable
    {
    public:
        virtual ~Searchable()
        {
            if (m_ParsedOutput != nullptr)
                gumbo_destroy_output(&kGumboDefaultOptions, m_ParsedOutput);
            m_ParsedOutput = nullptr;
        }
        virtual void Search(const std::string& search_text) = 0;
        [[nodiscard]] virtual Gtk::Widget& GetWidget() = 0;
        virtual void FetchCallback(GumboNode* root) = 0;
        virtual void FetchErrCallback(const std::string& what) = 0;

    protected:
        virtual void Fetch(const std::string& url)
        {
            try
            {
                std::list<std::string> headers;
                headers.emplace_back("Connection:close");

                curlpp::Easy request;
                request.setOpt<curlpp::options::Url>(url);
                request.setOpt<curlpp::options::Verbose>(true);
//                request.setOpt<curlpp::options::HttpHeader>(headers);
                std::ostringstream os;
                os << request;
                std::string page_content = os.str();

                m_ParsedOutput = gumbo_parse(page_content.c_str());
                FetchCallback(m_ParsedOutput->root);
            }
            catch(curlpp::LogicError& e)
            {
                FetchErrCallback(e.what());
            }
            catch(curlpp::RuntimeError& e)
            {
                FetchErrCallback(e.what());
            }
        }

    protected:
        std::vector<ProductComponent> m_Products;

    private:
        GumboOutput* m_ParsedOutput = nullptr;
    };
}

#endif //PRICECHECKER_SEARCHABLE_H
