#include <precompiledengine.h>
#include <internal/services/base/servicecontainer.h>

#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>
#include <engine/services/timerservice.h>
#include <internal/services/engineapplicationservice.h>
#include <internal/services/loggerservice.h>
#include <internal/services/physicsservice.h>

namespace puma
{
    ServiceContainer::ServiceContainer() {}
    ServiceContainer::~ServiceContainer() {}

    void ServiceContainer::init()
    {
        registerInterface<ILoggerService, LoggerService>();
        registerInterface<IEngineApplicationService, EngineApplicationService>();
        registerClass<PhysicsService>();
        registerClass<EcsService>();
        registerClass<TimerService>();
        registerClass<SystemsService>();

        add<LoggerService>();
        add<SystemsService>();
        add<EcsService>();
        add<EngineApplicationService>();
        add<PhysicsService>();
        add<TimerService>();
    }

    void ServiceContainer::uninit()
    {
        get<EngineApplicationService>()->uninit();
        clear();
    }
}