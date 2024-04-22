#include <optional>
#include <regex>
#include <exception>
#include <utility/event_system_exception.h>
#include <controller/cmd_api.h>
#include <controller/cmd_manager.h>
#include <controller/cmd_factory.h>
#include <controller/cmd.h>
#include <iostream>

namespace controller
{
    using namespace utility;
    using namespace controller;

    class CmdControllerAPI::Impl
    {
    public:
        explicit Impl();
        void parseAndHandleCmd(const std::string &cmd);

    private:
        std::optional<double> isNum(const std::string &);
        void handleCmd(ICmdPtr cmdPtr);
        CmdManager _cmdManager;
    };

    CmdControllerAPI::Impl::Impl()
    {
    }

    std::optional<double> CmdControllerAPI::Impl::isNum(const std::string &s)
    {
        std::cout << s << "\n";
        if (s == "+" || s == "-")
            return {};
        std::regex dpRegex("((\\+|-)?[[:digit:]]*)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
        bool isNumber{std::regex_match(s, dpRegex)};
        if (isNumber)
        {
            return std::stod(s);
        }
        return {};
    }

    void CmdControllerAPI::Impl::parseAndHandleCmd(const std::string &cmd)
    {
        auto num = isNum(cmd);
        if (num.has_value())
        {
             auto t = num.value();
            auto p = new NumberEnteredCmd(t);
            std::cout << p->payload();
            _cmdManager.execute(MakeICommandPtr(p));
        }
        else
        {
            // check if the command is registered
            auto cmdPtr = CmdFactory::Instance().cloneCommand(cmd);
            if (!cmdPtr)
            {
                // controller told view
                // ui_.postMessage(format("cmd: {} is not registered"));
            }
            else
            {
                handleCmd(std::move(cmdPtr));
            }
        }
    }

    void CmdControllerAPI::Impl::handleCmd(ICmdPtr cmdPtr)
    {
        try
        {
            _cmdManager.execute(std::move(cmdPtr));
        }
        catch (EventSystemException &e)
        {
            // ui_.postMessage(e.what());
        }
    }

    CmdControllerAPI::CmdControllerAPI()
    {
        _pimpl = std::make_unique<Impl>();
    }

    CmdControllerAPI::~CmdControllerAPI()
    {
    }

    void CmdControllerAPI::parseAndHandleCmd(const std::string &cmd)
    {
        _pimpl->parseAndHandleCmd(cmd);
    }
}