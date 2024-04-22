#include <controller/cmd.h>
#include <model/stack.h>

namespace controller
{
    using namespace model;
    void ICmd::execute()
    {
        checkPreconditionsImpl();
        executeImpl();
    }

    ICmd *ICmd::clone() const
    {
        return cloneImpl();
    }

    void ICmd::checkPreconditionsImpl() const
    {
    }

    NumberEnteredCmd::NumberEnteredCmd(double d)
        : ICmd{}, _number{d}
    {
    }

    NumberEnteredCmd::NumberEnteredCmd(const NumberEnteredCmd &rhs)
        : ICmd{rhs}, _number{rhs._number}
    {
    }

    NumberEnteredCmd::~NumberEnteredCmd()
    {
    }

    void NumberEnteredCmd::executeImpl() noexcept
    {
        // controller access to model
        Stack::Instance().push(_number);
    }

    NumberEnteredCmd *NumberEnteredCmd::cloneImpl() const
    {
        return new NumberEnteredCmd{*this};
    }
}