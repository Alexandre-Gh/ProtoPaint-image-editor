/*
** ProtoPaint
** File description:
** OOP
*/

#ifndef LAYER_H_
    #define LAYER_H_

    #include "../Graphics/DrawZone.hpp"

    namespace ProtoPaint
    {
        class Layer
        {
            public:
                Layer(std::string name, unsigned int w, unsigned int h);
                Layer(const Layer& other);
                ~Layer() = default;

                const std::shared_ptr<Graphic::DrawZone> &getDrawZone();

                void setName(std::string name);
                const std::string &getName();

                void setVisible(bool visible);
                const bool &isVisible();
                std::shared_ptr<Layer> clone() const {
                    return std::make_shared<Layer>(*this);
                }


            private:
                std::shared_ptr<Graphic::DrawZone> _drawZone;
                std::string _name;
                bool _visible;
        };
    }

#endif