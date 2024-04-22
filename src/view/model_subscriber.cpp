#include <model/stack.h> // view is able to access model
#include <view/model_subscriber.h>
#include <view/cli.h>
#include <utility/event_system_exception.h>

namespace view
{
    using namespace utility;
    using namespace model;

    ModelUpdatedSubscriber::ModelUpdatedSubscriber(ViewCLI &viewCli)
        : Subscriber("ModelUpdated"), _viewCli{viewCli}
    {

    }

    void ModelUpdatedSubscriber::handleEventImpl(std::shared_ptr<IEventPayload> eventData)
    {
        auto typedPayload = dynamic_pointer_cast<StackEventPayload>(eventData);
        if (!typedPayload)
        {
            throw EventSystemException("downcast failed, check the type");
        }
        else
        {
            _viewCli.handleModelUpdates();
        }
    }

}