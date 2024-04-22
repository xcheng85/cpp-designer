#include <unordered_map>
#include <format>
#include <controller/cmd_factory.h>
#include <utility/event_system_exception.h>

namespace controller
{
    using namespace std;
    using namespace utility;

    class CmdFactory::Impl
    {
    public:
        Impl();

        void registerCmd(const std::string &name, ICmdPtr cmd);

        ICmdPtr unregisterCmd(const std::string &name);

        inline size_t numberofCmds() const
        {
            return _cmdLookup.size();
        }

        ICmdPtr cloneCommand(const std::string &name) const;

        bool isCmdRegistered(const std::string &name) const;

        std::unordered_set<std::string> commands() const;

    private:
        std::unordered_map<string, ICmdPtr> _cmdLookup;
    };

    CmdFactory::Impl::Impl()
    {
    }

    void CmdFactory::Impl::registerCmd(const std::string &name, ICmdPtr cmd)
    {
        if (isCmdRegistered(name))
        {
            throw EventSystemException{format("{} is already registered", name)};
        }
        else
        {
            _cmdLookup.emplace(name, std::move(cmd));
        }
    }

    ICmdPtr CmdFactory::Impl::unregisterCmd(const std::string &name)
    {
        if (isCmdRegistered(name))
        {
            auto i = _cmdLookup.find(name);
            // release ownership here and give it to the caller
            auto tmp = MakeICommandPtr(i->second.release());
            _cmdLookup.erase(i);
            return tmp;
        }
        else
        {
            return MakeICommandPtr(nullptr);
        }
    }

    ICmdPtr CmdFactory::Impl::cloneCommand(const std::string &name) const
    {
        if (isCmdRegistered(name))
        {
            const auto &command = _cmdLookup.find(name)->second;
            return MakeICommandPtr(command->clone());
        }
        else
        {
            return MakeICommandPtr(nullptr);
        }
    }

    bool CmdFactory::Impl::isCmdRegistered(const std::string &name) const
    {
        return _cmdLookup.find(name) != _cmdLookup.end();
    }

    std::unordered_set<std::string> CmdFactory::Impl::commands() const
    {
        unordered_set<string> res;

        for (const auto &[name, ptr] : _cmdLookup)
        {
            res.emplace(name);
        }

        return res;
    }

    CmdFactory::CmdFactory()
    {
        _pimpl = std::make_unique<Impl>();
    }

    CmdFactory::~CmdFactory()
    {
    }

    CmdFactory &CmdFactory::Instance()
    {
        static CmdFactory instance;
        return instance;
    }

    void CmdFactory::registerCmd(const std::string &name, ICmdPtr cmd)
    {
        _pimpl->registerCmd(name, move(cmd));
    }

    ICmdPtr CmdFactory::unregisterCmd(const std::string &name)
    {
        return _pimpl->unregisterCmd(name);
    }

    size_t CmdFactory::numberofCmds() const
    {
        return _pimpl->numberofCmds();
    }

    // caller took the ownership of this cmdptr
    ICmdPtr CmdFactory::cloneCommand(const std::string &name) const
    {
        return _pimpl->cloneCommand(name);
    }

    bool CmdFactory::isCmdRegistered(const std::string &name) const
    {
        return _pimpl->isCmdRegistered(name);
    }

    std::unordered_set<std::string> CmdFactory::commands() const
    {
        return _pimpl->commands();
    }
}