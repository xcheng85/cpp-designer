#include <utility/subscriber.h>

namespace utility
{
    Subscriber::Subscriber(string_view name)
        : _name{name}
    {
    }

    void Subscriber::handleEvent(shared_ptr<IEventPayload> payload)
    {
        handleEventImpl(payload);
        return;
    }
}