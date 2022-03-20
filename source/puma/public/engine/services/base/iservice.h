#pragma once

namespace puma
{
    class IService : public NonCopyable
    {
    public:

        virtual ~IService() {}

        virtual void uninit() = 0;
    };
}