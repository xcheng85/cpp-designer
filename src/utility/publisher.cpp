#include <utility/publisher.h>
#include <utility/subscriber.h>
#include <utility>
#include <format>
#include <utility/event_system_exception.h>
#include <iostream>

namespace utility
{
    using namespace std;
    class Publisher::Impl
    {
        using Subscribers = unordered_map<string, unique_ptr<Subscriber>>;
        using EventSubscriptions = unordered_map<string, Subscribers>;

    public:
        Impl();
        ~Impl();
        void addEvent(shared_ptr<IEventPayload> payload) const;
        const Subscribers &subscribers(const string &eventName) const;
        Subscribers &subscribers(const string &eventName);
        void registerEvents(const vector<string> &events);
        void subscribe(const string &eventName, unique_ptr<Subscriber> subscriber);
        unique_ptr<Subscriber> unsubscribe(const string &eventName, const string &subscriberName);
        unordered_set<string> events() const;

    private:
        EventSubscriptions _events;
    };

    Publisher::Impl::Impl()
    {
    }

    Publisher::Impl::~Impl()
    {
    }
    // Scott Meyer's const_cast() pattern
    const Publisher::Impl::Subscribers &Publisher::Impl::subscribers(const string &eventName) const
    {
        // find or count
        auto itr = _events.find(eventName);
        if (itr == _events.end())
        {
            throw EventSystemException{format("{} is not supported", eventName)};
        }
        return itr->second;
    }

    Publisher::Impl::Subscribers &Publisher::Impl::subscribers(const string &eventName)
    {
        return const_cast<Publisher::Impl::Subscribers &>(as_const(*this).subscribers(eventName));
    }

    void Publisher::Impl::addEvent(shared_ptr<IEventPayload> payload) const
    {
        const auto &eventName = payload->name();
        const auto &subs = subscribers(eventName);
        for (const auto &[name, sub] : subs)
        {
            sub->handleEvent(payload);
        }
    }

    void Publisher::Impl::registerEvents(const vector<string> &events)
    {
        for (const auto &event : events)
        {
            auto i = _events.find(event);
            if (i != _events.end())
            {
                throw EventSystemException{std::format("{} already exists", event)};
            }
            // emplace version of unordered_map
            std::cout << event << "\n";
            _events.emplace(event, Subscribers{});
        }
    }

    void Publisher::Impl::subscribe(const string &eventName, unique_ptr<Subscriber> subscriber)
    {
        auto &subs = subscribers(eventName);
        auto sub = subs.find(subscriber->name());
        if (sub != subs.end())
        {
            throw EventSystemException(
                format("subscriber: {} already existed for event: {}", subscriber->name(), eventName));
        }

        subs.emplace(subscriber->name(), std::move(subscriber));
    }

    unique_ptr<Subscriber> Publisher::Impl::unsubscribe(const string &eventName, const string &subscriberName)
    {
        auto &subs = subscribers(eventName);
        auto sub = subs.find(subscriberName);
        if (sub == subs.end())
        {
            throw EventSystemException(
                format("subscriber: {} does not exsit for event: {}", subscriberName, eventName));
        }
        auto res = std::move(sub->second);
        // subs.erase(sub);
        subs.erase(subscriberName);
        return res;
    }

    unordered_set<string> Publisher::Impl::events() const
    {
        unordered_set<string> res;
        for (const auto &[event, subs] : _events)
            res.emplace(event);

        return res;
    }

    Publisher::Publisher()
    {
        _pimpl = make_unique<Impl>();
    }

    Publisher::~Publisher()
    {
    }

    void Publisher::subscribe(const string &eventName, unique_ptr<Subscriber> subscriber)
    {
        _pimpl->subscribe(eventName, move(subscriber));
    }

    unique_ptr<Subscriber> Publisher::unsubscribe(const string &eventName, const string &subscriberName)
    {
        return _pimpl->unsubscribe(eventName, subscriberName);
    }

    unordered_set<string> Publisher::events() const
    {
        return _pimpl->events();
    }

    unordered_set<string> Publisher::subscribers(const string &eventName) const
    {
        auto &subs = _pimpl->subscribers(eventName);

        unordered_set<string> res;
        for (const auto &[name, sub] : subs)
            res.emplace(name);

        return res;
    }

    void Publisher::addEvent(shared_ptr<IEventPayload> payload) const
    {
        _pimpl->addEvent(payload);
    }

    void Publisher::registerEvents(const vector<string> &events)
    {
        _pimpl->registerEvents(events);
    }
}