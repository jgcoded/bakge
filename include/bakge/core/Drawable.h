#ifndef BAKGE_CORE_DRAWABLE_H
#define BAKGE_CORE_DRAWABLE_H

namespace bakge
{

class Drawable
{

public:

    Drawable()
    {
    }

    virtual ~Drawable()
    {
    }

    virtual Result Draw() const = 0;

}; /* Drawable */

} /* bakge */

#endif /* BAKGE_CORE_DRAWABLE_H */
