//
// Created by Htrap19 on 3/23/2022.
//

#ifndef PRICECHECKER_SEARCHABLE_H
#define PRICECHECKER_SEARCHABLE_H

#include <iostream>
#include <sstream>
#include <gtkmm/widget.h>
#include <Document.h>
#include <functional>
#include "components/ProductComponent.h"
#include "Fetchable.h"

namespace PC
{
    class Searchable : public Fetchable
    {
    public:
        virtual ~Searchable() = default;
        virtual void Search(const std::string& search_text) = 0;
        [[nodiscard]] virtual Gtk::Widget& GetWidget() = 0;
        virtual void FetchCallback(CDocument& doc) = 0;
        [[nodiscard]] virtual const std::string& GetName() const = 0;
        [[nodiscard]] virtual const std::string& GetTitle() const = 0;

    protected:
        virtual void Fetch(const std::string& url);
        virtual std::string ConvertToUrlQuery(const std::string& text);

    private:
        CDocument m_Doc;
    };
}

#endif //PRICECHECKER_SEARCHABLE_H
