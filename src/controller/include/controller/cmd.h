#pragma once

#include <memory>

namespace controller
{
    class ICmd
    {
    public:
        virtual ~ICmd() {}
        void execute();

        // avoid slice bug
        ICmd *clone() const;

    protected:
        ICmd() {}
        ICmd(const ICmd &) {}

    private:
        virtual void checkPreconditionsImpl() const;
        // pattern
        virtual void executeImpl() noexcept = 0;
        virtual ICmd *cloneImpl() const = 0;

        ICmd(ICmd &&) = delete;
        ICmd &operator=(const ICmd &) = delete;
        ICmd &operator=(ICmd &&) = delete;
    };

    using ICmdPtr = std::unique_ptr<ICmd>;

    template <typename T, typename... Args>
    auto MakeICommandPtr(Args &&...args)
    {
        return ICmdPtr{new T{std::forward<Args>(args)...}};
    }

    inline auto MakeICommandPtr(ICmd *p)
    {
        return ICmdPtr{p};
    }

    class NumberEnteredCmd : public ICmd
    {
    public:
        explicit NumberEnteredCmd(double d);
        explicit NumberEnteredCmd(const NumberEnteredCmd &);
        virtual ~NumberEnteredCmd();
        inline auto payload() const {
            return _number;
        }
    private:
        NumberEnteredCmd(NumberEnteredCmd &&) = delete;
        NumberEnteredCmd &operator=(const NumberEnteredCmd &) = delete;
        NumberEnteredCmd &operator=(NumberEnteredCmd &&) = delete;

        void executeImpl() noexcept override;
        NumberEnteredCmd *cloneImpl() const override;

        // payload of this command
        double _number;
    };
}