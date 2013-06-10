#ifndef BAKGE_CORE_WINDOW_H
#define BAKGE_CORE_WINDOW_H

#include <bakge/Bakge.h>

namespace bakge
{

class Window
{

public:

    Window();
    ~Window();

    BGE_FACTORY Window* Create(int Width, int Height);

}; /* Window */

} /* bakge */

#endif /* BAKGE_CORE_WINDOW_H */
