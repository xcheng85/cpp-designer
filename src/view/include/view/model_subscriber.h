#pragma once

#include <utility/subscriber.h>

namespace view
{
    using namespace utility;
    class ViewCLI;
    // the model to view dotted line in mvc arch
    class ModelUpdatedSubscriber : public utility::Subscriber
    {
    public:
        // di
        explicit ModelUpdatedSubscriber(ViewCLI &viewCli);

    private:
        // custom impl
        virtual void handleEventImpl(shared_ptr<IEventPayload>) override;
        ViewCLI &_viewCli;
    };
}