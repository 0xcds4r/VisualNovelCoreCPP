#include "main.h"
#include "VNEngine.h"

VisualNovelEngine* pEngine = nullptr;

int main() 
{
    pEngine = new VisualNovelEngine();
    pEngine->run();

    return 0;
}
