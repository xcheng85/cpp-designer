#pragma once

#include <memory>
#include <string>
#include <string_view>

using namespace std;

namespace utility
{
    class IEventPayload;
    class Subscriber
    {
    public:
        explicit Subscriber(string_view name);
        virtual ~Subscriber() = default;

        // pattern virtual impl
        // payload of event could be anytype

        void handleEvent(shared_ptr<IEventPayload>);

        inline const string &name() const
        {
            return _name;
        }

    private:
        virtual void handleEventImpl(shared_ptr<IEventPayload>) = 0;

        string _name;
    };
}