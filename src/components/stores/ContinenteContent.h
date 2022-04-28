//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_CONTINENTECONTENT_H
#define PRICECHECKER_CONTINENTECONTENT_H

#include <gtkmm.h>
#include "components/SearchableContent.h"

namespace PC
{
    class ContinenteContent : public SearchableContent
    {
    public:
        ContinenteContent();

        void Search(const std::string& search_text) override;
        void ParseSearchableContent(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_CONTINENTECONTENT_H
