#include <precompiledengine.h>
#include <internal/services/base/servicecontainer.h>

#include <internal/services/engineapplicationservice.h>
#include <internal/services/loggerservice.h>
#include <internal/services/systemsservice.h>
#include <internal/services/providersservice.h>
#include <internal/services/physicsservice.h>

namespace puma
{
    ServiceContainer::ServiceContainer() {}
    ServiceContainer::~ServiceContainer() {}

    void ServiceContainer::init()
    {
        registerInterface<ILoggerService, LoggerService>();
        registerInterface<IProvidersService, ProvidersService>();
        registerInterface<ISystemsService, SystemsService>();
        registerInterface<IEngineApplicationService, EngineApplicationService>();
        registerClass<PhysicsService>();

        add<LoggerService>();
        add<ProvidersService>();
        add<EngineApplicationService>();
        add<PhysicsService>();
        add<SystemsService>();
    }

    void ServiceContainer::uninit()
    {
        get<SystemsService>()->uninit();
        get<PhysicsService>()->uninit();
        get<EngineApplicationService>()->uninit();
        get<ProvidersService>()->uninit();
        get<LoggerService>()->uninit();
        clear();
    }
}