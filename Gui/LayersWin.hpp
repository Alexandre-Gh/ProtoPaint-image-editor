/*
** ProtoPaint
** File description:
** Core
*/

#pragma once

#ifndef LAYERSWIN_H_
    #define LAYERSWIN_H_

    #include "../includes/Headers.hpp"
    #include "AGUIWindow.hpp"
    #include "../Graphics/DrawZone.hpp"
    #include "../Core/Layer.hpp"

    namespace GUI
    {
        class LayersWin : public GUI::AGUIWindow
        {
            public:
                LayersWin(std::vector<std::shared_ptr<ProtoPaint::Layer>> layers);
                ~LayersWin() = default;

                void content(); //Actual function to modify in inherited classes
                std::vector<std::shared_ptr<ProtoPaint::Layer>> getLayers();
                void setLayers(std::vector<std::shared_ptr<ProtoPaint::Layer>> layers, unsigned int index);
                const unsigned int &getCurrentLayerIndex();
                void addLayer();

            private:
                 std::vector<std::shared_ptr<ProtoPaint::Layer>> _layers;
                 unsigned int _currentLayerIndex;


        };
    }

#endif