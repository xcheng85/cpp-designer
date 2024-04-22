#pragma once
#include <iostream>
#include "view_base.h"

namespace view
{
    class ViewCLI : public ViewBase
    {
    public:
        ViewCLI(std::istream &, std::ostream &);
        ~ViewCLI();

        void execute();
        void handleModelUpdates() override;
    private:
        ViewCLI(const ViewCLI &) = delete;
        ViewCLI(ViewCLI &&) = delete;
        ViewCLI &operator=(const ViewCLI &) = delete;
        ViewCLI &operator=(ViewCLI &&) = delete;

        class Impl;
        std::unique_ptr<Impl> _pimpl;
    };
}