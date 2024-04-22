#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

using namespace std;

namespace utility
{
    class Subscriber;

    class IEventPayload
    {
    public:
        virtual ~IEventPayload(){};
        virtual std::string name() const = 0;
    };

    class Publisher
    {
    public:
        Publisher();
        ~Publisher();
        // Publisher own the life-cycle of subscribe
        void subscribe(const string &eventName, unique_ptr<Subscriber> subscriber);
        // use the raii of unique_ptr to release
        unique_ptr<Subscriber> unsubscribe(const string &eventName, const string &subscriberName);
        
        unordered_set<string> events() const;
        unordered_set<string> subscribers(const string &eventName) const;

    protected:
        void addEvent(shared_ptr<IEventPayload> payload) const;
        void registerEvents(const vector<string> &events);

    private:
        class Impl;
        unique_ptr<Impl> _pimpl;
    };
}