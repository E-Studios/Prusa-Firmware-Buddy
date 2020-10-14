#pragma once

#include "Iwindow_menu.hpp"
#include "IWinMenuContainer.hpp"
#include <stdint.h>

//todo
//use template instead IWinMenuContainer *pContainer;
//I want same methods for IWinMenuContainer as std::array<IWindowMenuItem *, N>  .. need to add iterators
class window_menu_t : public IWindowMenu {
    uint8_t index;
    void setIndex(uint8_t index); //for ctor (cannot fail)
    /// Prints single item in the menu
    /// \param rect is rectangle of the whole window menu
    void printItem(const Rect16 &rect, const size_t visible_count, IWindowMenuItem *item, const int item_height);
    /// Searches for next visible item
    /// Repeats search for \param steps times
    /// Negative value searches in backward direction
    /// \returns false if end of item list reached before all steps consumed
    bool moveToNextVisibleItem(int steps = 1);
    /// Moves menu so the cursor is on the screen
    /// \returns true if menu was moved
    bool refreshTopIndex();
    /// \returns index in visible item list (excluding hidden) according to
    /// index from the complete item list (including hidden)
    int visibleIndex(const int real_index);
    /// \returns index of the item (including hidden) defined by
    /// index in visible item list (excluding hidden)
    int realIndex(const int visible_index);

public:
    window_menu_t(window_t *parent, Rect16 rect, IWinMenuContainer *pContainer, uint8_t index = 0);
    uint8_t top_index;
    IWinMenuContainer *pContainer;
    bool SetIndex(uint8_t index); //must check container
    void Increment(int dif);
    void Decrement(int dif) { Increment(-dif); }
    uint8_t GetIndex() const { return index; }
    uint8_t GetCount() const;
    IWindowMenuItem *GetItem(uint8_t index) const;
    IWindowMenuItem *GetActiveItem();
    /// Redraws single item in menu
    /// If the item is out of screen nothing happens
    void unconditionalDrawItem(uint8_t index);

protected:
    virtual void unconditionalDraw() override;
    virtual void windowEvent(EventLock /*has private ctor*/, window_t *sender, GUI_event_t event, void *param) override;
};
