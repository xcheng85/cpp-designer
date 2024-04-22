#pragma once
#include "cmd.h"

namespace controller
{
    class CmdManager
    {
    public:
        CmdManager();
        ~CmdManager();

        void execute(ICmdPtr cmd);

    private:
        CmdManager(CmdManager &) = delete;
        CmdManager(CmdManager &&) = delete;
        CmdManager &operator=(CmdManager &) = delete;
        CmdManager &operator=(CmdManager &&) = delete;

        class Impl;
        class DoubleStackImpl;
        std::unique_ptr<Impl> _pimpl;
    };
}