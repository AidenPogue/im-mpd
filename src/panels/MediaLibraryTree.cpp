#include "MediaLibraryTree.hpp"

#include "LibraryLayer.hpp"
#include "../TitleFormatting/TitleFormatter.hpp"

namespace ImpyD {
    void MediaLibraryTree::FetchChildren(MpdClientWrapper &client, TreeItem &item)
    {
        if (!item.children)
        {
            item.children = std::make_unique<std::vector<TreeItem>>();
        }
        item.children->clear();
        //Testing layers!

        // std::vector<LibraryLayer> layers =
        //     {
        //     LibraryLayer("%albumartist%", ""),
        //     LibraryLayer("%album% (%date%)", "%date% %album%"),
        //     LibraryLayer("%disc%.%track% - %title%", ""),
        // };

        auto rootTags = TitleFormatting::GetUsedTags(layers.front().displayFormat);
        auto rootTagsVec = std::vector<mpd_tag_type>(rootTags.begin(), rootTags.end());

        client.BeginNoIdle();
        auto rootList = client.List(&rootTagsVec);
        client.EndNoIdle();

        for (const auto &item : rootList)
        {
            item.push_back(TreeItem(TitleFormatting::FormatITagged(*item, layers.front().displayFormat), nullptr, nullptr));
        }
    }

    std::string MediaLibraryTree::PanelName()
    {
        return GetFactoryName();
    }

    void MediaLibraryTree::DrawContents(MpdClientWrapper &client)
    {
        for (int i = 0; i < rootItems.size(); ++i)
        {
            const auto &rootItem = rootItems[i];

            ImGui::PushID(i);
            if (ImGui::TreeNodeEx(rootItem.content.c_str(), ImGuiTreeNodeFlags_SpanFullWidth))
            {
                ImGui::TreePop();
            }
            ImGui::PopID();
        }

    }

    void MediaLibraryTree::OnIdleEvent(MpdClientWrapper &client, mpd_idle event)
    {
        if (event & MPD_IDLE_DATABASE)
        {
            FetchChildren(client, TODO);
        }
    }

    void MediaLibraryTree::InitState(MpdClientWrapper &client)
    {
        FetchChildren(client, TODO);
    }
} // ImMPD