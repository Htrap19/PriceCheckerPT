//
// Created by htrap19 on 4/14/22.
//

#ifndef PRICECHECKER_ELCORTEINGLESCONTENT_H
#define PRICECHECKER_ELCORTEINGLESCONTENT_H

#include "SearchableContent.h"

namespace PC
{
    class ElcorteinglesContent : public SearchableContent
    {
    public:
        ElcorteinglesContent();

        void Search(const std::string& search_text) override;
        void FetchCallback(CDocument &doc) override;
    };
}

#endif //PRICECHECKER_ELCORTEINGLESCONTENT_H
