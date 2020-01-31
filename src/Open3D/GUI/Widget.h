// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include "Gui.h"

#include <memory>
#include <vector>

namespace open3d {
namespace gui {

class Color;
struct KeyEvent;
struct MouseEvent;
struct Theme;

struct DrawContext {
    const Theme& theme;
    int uiOffsetX;
    int uiOffsetY;
    int screenWidth;
    int screenHeight;
    int emPx;
    float frameDelta;  // in seconds
};

class Widget {
    friend class Window;

public:
    enum class DrawResult { NONE, CLICKED };

    Widget();
    explicit Widget(const std::vector<std::shared_ptr<Widget>>& children);
    virtual ~Widget();

    void AddChild(std::shared_ptr<Widget> child);
    const std::vector<std::shared_ptr<Widget>> GetChildren() const;

    const Rect& GetFrame() const;
    virtual void SetFrame(const Rect& f);

    const Color& GetBackgroundColor() const;
    bool IsDefaultBackgroundColor() const;
    void SetBackgroundColor(const Color& color);

    static constexpr int DIM_GROW = 10000;
    virtual Size CalcPreferredSize(const Theme& theme) const;

    virtual void Layout(const Theme& theme);
    virtual DrawResult Draw(const DrawContext& context);

    /// Widgets that use Dear ImGUI should not need to override this,
    /// as Dear ImGUI will take care of all the mouse handling during
    /// the Draw().
    virtual void Mouse(const MouseEvent& e);

    /// Widgets that use Dear ImGUI should not need to override this,
    /// as Dear ImGUI will take care of all the mouse handling during
    /// the Draw().
    virtual void Key(const KeyEvent& e);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace gui
}  // namespace open3d
