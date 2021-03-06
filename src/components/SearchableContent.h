//
// Created by htrap19 on 4/13/22.
//

#ifndef PRICECHECKER_SEARCHABLECONTENT_H
#define PRICECHECKER_SEARCHABLECONTENT_H

#include <gtkmm.h>
#include <mutex>
#include "utils/Searchable.h"
#include "EmptyList.h"

namespace PC
{
    class SearchableContent : public Gtk::ScrolledWindow, public Searchable
    {
    public:
        virtual ~SearchableContent() = default;
        inline Gtk::Widget& GetWidget() override { return *this; }
        void Search(const std::string& url) override; // same name but different logic implementation
        void FetchCallback(CDocument& doc) override;
        virtual void ParseSearchableContent(CDocument& doc) = 0;
        [[nodiscard]] inline const std::string& GetName() const override { return m_Name; }
        [[nodiscard]] inline const std::string& GetTitle() const override { return m_Name; }
        inline bool IsRunning() const { std::lock_guard lock(m_RunningMutex); return m_Running; }
        inline void SetIsRunning(bool running) { std::lock_guard lock(m_RunningMutex); m_Running = running; }
        inline bool IsCompleted() const { return m_ProgressBar.get_fraction() >= 1.0; }
        inline Gtk::ListBox& GetListBox() { return m_ListBox; }
        inline Gtk::Spinner& GetSpinner() { return m_Spinner; }
        inline Gtk::ProgressBar& GetProgressBar() { return m_ProgressBar; }
        inline bool UseCookies() const { return m_UseCookies; }
        inline void SetTotalItemsCount(uint32_t total_item_count) { m_TotalItemCount = total_item_count; m_ProgressBar.set_fraction(0.0); }
        void Increment();
        void ClearProductList();

    protected:
        explicit SearchableContent(const std::string& name, bool use_cookies = false);
        void FetchErrCallback(const std::string& what) override;

    protected:
        std::list<ProductComponent> m_Products;
        Gtk::ListBox m_ListBox;
        EmptyList m_EmptyWidget;
        Gtk::Spinner m_Spinner;
        Gtk::ProgressBar m_ProgressBar;

        std::string m_Name;
        bool m_Running = false;
        mutable std::mutex m_RunningMutex;
        bool m_UseCookies = false;

        // Progress bar
        uint32_t m_TotalItemCount = 0;
    };
}

#endif //PRICECHECKER_SEARCHABLECONTENT_H
