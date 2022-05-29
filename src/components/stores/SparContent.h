//
// Created by htrap19 on 5/9/22.
//

#ifndef PRICECHECKER_SPARCONTENT_H
#define PRICECHECKER_SPARCONTENT_H

#include "components/SearchableContent.h"

namespace PC
{
    class SparContent : public SearchableContent
    {
    public:
        SparContent();
        void Search(const std::string& search_text) override;
        void ParseSearchableContent(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_SPARCONTENT_H
