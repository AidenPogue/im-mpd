#pragma once

#include "PanelBase.hpp"
#include "../PanelFactory/RegisterPanel.hpp"

namespace ImpyD
{
    class SeekBar : public PanelBase, PanelFactory::RegisterPanel<SeekBar>
    {
    private:
        //The glfw time that currentElapsedSettings was last set.
        double elapsedSecondsSetAtTime = 0;
        float currentElapsedSeconds = 0;
        float currentDuration = 0;

        float currentSeek = -1;

        mpd_state currentState = MPD_STATE_STOP;

        void SetState(const MpdClientWrapper::MpdSongPtr &song, const MpdClientWrapper::MpdStatusPtr &status);

    public:
        IMPYD_REGISTER_PANEL_FactoryFunc(SeekBar)
        IMPYD_REGISTER_PANEL_GetFactoryName("Seekbar")

        SeekBar(int panelId)
            : PanelBase(panelId)
        {
        }

        ~SeekBar() override;

        void DrawContents(MpdClientWrapper &client) override;

        void OnIdleEvent(MpdClientWrapper &client, mpd_idle event) override;

        void InitState(MpdClientWrapper &client) override;

        std::string PanelName() override;
    };
}
