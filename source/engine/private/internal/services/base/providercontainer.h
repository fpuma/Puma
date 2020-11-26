#pragma once
#include <engine/services/base/iprovidercontainer.h>

namespace puma
{
    class ProviderContainer final : public IProviderContainer
    {
    public:

        void uninit();
    };
}