#ifndef __XGLEVENTHANDLER_H__
#define __XGLEVENTHANDLER_H__

#include "XGLIncludes.h"

namespace XGL
{
    /**
     *  @brief Defines an event handler.
     * 
     */
    template < typename... Args >
    class EventHandler 
    {
    public:
        //! @brief The handler function we use.
        typedef std::function < void(Args...) > HandlerPFn;

        //! @brief The handler id type.
        typedef unsigned int Id;

    private:   
        //! @brief The handler.
        HandlerPFn mHandler;
        //! @brief The handler id.
        Id mId;
        //! @brief A counter to initialize new ids.
        static std::atomic_uint mIdCounter;

    public:

        //! @brief Constructs a new instance.
        explicit EventHandler(HandlerPFn function):
        mHandler(function),
        mId(++mIdCounter) { }

        //! @brief Copy constructor.
        EventHandler(const EventHandler& rhs):
        mHandler(rhs.mHandler),
        mId(rhs.mId) {}

        //! @brief Move constructor.
        EventHandler(EventHandler&& rhs):
        mHandler(std::move(rhs.mHandler)),
        mId(std::exchange(rhs.mId, 0)) {}

        //! @brief Copy operator.
        EventHandler& operator = (const EventHandler& rhs)
        {
            mHandler = rhs.mHandler;
            mId = rhs.mId;
            return *this;
        }

        //! @brief Move operator.
        EventHandler& operator = (EventHandler&& rhs)
        {
            std::swap(mHandler, rhs.mHandler);
            std::swap(mId, rhs.mId);
            return *this;
        }

        //! @brief Compares two handler.
        bool operator == (const EventHandler& rhs) const { return mId == rhs.mId; }

        //! @brief Returns the handler id.
        Id id() const { return mId; }

        //! @brief Calls the handler.
        void operator()(Args... args) const 
        {
            if (mHandler)
                mHandler(args...);
        }
    };

    template < typename... Args >
    std::atomic_uint EventHandler < Args... >::mIdCounter(0);
}

#endif // !__XGLEVENTHANDLER_H__