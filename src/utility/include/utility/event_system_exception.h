#pragma once

#include <string>
#include <exception>

namespace utility
{
    class EventSystemException : public std::exception
    {
    public:
        explicit EventSystemException(const std::string &message) : _message{message}
        {
        }

        const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

}