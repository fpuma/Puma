#include <precompiledengine.h>

#include <internal/services/base/providercontainer.h>

namespace puma
{
    void ProviderContainer::uninit()
    {
        visit( []( std::shared_ptr<IProvider> _ptr )
            {
                _ptr->uninit();
            } );

        clear();
    }
}