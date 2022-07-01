//
// Created by htrap19 on 6/25/22.
//

#include "WatchListComponent.h"
#include "utils/ConfigManager.h"
#include "utils/LanguageManager.h"
#include "WatchListNotification.h"
#include <base64.h>
#include <json/json.h>

namespace PC
{
    static Json::Value ParseJson(const std::string& json_data)
    {
        std::stringstream jsonStream;
        jsonStream << json_data;
        Json::Value json;
        jsonStream >> json;
        return json;
    }

    WatchListComponent::WatchListComponent()
        : m_TreeModel(Gtk::TreeStore::create(m_Columns)),
        m_TreeView(m_TreeModel)
    {
        m_DeleteButton.set_icon_name("user-trash-symbolic");
        m_DeleteButton.set_halign(Gtk::Align::END);
        m_DeleteButton.signal_clicked().connect([&]()
        {
            auto treeSelection = m_TreeView.get_selection();
            treeSelection->selected_foreach_iter([&](const Gtk::TreeModel::const_iterator& iter)
            {
                auto& row = *iter;
                auto name = row.get_value(m_Columns.m_ColProductName);
                if (!row.children().empty())
                {
                    CONFIG(RemoveWatchListStore, name);
                    return;
                }

                auto store_name = row.parent()->get_value(m_Columns.m_ColProductName);
                CONFIG(RemoveWatchListProduct, store_name, name);
            });
            ViewWatchList();
        });
        auto toolBarHBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
        toolBarHBox->append(m_DeleteButton);
        toolBarHBox->set_margin_bottom(5);

        AppendCol(LANGUAGE(name), m_Columns.m_ColProductName);
        AppendCol(LANGUAGE(actual_price), m_Columns.m_ColActualPrice);
        AppendCol(LANGUAGE(original_price), m_Columns.m_ColOriginalPrice);
        AppendCol(LANGUAGE(price_desc), m_Columns.m_ColSecondaryPriceDesc);
        m_TreeView.set_headers_visible();
        auto treeSelection = m_TreeView.get_selection();
        treeSelection->set_mode(Gtk::SelectionMode::MULTIPLE);

        m_MainVBox.append(m_TreeView);
        m_TreeView.set_expand();
        m_MainVBox.append(*toolBarHBox);

        set_child(m_MainVBox);
    }

    void WatchListComponent::AddToWatchList(const std::list<Glib::RefPtr<SearchableContent>>& searchable_content)
    {
        for (auto& searchable : searchable_content)
        {
            auto& listbox = searchable->GetListBox();
            listbox.selected_foreach([&](Gtk::ListBoxRow* row)
            {
                auto& productComponent = *dynamic_cast<ProductComponent*>(row);
                Json::Value detailsStrObj = Json::ValueType::objectValue;
                detailsStrObj["actual_price"] = Json::Value(productComponent.GetProductActualPrice());
                detailsStrObj["original_price"] = Json::Value(productComponent.GetProductOriginalPrice());
                detailsStrObj["secondary_price_desc"] = Json::Value(productComponent.GetProductSecondaryPriceDesc());
                std::stringstream detailStream;
                detailStream << detailsStrObj;
                auto detailsStr = detailStream.str();
                auto detailsBase64 = base64_encode(reinterpret_cast<const uint8_t*>(detailsStr.c_str()), detailsStr.length());
                CONFIG(SetWatchListProduct, searchable->GetName(), productComponent.GetProductName(), detailsBase64);
            });
            listbox.unselect_all();
        }
    }

    void WatchListComponent::ViewWatchList()
    {
        m_TreeModel->clear();
        auto watchList = CONFIG(GetWatchList);

        for (auto& key : watchList.getMemberNames())
        {
            auto store = watchList[key];
            if (!store.isObject())
                continue;

            auto mainRow = AppendMain(key);
            for (auto& product : store.getMemberNames())
            {
                auto decodedDetails = base64_decode(store[product].asString());
                auto detailsObj = ParseJson(decodedDetails);
                AppendChild(mainRow, product, detailsObj["actual_price"].asString(),
                            detailsObj["original_price"].asString(),
                            detailsObj["secondary_price_desc"].asString());
            }
        }
        m_TreeView.expand_all();
    }

    void WatchListComponent::CheckWatchList(const std::string& store_name, ProductComponent& comp)
    {
        auto productWatchList = CONFIG(GetWatchListStore, store_name);

        for (auto& key : productWatchList.getMemberNames())
        {
            if (Glib::ustring(key) != comp.GetProductName())
                continue;

            auto decodedDetails = base64_decode(productWatchList[key].asString());
            auto detailsObj = ParseJson(decodedDetails);

            auto savedActualPrice = detailsObj["actual_price"].asString();
            auto savedOriginalPrice = detailsObj["original_price"].asString();
            auto savedPriceDesc = detailsObj["secondary_price_desc"].asString();

            if (comp.GetProductActualPrice() != Glib::ustring(savedActualPrice) ||
                comp.GetProductOriginalPrice() != Glib::ustring(savedOriginalPrice) ||
                comp.GetProductSecondaryPriceDesc() != Glib::ustring(savedPriceDesc))
                WatchListNotification::_().Notify(comp, savedActualPrice,
                                              savedOriginalPrice,
                                              savedPriceDesc);
        }
    }

    Gtk::TreeRow WatchListComponent::AppendMain(const Glib::ustring& name)
    {
        auto row = *m_TreeModel->append();
        row[m_Columns.m_ColProductName] = name;
        return row;
    }

    void WatchListComponent::AppendChild(Gtk::TreeRow& row, const Glib::ustring& name, const Glib::ustring& actual_price,
                                         const Glib::ustring& original_price, const Glib::ustring& secondary_price_desc)
    {
        auto childRow = *m_TreeModel->append(row.children());
        childRow[m_Columns.m_ColProductName] = name;
        childRow[m_Columns.m_ColActualPrice] = actual_price;
        childRow[m_Columns.m_ColOriginalPrice] = original_price;
        childRow[m_Columns.m_ColSecondaryPriceDesc] = secondary_price_desc;
    }
}