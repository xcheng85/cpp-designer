#pragma once

#include <utility/publisher.h>
#include <vector>
#include <memory>
#include <string>
#include <optional>

namespace model
{
    using namespace utility;
    class StackEventPayload : public IEventPayload
    {
    public:
        enum class EventType : int
        {
            STACK_UPDATED,
            STACK_ERROR,
        };

        enum class ErrorType : int
        {
            STACK_EMPTY,
            NOT_ENOUGH_ELEMENTS,
        };

        StackEventPayload() = delete;

        explicit StackEventPayload(EventType eventType, std::optional<ErrorType> errorType)
            : _eventType{eventType},
              _errorType{errorType}
        {
        }
        virtual std::string name() const override;
        inline auto eventType() const { return _eventType; }
        inline auto errorType() const { return _errorType; }
        static std::string errorMessage(const ErrorType &errorType);

    private:
        EventType _eventType;
        std::optional<ErrorType> _errorType;
    };

    class Stack : public Publisher
    {
        class Impl; // so that the implementation can raise events
    public:
        static Stack &Instance();

        void push(double, bool sendEvent = true);

        double pop(bool sendEvent = true);

        std::vector<double> getElements(size_t n) const;

        using Publisher::subscribe;
        using Publisher::unsubscribe;

        size_t size() const;
        void clear() const;

        // singletion
    private:
        Stack();
        ~Stack();
        Stack(const Stack &) = delete;
        Stack(Stack &&) = delete;
        Stack &operator=(const Stack &) = delete;
        Stack &operator=(const Stack &&) = delete;

        std::unique_ptr<Impl> _pimpl;
    };

}
