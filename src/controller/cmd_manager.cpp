#include <iostream>
#include <stack>
#include <controller/cmd_manager.h>


namespace controller
{
    using namespace std;
    class CmdManager::Impl
    {
    public:
        virtual ~Impl(){};
        virtual void execute(ICmdPtr cmd) = 0;
    };

    class CmdManager::DoubleStackImpl : public CmdManager::Impl
    {
    public:
        virtual ~DoubleStackImpl(){

        };
        void execute(ICmdPtr cmd) override;

    private:
    };

    void CmdManager::DoubleStackImpl::execute(ICmdPtr cmd)
    {
        cmd->execute();
    }

    CmdManager::CmdManager()
    {
        _pimpl = make_unique<DoubleStackImpl>();
    }
    CmdManager::~CmdManager()
    {
    }

    void CmdManager::execute(ICmdPtr cmd)
    {
        _pimpl->execute(move(cmd));
    }
}