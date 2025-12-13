//
// Created by aiden on 2025-12-09.
//

#ifndef IM_MPD_VOLUMECONTROL_H
#define IM_MPD_VOLUMECONTROL_H
#include "PanelBase.hpp"

namespace ImpyD {
    class VolumeControl : public PanelBase
    {
    private:
        int editingValue = -1;
        int currentValue = 0;

        void SetState(mpd_status *status);
    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;

        ~VolumeControl() override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;
    };
} // ImMPD

#endif //IM_MPD_VOLUMECONTROL_H