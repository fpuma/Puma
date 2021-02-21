//#pragma once
//
//#include <engine/services/iinputservice.h>
//
//namespace puma
//{
//    class InputService final : public IInputService
//    {
//    public:
//
//        InputService() { m_input = input::IInput::create(); }
//
//        ~InputService() { m_input.reset(); }
//
//        input::IInput* get() override { return m_input.get(); }
//
//        void uninit() {}
//
//    private:
//
//        std::unique_ptr<input::IInput> m_input;
//    };
//}
