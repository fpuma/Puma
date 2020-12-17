#include <precompiledengine.h>

#include <engine/iengine.h>

#include <engine/ecs/base/containers/isystemcontainer.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/icomponent.h>
#include <engine/ecs/base/isystem.h>

#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>

#include <engine/ecs/systems/irendersystem.h>

#include <engine/services/base/iprovider.h>
#include <engine/services/base/iprovidercontainer.h>
#include <engine/services/base/iservice.h>
#include <engine/services/base/iservicecontainer.h>

#include <engine/services/isystemsservice.h>
#include <engine/services/iapplicationservice.h>
#include <engine/services/iinputservice.h>
#include <engine/services/iphysicsservice.h>
#include <engine/services/iprovidersservice.h>
