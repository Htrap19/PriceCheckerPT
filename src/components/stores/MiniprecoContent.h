//
// Created by htrap19 on 4/13/22.
//

#ifndef PRICECHECKER_MINIPRECOCONTENT_H
#define PRICECHECKER_MINIPRECOCONTENT_H

#include <gtkmm.h>
#include "components/SearchableContent.h"

namespace PC
{
    class MiniprecoContent : public SearchableContent
    {
    public:
        MiniprecoContent();

        void Search(const std::string& search_text) override;
        void ParseSearchableContent(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_MINIPRECOCONTENT_H
