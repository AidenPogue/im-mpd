#ifndef IM_MPD_PANELFLAGS_HPP
#define IM_MPD_PANELFLAGS_HPP

namespace ImpyD
{
    typedef int PanelFlags;

    enum PanelFlags_
    {
        PanelFlags_None = 0,
        //If set, this panel will be drawn before all panels that do not have this set. No other guarantees are made about order.
        PanelFlags_DrawEarly = 1 << 0,
        //If set, this panel will always call DrawContents even if it's collapsed.
        PanelFlags_AlwaysDraw = 1 << 1,
    };
}

#endif //IM_MPD_PANELFLAGS_HPP