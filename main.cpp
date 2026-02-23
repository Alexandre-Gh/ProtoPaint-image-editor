/*
** ProtoPaint
** File description:
** main
*/

#include "includes/Headers.hpp"
#include "Core/Core.hpp"

int main(int argc, char* argv[])
{
    try {
        //PROGRAM START
        ProtoPaint::Core core;
        core.loop();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
