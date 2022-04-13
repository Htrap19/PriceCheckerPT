//
// Created by htrap19 on 4/13/22.
//

#ifndef PRICECHECKER_MINIPRECO_H
#define PRICECHECKER_MINIPRECO_H

#include <gtkmm.h>
#include "SearchableContent.h"

namespace PC
{
    class MiniPreco : public SearchableContent
    {
    public:
        MiniPreco();

        void Search(const std::string& search_text) override;
        void FetchCallback(CDocument& doc) override;
    };
}

#endif //PRICECHECKER_MINIPRECO_H
