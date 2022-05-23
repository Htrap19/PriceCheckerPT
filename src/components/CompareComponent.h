//
// Created by htrap19 on 5/23/22.
//

#ifndef PRICECHECKER_COMPARECOMPONENT_H
#define PRICECHECKER_COMPARECOMPONENT_H

#include <gtkmm.h>
#include "utils/Utils.h"

namespace PC
{
    class SearchableContent;
    class CompareComponent : public Gtk::ScrolledWindow
    {
    public:
        class CompareColumns : public Gtk::TreeModelColumnRecord
        {
        public:
            CompareColumns() { add(m_ColName); add(m_ColPriceDesc); add(m_ColOriginalPrice); add(m_ColActualPrice); }

        public:
            Gtk::TreeModelColumn<Glib::ustring> m_ColName;
            Gtk::TreeModelColumn<Glib::ustring> m_ColPriceDesc;
            Gtk::TreeModelColumn<Glib::ustring> m_ColOriginalPrice;
            Gtk::TreeModelColumn<Glib::ustring> m_ColActualPrice;
        };

    public:
        SINGLE_TON(CompareComponent)
        void SetSearchableContentList(const std::list<Glib::RefPtr<SearchableContent>>& searchable_content_list);

    private:
        CompareComponent();
        template <typename T>
        inline void AppendCol(const Glib::ustring& title, const Gtk::TreeModelColumn<T>& tree_col)
        {
            auto treeViewCol = Gtk::make_managed<Gtk::TreeViewColumn>(title, tree_col);
            treeViewCol->set_resizable();
            m_TreeView.append_column(*treeViewCol);
        }

        Gtk::TreeRow AppendMain(const Glib::ustring& name);
        Gtk::TreeRow AppendChild(Gtk::TreeRow& main_row,
                                 const Glib::ustring& name,
                                 const Glib::ustring& price_desc,
                                 const Glib::ustring& original_price,
                                 const Glib::ustring& actual_price);

    private:
        CompareColumns m_Columns;
        Glib::RefPtr<Gtk::TreeStore> m_TreeModel;
        Gtk::TreeView m_TreeView;
    };
}

#endif //PRICECHECKER_COMPARECOMPONENT_H
