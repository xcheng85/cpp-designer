#pragma once

#include <utility/subscriber.h>

// in the mvc architecture

// controller subscribe to view event
// view subscribe to model event

namespace controller
{
    using namespace utility;
    class CmdControllerAPI;
    class CmdTriggeredSubscriber : public utility::Subscriber
    {
    public:
        // di
        explicit CmdTriggeredSubscriber(CmdControllerAPI &cmdApi);
    private:
        // custom impl
        virtual void handleEventImpl(shared_ptr<IEventPayload>) override;
        CmdControllerAPI &_cmdApi;
    };
}
