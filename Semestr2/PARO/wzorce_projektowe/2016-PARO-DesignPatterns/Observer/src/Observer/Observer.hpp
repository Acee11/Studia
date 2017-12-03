#pragma once

#include <functional>
#include <map>

typedef std::function<void ()> Handler;

class Observer
{
public:
    Observer()
        :nextAvailableId(0)
    {
    }

    unsigned subscribe(Handler handler)
    {
        handlers[nextAvailableId] = handler;
        return nextAvailableId++;
    }

    void unsubscribe(unsigned id)
    {
        handlers.erase(id);
    }

    void notify()
    {
        for (auto h : handlers)
        {
            h.second();
        }
    }

private:
    std::map<unsigned, Handler> handlers;
    unsigned nextAvailableId;
};


// example of use:
// #include <functional>
// subscribeId = databaseObserver->subscribe(std::bind(&Chart::plot, this));
