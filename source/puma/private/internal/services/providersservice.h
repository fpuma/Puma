#pragma once

#include <engine/services/iprovidersservice.h>
#include <internal/services/base/providercontainer.h>

namespace puma
{
    class ProvidersService final : public IProvidersService
    {
    public:

        ProvidersService() { m_providers = std::make_unique<ProviderContainer>(); }

        ~ProvidersService() { m_providers.reset(); }

        ProviderContainer* get() override { return m_providers.get(); }

        void uninit() { m_providers->uninit(); }

    private:

        std::unique_ptr<ProviderContainer> m_providers;
    };
}