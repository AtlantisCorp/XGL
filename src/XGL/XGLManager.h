#ifndef __XGL_MANAGER_H__
#define __XGL_MANAGER_H__

#include "XGLIncludes.h"
#include "XGLError.h"

namespace XGL
{
    /** 
     *  @brief Defines a generalized manager for objects.
     * 
     *  Objects are stored as std::shared_ptr instances. You can add/remove them,
     *  you can find them through a predicate, and clear the manager.
     * 
     */
    template < class T >
    class Manager 
    {
        //! @brief The objects in the manager.
        std::list < std::shared_ptr < T > > mObjects;

        //! @brief The mutex.
        mutable std::mutex mutex;

    public: 
        
        //! @brief Adds a new object.
        void add(const std::shared_ptr < T >& rhs)
        {
            XGLThrowIf(!rhs, std::runtime_error("Null rhs."));
            std::lock_guard l(mutex);
            mObjects.push_back(rhs);
        }

        //! @brief Removes an object.
        void remove(const std::shared_ptr < T >& rhs)
        {
            std::lock_guard l(mutex);
            auto iter = std::find(mObjects.begin(), mObjects.end(), rhs);
            if (iter != mObjects.end())
                mObjects.erase(iter);
        }

        //! @brief Clears the manager.
        void clear() 
        {
            std::lock_guard l(mutex);
            mObjects.clear();
        }

        //! @brief Finds an object through a predicate.
        std::shared_ptr < T > find(auto predicate) const 
        {
            std::lock_guard l(mutex);

            for (auto& rhs : mObjects)
                if (predicate(rhs))
                    return rhs;
            
            return nullptr;
        }
    };
}

#endif // !__XGL_MANAGER_H__