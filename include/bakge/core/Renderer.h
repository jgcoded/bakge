#ifndef BAKGE_CORE_RENDERER_H
#define BAKGE_CORE_RENDERER_H

#include <bakge/Bakge.h>

namespace bakge
{

class Renderer : public Bindable
{

public:

    Renderer()
    {
    }

    virtual ~Renderer()
    {
    }

    virtual Result Draw(Drawable* Obj) = 0;

}; /* Renderer */

} /* bakge */

#endif /* BAKGE_CORE_RENDERER_H */

