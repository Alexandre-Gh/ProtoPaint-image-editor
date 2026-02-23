/*
** ProtoPaint
** File description:
** ErrorException
*/

#pragma once

#ifndef FACTORY_TOOL_H_
    #define FACTORY_TOOL_H_

    #include "../Interfaces/ITool.hpp"

        class FactoryTool
        {
            public:
                static FactoryTool &GetInstance();
                std::unique_ptr<ProtoPaint::ITool> createTool(const std::string toolName);

            protected:
                FactoryTool();
                FactoryTool(const FactoryTool&) = delete;
                FactoryTool& operator=(const FactoryTool&) = delete;

                std::map<std::string, std::function<std::unique_ptr<ProtoPaint::ITool>()>> _allTools;
        };

#endif