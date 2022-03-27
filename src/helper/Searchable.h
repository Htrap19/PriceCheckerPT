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
#include <Document.h>
#include <functional>
#include "components/ProductComponent.h"
#include "Fetchable.h"

namespace ps
{
    class Searchable : public Fetchable
    {
    public:
        virtual ~Searchable() = default;
        virtual void Search(const std::string& search_text) = 0;
        [[nodiscard]] virtual Gtk::Widget& GetWidget() = 0;
        virtual void FetchCallback(CDocument& doc) = 0;

    protected:
        virtual void Fetch(const std::string& url)
        {
//            try
//            {
//                curlpp::Cleanup cleanup;
//                curlpp::Easy request;
//                request.setOpt<curlpp::options::Url>(url);
//                request.setOpt<curlpp::options::Verbose>(true);
//                std::ostringstream os;
//                os << request;
                std::string page_content = FetchBase(url).str();

                m_Doc.parse(page_content);
                FetchCallback(m_Doc);
//            }
//            catch(curlpp::LogicError& e)
//            {
//                FetchErrCallback(e.what());
//            }
//            catch(curlpp::RuntimeError& e)
//            {
//                FetchErrCallback(e.what());
//            }
        }

    protected:
        std::vector<ProductComponent> m_Products;

    private:
        CDocument m_Doc;
    };
}

#endif //PRICECHECKER_SEARCHABLE_H
