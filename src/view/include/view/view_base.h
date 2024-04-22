#pragma once

#include <utility/publisher.h>

namespace view
{
    using namespace utility;

    class ViewEventPayload : public IEventPayload
    {
    public:
        ViewEventPayload(const std::string &cmd) : _cmd{cmd} {}
        inline std::string name() const override
        {
            return CmdEntered;
        }
        inline std::string cmd() const
        {
            return _cmd;
        }
        constexpr static std::string CmdEntered = "CmdEntered";
    private:
        std::string _cmd; // payload
    };

    class ViewBase : protected Publisher
    {
    public:
        ViewBase()
        {
            registerEvents({ViewEventPayload::CmdEntered});
        }
        virtual ~ViewBase()
        {
        }

        // // post a message to the user
        // virtual void postMessage(const std::string &m) = 0;

        // event handler for model changes
        virtual void handleModelUpdates() = 0;

        using Publisher::subscribe;
        using Publisher::unsubscribe;
    };
}