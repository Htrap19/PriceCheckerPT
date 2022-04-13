//
// Created by Htrap19 on 3/22/2022.
//

#ifndef PRICECHECKER_AUCHANCONTENT_H
#define PRICECHECKER_AUCHANCONTENT_H

#include <gtkmm.h>
#include "SearchableContent.h"

namespace PC
{
    class AuchanContent : public SearchableContent
    {
    public:
        AuchanContent();

        void Search(const std::string& search_text) override;
        void FetchCallback(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_AUCHANCONTENT_H
