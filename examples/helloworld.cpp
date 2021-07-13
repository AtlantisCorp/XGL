
#include <XGL/XGL.h>
#include <iostream>

namespace XGL
{
    
}

int main(int argc, char** argv)
{
    try
    {
        XGL::Main mMain;

        mMain.plugins().load("Plugins/libGlRenderer");
        mMain.plugins().load("Plugins/libOBJMeshLoader");

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
        
        auto scene = XGL::Scene(mMain, { 1024, 256, 1024 });
        
        auto meshNode = scene.createMeshNode(mesh, { 4.0, 0.0, 4.0 });
        auto materialNode = scene.createMaterialNode(material);
        auto entityNode = scene.createEntityNode(meshNode, { materialNode });
        scene.append(entityNode);
        
        glm::mat4 projection = glm::perspective(70.0f, 1024.0f/768.0f, 0.1f, 100.0f);
        XGL::PCamera camera = XGL::Camera::New(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
        
        surface->Render.add([&](XGL::ISurface& surface){
            surface.clearBuffers();
            
            XGL::Frustum frustum(projection, camera->matrix());

            pipeline->bind(renderer);
            scene.render(renderer, frustum);

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
