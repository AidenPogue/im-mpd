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

    if (ImGui::Begin(GetTitle(), nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
    {
        if (ImGui::BeginPopupContextWindow(GetTitle()))
        {
            // ImGui::Selectable("Test", &test);
            ImGui::EndPopup();
        }

        if (ImGui::Button("<<")) {
            client->BeginNoIdle();
            result = client->Prev();
            client->EndNoIdle();
        }

        ImGui::SameLine();
        
        if (ImGui::Button(">||")) {
            client->BeginNoIdle();
            result = client->Toggle();
            client->EndNoIdle();
        }
        ImGui::SameLine();

        if (ImGui::Button(">>")) {
            client->BeginNoIdle();
            result = client->Next();
            client->EndNoIdle();
        }
        
    }

    ImGui::End();
}

const char *ImMPD::PlaybackButtonsPanel::GetTitle()
{
    return "Playback Control Buttons";
}
