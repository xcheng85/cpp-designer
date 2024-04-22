#include <controller/cmd_subscriber.h>
#include <controller/cmd_api.h>
#include <view/view_base.h>
#include <utility/event_system_exception.h>

namespace controller
{
    using namespace view;
    using namespace utility;

    CmdTriggeredSubscriber::CmdTriggeredSubscriber(CmdControllerAPI &cmdApi)
        : Subscriber("CmdTriggered"), _cmdApi{cmdApi}
    {

    }

    void CmdTriggeredSubscriber::handleEventImpl(std::shared_ptr<IEventPayload> eventData)
    {
        auto typedPayload = dynamic_pointer_cast<ViewEventPayload>(eventData);
        if (!typedPayload)
        {
            throw EventSystemException("downcast failed, check the type");
        }
        else
        {
            _cmdApi.parseAndHandleCmd(typedPayload->cmd());
        }
    }

}