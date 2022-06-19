//
// Created by htrap19 on 4/27/22.
//

#include "Searchable.h"
#include "utils/Utils.h"

namespace PC
{
    void Searchable::Fetch(const std::string& url, const std::string& cookies_file)
    {
        std::string page_content = FetchBase(url, false, cookies_file).str();

        m_Doc.parse(page_content);
        FetchCallback(m_Doc);
    }

    std::string Searchable::ConvertToUrlQuery(const std::string& text)
    {
        std::stringstream txtStream(text);
        std::string word;
        std::string urlQueryStr;
        while (std::getline(txtStream, word, ' '))
            urlQueryStr += word + "+";
        urlQueryStr = urlQueryStr.substr(0, urlQueryStr.size() - 1);
        return urlQueryStr;
    }
}
