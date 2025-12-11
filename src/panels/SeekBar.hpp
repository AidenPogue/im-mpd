#pragma once

#include "PanelBase.hpp"

namespace ImMPD
{
    class SeekBar : public PanelBase
    {
    private:
        //The glfw time that currentElapsedSettings was last set.
        double elapsedSecondsSetAtTime;
        float currentElapsedSeconds;
        float currentDuration;

        float currentSeek = -1;

        mpd_state currentState = MPD_STATE_STOP;

        void SetState(mpd_song *song, mpd_status *status);
    public:
        SeekBar();
        ~SeekBar();
        void Draw(MpdClientWrapper *client) override;
        const char *GetTitle() override;

        void OnIdleEvent(MpdClientWrapper *client, MpdIdleEventData *data) override;

        void InitState(MpdClientWrapper *client) override;
    };
}
