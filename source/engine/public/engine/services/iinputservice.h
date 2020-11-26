#pragma once

#include <input/iinput.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class IInputService : public IService
    {
    public:

        virtual ~IInputService() {}

        virtual input::IInput* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInput puma::DefaultServices::getInstance()->get<puma::IInputService>()->get()
