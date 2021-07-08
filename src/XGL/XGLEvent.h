#ifndef __XGL_EVENT_H__
#define __XGL_EVENT_H__

#include "XGLIncludes.h"
#include "XGLEventHandler.h"

namespace XGL
{
    /**
     *  @brief Defines an event.
     * 
     *  An event is an holder for a collection of EventHandler. A class
     *  defines an event that holds EventHandler for that event and then,
     *  calls them when necessary.
     * 
     */
    template < typename... Args > 
    class Event
    {
    public: 
        typedef EventHandler < Args... > HandlerType;
    protected:
        typedef std::list < HandlerType > HandlerCollection;

    private:
        //! @brief The handlers for this event.
        HandlerCollection mHandlers;

        //! @brief The mutex.
        mutable std::mutex mutex;

    public:
        //! @brief Default constructor.
        Event() {}

        //! @brief Copy constructor.
        Event(const Event& rhs) 
        {
            std::lock_guard l(rhs.mutex);
            mHandlers = rhs.mHandlers;
        }

        //! @brief Move constructor.
        Event(Event&& rhs)
        {
            std::lock_guard l(rhs.mutex);
            mHandlers = std::move(rhs.mHandlers);
        }

        //! @brief Copy operator.
        Event& operator = (const Event& rhs)
        {
            std::scoped_lock l(mutex, rhs.mutex);
            mHandlers = rhs.mHandlers;
            return *this;
        }

        //! @brief Move operator.
        Event& operator = (Event&& rhs)
        {
            std::scoped_lock l(mutex, rhs.mutex);
            mHandlers = std::move(rhs.mHandlers);
            return *this;
        }

        //! @brief Adds a new handler and returns its id.
        auto add(const HandlerType& handler)
        {
            std::lock_guard l(mutex);
            mHandlers.push_back(handler);
            return handler.id();
        }

        //! @brief Adds a new handler only from its function.
        auto add(const typename HandlerType::HandlerPFn & handler)
        {
            return add(HandlerType(handler));
        }

        //! @brief Removes a handler, and returns true on success.
        bool remove(const HandlerType& handler) 
        {
            std::lock_guard l(mutex);

            auto it = std::find(mHandlers.begin(), mHandlers.end(), handler);
            if (it != mHandlers.end())
            {
                mHandlers.erase(it);
                return true;
            }

            return false;
        }

        //! @brief Removes a handler from its id.
        bool remove(unsigned int id)
        {
            std::lock_guard l(mutex);

            auto it = std::find_if(mHandlers.begin(), mHandlers.end(), [id](auto& rhs){ return id == rhs.id(); });
            if (it != mHandlers.end())
            {
                mHandlers.erase(it);
                return true;
            }

            return false;
        }

        //! @brief Returns a copy of the handlers list.
        auto handlers() const 
        {
            std::lock_guard l(mutex);
            return mHandlers;
        }

        //! @brief Calls all handlers.
        void call(Args... params)
        {
            auto lHandlers = handlers();

            for (auto& handler : lHandlers)
                handler(params...);
        }

        //! @brief Calls all handlers async.
        auto callAsync(Args... params)
        {
            return std::async(std::launch::async, [this](Args... params){
                call(params...);
            }, params...);
        }
    };
}

#endif // !__XGL_EVENT_H__