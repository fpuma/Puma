#include <precompiledengine.h>

#include <internal/services/base/providercontainer.h>

namespace puma
{
    void ProviderContainer::uninit()
    {
        traverse( [](IProvider* _ptr)
        {
            _ptr->uninit();
        } );

        clear();
    }
}