/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Function.h>
#include <AK/NonnullOwnPtrVector.h>
#include <LibGUI/Forward.h>

namespace GUI {

class UndoStack {
public:
    UndoStack();
    ~UndoStack();

    void push(NonnullOwnPtr<Command>&&);

    bool can_undo() const;
    bool can_redo() const;

    void undo();
    void redo();

    void finalize_current_combo();

    void set_current_unmodified();
    bool is_current_modified() const;

    void clear();

    Function<void()> on_state_change;

private:
    struct Combo {
        NonnullOwnPtrVector<Command> commands;
    };

    void pop();

    NonnullOwnPtrVector<Combo> m_stack;
    size_t m_stack_index { 0 };
    Optional<size_t> m_clean_index;
};

}
