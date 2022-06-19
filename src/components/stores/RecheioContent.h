//
// Created by htrap19 on 6/19/22.
//

#ifndef PRICECHECKER_RECHEIOCONTENT_H
#define PRICECHECKER_RECHEIOCONTENT_H

#include "components/SearchableContent.h"

namespace PC
{
    class RecheioContent : public SearchableContent
    {
    public:
        RecheioContent();

        void Search(const std::string& search_text) override;
        void ParseSearchableContent(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_RECHEIOCONTENT_H
