//
// Created by aiden on 2025-12-11.
//

#ifndef IM_MPD_CONTAINER_HPP
#define IM_MPD_CONTAINER_HPP
#include "PanelBase.hpp"


namespace ImMPD
{
    class Container : public ImMPD::PanelBase
    {
    public:
        const char * GetTitle() override;

        void Draw(MpdClientWrapper *client) override;
    };
}

#endif //IM_MPD_CONTAINER_HPP