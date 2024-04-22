#include <sstream>
#include <iterator>
#include <algorithm>
#include <utility/tokenizer.h>

namespace utility
{
    using namespace std;
    Tokenizer::Tokenizer(const string &s)
    {
        istringstream iss{s};

        tokenize(iss);
    }

    Tokenizer::Tokenizer(std::istream &is)
    {
        tokenize(is);
    }

    Tokenizer::~Tokenizer()
    {
    }

    void Tokenizer::tokenize(std::istream &is)
    {
        // iterator of all the strings
        _tokens.assign(istream_iterator<string>{is}, istream_iterator<string>{});

        for (auto &i : _tokens)
        {
            std::transform(i.begin(), i.end(), i.begin(), ::tolower);
        }
    }
}