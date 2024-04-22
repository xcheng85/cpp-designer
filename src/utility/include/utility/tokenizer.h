#pragma once

#include <string>
#include <vector>

using namespace std;

namespace utility
{

    // 1. split string based on delimiter
    // 2. rang-loop

    class Tokenizer
    {
    public:
        using Token = string;
        using Tokens = vector<Token>;
        using const_iterator = Tokens::const_iterator;

        explicit Tokenizer(const std::string &);
        explicit Tokenizer(std::istream &);
        ~Tokenizer();

        inline size_t numberOfTokens() const
        {
            return _tokens.size();
        }

        // for range-based loop
        inline const_iterator begin() const
        {
            return _tokens.begin();
        }

        inline const_iterator end() const
        {
            return _tokens.end();
        }

        inline const Token &operator[](size_t i) const
        {
            return _tokens[i];
        }

    private:
        void tokenize(std::istream &);

        Tokenizer() = delete;
        Tokenizer(const Tokenizer &) = delete;
        Tokenizer(Tokenizer &&) = delete;
        Tokenizer &operator=(const Tokenizer &) = delete;
        Tokenizer &operator=(Tokenizer &&) = delete;

        Tokens _tokens;
    };
}