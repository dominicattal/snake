#include "util/util.h"
#include "gfx/window.h"

int main(int argc, char** argv) 
{
    assert(argc <= 2);
    window_init(argc, argv);
    window_loop(argc, argv);
    return 0;
}