//
// Created by htrap19 on 6/25/22.
//

#ifndef PRICECHECKER_WATCHLISTCOMPONENT_H
#define PRICECHECKER_WATCHLISTCOMPONENT_H

#include <gtkmm.h>
#include "utils/Utils.h"
#include "components/SearchableContent.h"
#include "components/ProductComponent.h"

namespace PC
{
    class WatchListComponent : public Gtk::ScrolledWindow // Single-Ton
    {
    public:
        class WatchListColumns : public Gtk::TreeModelColumnRecord
        {
        public:
            WatchListColumns()
            {
                add(m_ColProductName);
                add(m_ColActualPrice);
                add(m_ColOriginalPrice);
                add(m_ColSecondaryPriceDesc);
            }

        public:
            Gtk::TreeModelColumn<Glib::ustring> m_ColProductName;
            Gtk::TreeModelColumn<Glib::ustring> m_ColActualPrice;
            Gtk::TreeModelColumn<Glib::ustring> m_ColOriginalPrice;
            Gtk::TreeModelColumn<Glib::ustring> m_ColSecondaryPriceDesc;
        };

    public:
        SINGLE_TON(WatchListComponent)

        void AddToWatchList(const std::list<Glib::RefPtr<SearchableContent>>& searchable_content);
        void ViewWatchList();
        void CheckWatchList(const std::string& store_name, ProductComponent& comp);

    private:
        WatchListComponent();
        template <typename T>
        inline void AppendCol(const Glib::ustring& title, const Gtk::TreeModelColumn<T>& tree_col)
        {
            auto treeViewCol = Gtk::make_managed<Gtk::TreeViewColumn>(title, tree_col);
            treeViewCol->set_resizable();
            m_TreeView.append_column(*treeViewCol);
        }

        Gtk::TreeRow AppendMain(const Glib::ustring& name);
        void AppendChild(Gtk::TreeRow& row, const Glib::ustring& name, const Glib::ustring& actual_price,
                         const Glib::ustring& original_price, const Glib::ustring& secondary_price_desc);

    private:
        WatchListColumns m_Columns;
        Glib::RefPtr<Gtk::TreeStore> m_TreeModel;
        Gtk::TreeView m_TreeView;
        Gtk::Box m_MainVBox = Gtk::Box(Gtk::Orientation::VERTICAL, 10);
        Gtk::Button m_DeleteButton;
    };
}

#endif //PRICECHECKER_WATCHLISTCOMPONENT_H
