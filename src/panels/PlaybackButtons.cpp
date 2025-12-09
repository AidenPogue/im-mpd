#include "PlaybackButtons.hpp"
#include "imgui.h"
#include <vector>

struct PlaybackButton
{
    void (*onClick) (MpdClientWrapper *client);
    const char *text;
    const char *name;
    bool enabled = false;

    PlaybackButton(void (*onClick) (MpdClientWrapper *client), const char *text, const char *name)
    {
        this->onClick = onClick;
        this->text = text;
        this->name = name;
    }
};

static void Toggle_Click(MpdClientWrapper *client)
{
    client->Toggle();
}

ImMPD::PlaybackButtonsPanel::~PlaybackButtonsPanel()
{
}

void ImMPD::PlaybackButtonsPanel::Draw(MpdClientWrapper *client)
{
    bool result = false;


    if (ImGui::Begin(GetTitle(), nullptr, ImGuiWindowFlags_NoScrollbar))
    {
        if (ImGui::BeginPopupContextWindow(GetTitle()))
        {
            // ImGui::Selectable("Test", &test);
            ImGui::EndPopup();
        }
        

        if (ImGui::Button("<<")) {
            result = client->Prev();
        }

        ImGui::SameLine();
        
        if (ImGui::Button(">||")) {
            result = client->Toggle();
        }
        ImGui::SameLine();

        if (ImGui::Button(">>")) {
            result = client->Next();
        }
        
    }

    ImGui::End();
}

const char *ImMPD::PlaybackButtonsPanel::GetTitle()
{
    return "Playback Control Buttons";
}
