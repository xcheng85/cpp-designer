#include <model/stack.h>
#include <utility/event_system_exception.h>
#include <deque>
#include <algorithm>
#include <assert.h>

namespace model
{
    class Stack::Impl
    {
    public:
        explicit Impl(const Stack &);

        void push(double d, bool sendEvent);

        double pop(bool sendEvent);

        vector<double> getElements(size_t n) const;

        inline auto size() const { return _deque.size(); }

        void clear();

    private:
        const Stack &_stack;

        std::deque<double> _deque;
    };

    std::string StackEventPayload::name() const
    {
        return StackEventPayload::name(_eventType);
    }

    std::string StackEventPayload::name(EventType eventType)
    {
        switch (eventType)
        {
        case EventType::STACK_UPDATED:
            return "STACK_UPDATED";
        case EventType::STACK_ERROR:
            return "STACK_ERROR";
        default:
            assert(false);
        };
    }

    std::string StackEventPayload::errorMessage(const ErrorType &errorType)
    {
        switch (errorType)
        {
        case ErrorType::STACK_EMPTY:
            return "Attempting to pop empty stack";
        case ErrorType::NOT_ENOUGH_ELEMENTS:
            return "Need at least two stack elements to swap top";
        default:
            return "Unknown error";
        };
    }

    Stack::Impl::Impl(const Stack &stack)
        : _stack{stack}
    {
    }

    void Stack::Impl::push(double d, bool sendEvent)
    {
        _deque.emplace_back(d);
        if (sendEvent)
        {
            _stack.addEvent(std::make_shared<StackEventPayload>(
                StackEventPayload(StackEventPayload::EventType::STACK_UPDATED,
                                  {})));
        }
    }

    double Stack::Impl::pop(bool sendEvent)
    {
        if (_deque.empty())
        {
            _stack.addEvent(std::make_shared<StackEventPayload>(
                StackEventPayload(StackEventPayload::EventType::STACK_ERROR,
                                  StackEventPayload::ErrorType::STACK_EMPTY)));

            throw EventSystemException{StackEventPayload::errorMessage(StackEventPayload::ErrorType::STACK_EMPTY)};
        }
        else
        {
            auto val = _deque.back();
            _deque.pop_back();
            if (sendEvent)
            {
                _stack.addEvent(std::make_shared<StackEventPayload>(
                    StackEventPayload(StackEventPayload::EventType::STACK_UPDATED,
                                      {})));
            }
            return val;
        }
    }

    vector<double> Stack::Impl::getElements(size_t n) const
    {
        vector<double> res;
        if (n > _deque.size())
        {
            n = _deque.size();
        }

        std::copy(_deque.rbegin(), _deque.rbegin() + n, std::back_inserter(res));
        return res;
    }

    void Stack::Impl::clear()
    {
        _deque.clear();
        _stack.addEvent(std::make_shared<StackEventPayload>(
            StackEventPayload(StackEventPayload::EventType::STACK_UPDATED,
                              {})));
    }

    Stack &Stack::Instance()
    {
        static Stack instance;
        return instance;
    }

    void Stack::push(double d, bool sendEvent)
    {
        _pimpl->push(d, sendEvent);
        return;
    }

    double Stack::pop(bool sendEvent)
    {
        return _pimpl->pop(sendEvent);
    }

    vector<double> Stack::getElements(size_t n) const
    {
        return _pimpl->getElements(n);
    }

    size_t Stack::size() const
    {
        return _pimpl->size();
    }

    void Stack::clear() const
    {
        _pimpl->clear();
    }

    Stack::Stack()
    {
        _pimpl = std::make_unique<Impl>(*this);
        registerEvents({StackEventPayload::name(StackEventPayload::EventType::STACK_UPDATED),
                        StackEventPayload::name(StackEventPayload::EventType::STACK_ERROR)});
    }
    // required by pimpl idiom, cannot =default
    Stack::~Stack()
    {
    }
}