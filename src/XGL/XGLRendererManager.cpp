#include "XGLRendererManager.h"

namespace XGL
{
    std::shared_ptr < IRenderer > RendererManager::first() const 
    {
        return find([](auto const&){ return true; });
    }

    std::shared_ptr < IRenderer > RendererManager::findByName(const std::string& name) const 
    {
        return find([&name](auto const& rhs){ return name == rhs->name(); });
    }
}