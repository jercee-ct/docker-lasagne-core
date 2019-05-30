#include "ExampleService_Export.h"
#include <daf/TaskExecutor.h>
#include <daf/SemaphoreControlledQueue_T.h>
#include <ace/Reactor.h>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

namespace example
{

class Service : public DAF::TaskExecutor
{
public:
    Service() :
        queue_(10)
    {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) ctor\n")));
    }

    int init(int, char**) override
    {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) init\n")));

        try
        {
            // schedule timer?
            const auto interval = 1s;
            if (ACE_Reactor::instance()->schedule_timer(this, nullptr, interval, interval) == 0)
                throw std::runtime_error("schedule timer failed");

            // execute svc thread(s)?
            const auto num_threads = 1;
            if (execute(num_threads) != 0)
                throw std::runtime_error("execute threads failed");
        }
        catch (std::exception& e)
        {
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) init error: %s\n"), e.what()));
            return -1;
        }
        return 0;
    }

    int svc() override
    {
        while (isAvailable())
        {
           ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) svc\n")));
           auto work = queue_.take();
           ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) work: %d\n"), data));
        }
        return 0;
    }

    int handle_timeout(const ACE_Time_Value&, const void*) override
    {
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) handle_timeout\n")));
        queue_.put(++counter_);
        return isAvailable() ? 0 : -1;
    }

private:
    size_t counter_ = 0;
    DAF::SemaphoreControlledQueue<decltype(counter_)> queue_;
};

ACE_FACTORY_NAMESPACE_DEFINE(ExampleService, ExampleService, example::Service)

} // namespace example
