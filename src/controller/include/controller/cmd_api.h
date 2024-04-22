#pragma once

#include <memory>
#include <string>

// CmdControllerApi is called by ui
// controller CmdControllerApi has access to both view and model
namespace controller
{
    class CmdControllerAPI
    {
    public:
        explicit CmdControllerAPI();
        ~CmdControllerAPI();
        // handle event from view.
        void parseAndHandleCmd(const std::string &cmd);
    private:
        CmdControllerAPI(const CmdControllerAPI &) = delete;
        CmdControllerAPI(CmdControllerAPI &&) = delete;
        CmdControllerAPI &operator=(const CmdControllerAPI &) = delete;
        CmdControllerAPI &operator=(CmdControllerAPI &&) = delete;

        class Impl;
        std::unique_ptr<Impl> _pimpl;
    };
}