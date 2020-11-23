#include "ModelApplication.h"

//TODO: timestep
//TODO: proper zoom and camera movement

int main(void)
{
    srand(time(NULL));
    ModelApplication app("test2.mdl");
    app.run();
    return 0;
}