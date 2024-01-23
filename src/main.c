#include "util/util.h"
#include "gfx/window.h"

int main(int argc, char** argv) 
{
    window_init(argc, argv);
    window_loop();
    return 0;
}