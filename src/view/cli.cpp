#include <sstream>
#include <view/cli.h>
#include <view/view_base.h>
#include <model/stack.h>
#include <utility/tokenizer.h>

namespace view
{
    using namespace utility;
    using namespace model;
    using namespace view;
    using namespace std;

    class ViewCLI::Impl
    {
    public:
        Impl(ViewCLI &, istream &in, ostream &out);
        void execute();
        void handleModelUpdates();

    private:
        ViewCLI &_viewCLI;
        istream &_is;
        ostream &_os;
    };

    ViewCLI::Impl::Impl(ViewCLI &viewCLI, istream &is, ostream &os)
        : _viewCLI{viewCLI},
          _is{is},
          _os{os}
    {
    }

    void ViewCLI::Impl::execute()
    {
        for (string line; std::getline(_is, line, '\n');)
        {
            Tokenizer tokenizer{line};
            for (const auto &i : tokenizer)
            {
                _os << i << endl;
                if (i == "exit" || i == "quit")
                {
                    return;
                }
                else
                {
                    _viewCLI.addEvent(std::make_shared<ViewEventPayload>(i));
                }
            }
        }
    }

    // view can access model
    void ViewCLI::Impl::handleModelUpdates()
    {
        ostringstream oss;
        size_t size = Stack::Instance().size();
        // already reversed
        const auto tmp = Stack::Instance().getElements(size);
        oss << "\n";
        size_t j{size - 1};
        for (auto i = tmp.begin(); i != tmp.end(); ++i)
        {
            oss << j << ":\t" << *i << "\n";
            --j;
        }
        _os << oss.str() << endl;
    }

    ViewCLI::ViewCLI(istream &in, ostream &out)
    {
        _pimpl = std::make_unique<Impl>(*this, in, out);
    }

    ViewCLI::~ViewCLI()
    {
    }

    void ViewCLI::handleModelUpdates()
    {
        _pimpl->handleModelUpdates();
    }

    void ViewCLI::execute()
    {
        _pimpl->execute();
    }
}