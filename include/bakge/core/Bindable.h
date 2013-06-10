#ifndef BAKGE_CORE_BINDABLE_H
#define BAKGE_CORE_BINDABLE_H

#include <bakge/Bakge.h>

namespace bakge
{

class Bindable
{

public:

    Bindable();
    virtual ~Bindable();

    /* *
     * Bind and Unbind return results. A failed Bind means you shouldn't
     * use the resource, as it is unsafe and can cause errors
     * */
    virtual Result Bind() const = 0;
    virtual Result Unbind() const = 0;

}; /* Bindable */

} /* bakge */

#endif /* BAKGE_CORE_BINDABLE_H */
