
#include <XGL/XGL.h>
#include <iostream>

namespace XGL
{
    struct OBJMeshLoader : public IMeshLoader, public Class < OBJMeshLoader >
    {
        std::shared_ptr < Mesh > load(const std::string& meshName, 
                                      const std::string& filename,
                                      const std::shared_ptr < IRenderer >& renderer)
        {
            return nullptr;
        }

        std::string name() const { return "OBJMeshLoader"; }
    };
}

struct OBJMeshLoaderPlugin : public XGL::IPlugin
{
    const char* name() const { return "OBJMeshLoaderPlugin"; }

    void inscribe(XGL::Main& mMain) {
        mMain.meshLoaders().add(XGL::OBJMeshLoader::New());
    }

    void unscribe(XGL::Main& mMain) {
        mMain.meshLoaders().remove(mMain.meshLoaders().findByName("OBJMeshLoader"));
    }
};

extern "C" XGL::IPlugin* PluginMain(void)
{
    static OBJMeshLoaderPlugin plugin;
    return &plugin;
}

int main(int argc, char** argv)
{
    try
    {
        XGL::Main mMain;

        mMain.plugins().load("Plugins/libGlRenderer");
        mMain.plugins().load("Plugins/libOBJMeshLoader");
        mMain.meshLoaders().add(XGL::OBJMeshLoader::New());

        auto renderer = mMain.renderers().first();
        renderer->initialize({});

        auto surface = renderer->createSurface({
            .title = "Hello World",
            .width = 1024,
            .height = 768,
            .closable = true
        });

        auto& window = *surface->window();

        auto mesh = mMain.meshes().loadOrGet("Cube", "cube.obj", "OBJMeshLoader", renderer);

        auto vshader = renderer->createShader(XGL::ShaderType::Vertex, "shader.vert");
        auto fshader = renderer->createShader(XGL::ShaderType::Fragment, "shader.frag");
        auto pipeline = XGL::Pipeline::New(std::vector{ vshader, fshader });
        mMain.pipelines().add(pipeline);

        auto diffuseTex = mMain.textureLoaders().findByName("PNGTextureLoader")->load(
            "Cube Diffuse", 
            "cube.png", 
            XGL::PixelFormat::RGB32,
            renderer
        );

        auto material = XGL::Material::New("Cube Material");
        material->setValue("view", glm::mat4(), XGL::ShaderType::Vertex);
        material->setTexture("diffuse", diffuseTex, XGL::ShaderType::Fragment);
        mMain.materials().add(material);

        surface->Render.add([&](XGL::ISurface& surface){
            surface.clearBuffers();

            pipeline->bind(renderer);
            material->bind(renderer);
            mesh->render(renderer);

            surface.swapBuffers();
        });

        while (!window.isClosed())
            window.update();
    }

    catch (const std::exception& err)
    {
        std::cout << err.what() << std::endl;
        return -1;
    }
}