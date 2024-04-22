#include <iostream>
#include <memory>
#include "app.h"
#include <controller/cmd_api.h>
#include <controller/cmd_subscriber.h>
#include <view/view_base.h>
#include <view/model_subscriber.h>
#include <model/stack.h>

using namespace std;
using namespace view;
using namespace model;
using namespace controller;

unique_ptr<ViewCLI> getViewCLI()
{
    auto cli = make_unique<ViewCLI>(std::cin, std::cout);
    // has to be static
    // or else pass dangling reference to CmdTriggeredSubscriber
    static CmdControllerAPI cmdApi{};
    cli->subscribe(ViewEventPayload::CmdEntered, make_unique<CmdTriggeredSubscriber>(cmdApi));
    Stack::Instance().subscribe(
        StackEventPayload::name(StackEventPayload::EventType::STACK_UPDATED), 
        make_unique<ModelUpdatedSubscriber>(*(cli.get())));
    return cli;
}
