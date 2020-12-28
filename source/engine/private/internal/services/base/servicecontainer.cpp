#include <precompiledengine.h>
#include <internal/services/base/servicecontainer.h>

#include <internal/services/applicationservice.h>
#include <internal/services/inputservice.h>
#include <internal/services/systemsservice.h>
#include <internal/services/providersservice.h>
#include <internal/services/physicsservice.h>

namespace puma
{
    ServiceContainer::ServiceContainer() {}
    ServiceContainer::~ServiceContainer() {}

    void ServiceContainer::init()
    {
        registerInterface<IProvidersService, ProvidersService>();
        registerInterface<IInputService, InputService>();
        registerInterface<ISystemsService, SystemsService>();
        registerClass<ApplicationService>();
        registerClass<PhysicsService>();

        add<ProvidersService>();
        add<InputService>();
        add<ApplicationService>();
        add<PhysicsService>();
        add<SystemsService>();
    }

    void ServiceContainer::uninit()
    {
        get<SystemsService>()->uninit();
        get<PhysicsService>()->uninit();
        get<ApplicationService>()->uninit();
        get<InputService>()->uninit();
        get<ProvidersService>()->uninit();
        clear();
    }
}