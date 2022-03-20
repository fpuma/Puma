#pragma once

namespace puma
{
    class IProvider : public NonCopyable
    {
    public:
        virtual ~IProvider() {}
        virtual void uninit() = 0;
    };
}