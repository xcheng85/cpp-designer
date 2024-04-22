#pragma once

#include <string>
#include <unordered_set>
#include "cmd.h"

namespace controller
{
    // 1. singleton
    class CmdFactory
    {
    public:
        static CmdFactory &Instance();

        void registerCmd(const std::string &name, ICmdPtr cmd);

        // caller took the ownership
        ICmdPtr unregisterCmd(const std::string &name);

        size_t numberofCmds() const;

        // caller took the ownership of this cmdptr
        ICmdPtr cloneCommand(const std::string &name) const;

        bool isCmdRegistered(const std::string &name) const;

        std::unordered_set<std::string> commands() const;

    private:
        CmdFactory();
        ~CmdFactory();

        CmdFactory(CmdFactory &) = delete;
        CmdFactory(CmdFactory &&) = delete;
        CmdFactory &operator=(CmdFactory &) = delete;
        CmdFactory &operator=(CmdFactory &&) = delete;

        class Impl;
        std::unique_ptr<Impl> _pimpl;
    };

}