#include "XGLVertex.h"

namespace XGL
{
    Vertex::Vertex(const std::list < Attrib >& attribs):
    mAttribs(attribs)
    {

    }

    Vertex::Vertex(const Vertex& rhs):
    mAttribs(rhs.mAttribs)
    {

    }

    Vertex& Vertex::operator = (const Vertex& rhs)
    {
        std::scoped_lock l(mutex, rhs.mutex);
        mAttribs = rhs.mAttribs;
        return *this;
    }

    Attrib Vertex::get(const std::string& name) const
    {
        std::lock_guard l(mutex);

        for (auto& attrib : mAttribs)
            if (attrib.name() == name)
                return attrib;

        return Attrib("", Attrib::None, 0);
    }

    void Vertex::set(const Attrib& attrib)
    {
        std::lock_guard l(mutex);

        for (auto& lAttrib : mAttribs)
        {
            if (lAttrib.name() == attrib.name())
            {
                lAttrib = attrib;
                return;
            }
        }

        mAttribs.push_back(attrib);
    }

    void Vertex::remove(const std::string& name)
    {
        std::lock_guard l(mutex);
        auto it = std::find_if(mAttribs.begin(), mAttribs.end(), [&name](auto& rhs){ return rhs.name() == name; });
        if (it != mAttribs.end())
            mAttribs.erase(it);
    }

    void Vertex::clear() 
    {
        std::lock_guard l(mutex);
        mAttribs.clear();
    }
}