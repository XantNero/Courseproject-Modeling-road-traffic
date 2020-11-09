#include "ModelApplication.h"

int main(void)
{
    srand(time(NULL));
    ModelApplication app("example.mdl");
    app.run();
    return 0;
}