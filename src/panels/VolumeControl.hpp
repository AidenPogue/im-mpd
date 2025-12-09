//
// Created by aiden on 2025-12-09.
//

#ifndef IM_MPD_VOLUMECONTROL_H
#define IM_MPD_VOLUMECONTROL_H
#include "PanelBase.hpp"

namespace ImMPD {
    class VolumeControl : public PanelBase
    {
    private:
        int editingValue = -1;
    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        ~VolumeControl() override;
    };
} // ImMPD

#endif //IM_MPD_VOLUMECONTROL_H