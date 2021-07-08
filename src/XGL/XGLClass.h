#ifndef __XGL_CLASS_H__
#define __XGL_CLASS_H__

#include "XGLIncludes.h"

namespace XGL
{
    /// @brief Defines a wrapper around a Class.
    ///
    /// A Class instance gives informations about an XGL Class: the type_info,
    /// the class name and the New() function. Uses this function to create a 
    /// new instance.
    ///
    /// Those functions are statics: you can use them without creating a Class
    /// instance.
    template < class T > 
    struct Class 
    {
        /// @brief Returns the std::type_info for the wrapped class.
        static const std::type_info& TypeInfo() { return typeid(T); }
        
        /// @brief Returns the name for this class.
        static const char* Name() { return TypeInfo().name(); }

        /// @brief Creates a new instance of the wrapped class.
        template < class... Args >
        static std::shared_ptr < T > New(Args&&... args) { return std::make_shared < T >(std::forward<Args>(args)...); }
    };
}

#endif // !__XGL_CLASS_H__