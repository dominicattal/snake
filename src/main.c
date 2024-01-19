#include "util/util.h"
#include "gfx/window.h"

int main(int argc, char** argv) 
{
    if (argc == 1)
    {
        printf("Missing arguments");
        return 1;
    }
    window_init(argc, argv);
    window_loop();
    return 0;
}