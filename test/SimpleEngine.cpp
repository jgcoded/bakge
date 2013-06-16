
#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

class SimpleEngine : bakge::Engine
{

public:

    SimpleEngine();
    ~SimpleEngine();

    bakge::Result Initialize();
    bakge::Result ShutDown();
    int Run();

    bakge::Result Update(bakge::Seconds DeltaTime);

    bakge::Result PreRenderStage();
    bakge::Result RenderStage();
    bakge::Result PostRenderStage();


protected:

    bakge::Window* AppWindow;
    bakge::FrontRenderer* SceneRenderer;

    GLUquadric* Quadric;

};

int main(int argc, char* argv[])
{
    SimpleEngine* MyEngine;

    printf("Initializing Bakge\n");
    bakge::Init(argc, argv);

    MyEngine = new SimpleEngine;

    if(MyEngine->Initialize() == BGE_FAILURE) {
        printf("Engine init failed\n");
        return 1;
    }

    MyEngine->Run();
    MyEngine->ShutDown();
    delete MyEngine;

    printf("Deinitializing Bakge\n");
    bakge::Deinit();

    return 0;
}


SimpleEngine::SimpleEngine()
{
    printf("Creating a SimpleEngine\n");
}


SimpleEngine::~SimpleEngine()
{
    printf("Destroying a SimpleEngine\n");
}


int SimpleEngine::Run()
{
    int ExitCode;

    bakge::Event Ev;

    while(1) {

        while(AppWindow->PollEvent(&Ev) == BGE_SUCCESS) {
            if(Ev.Type == -1) {
                AppWindow->Close();
                ExitCode = 0;
            }
        }

        if(AppWindow->IsOpen() == false)
            break;

        Update(0);
        PreRenderStage();
        RenderStage();
        PostRenderStage();
    }

    return ExitCode;
}


bakge::Result SimpleEngine::ShutDown()
{
    gluDeleteQuadric(Quadric);

    delete AppWindow;
    delete SceneRenderer;

    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::Initialize()
{
    SceneRenderer = bakge::FrontRenderer::Create();
    if(SceneRenderer == NULL)
        return BGE_FAILURE;

    AppWindow = bakge::Window::Create(600, 400);
    if(AppWindow == NULL)
        return BGE_FAILURE;

    Quadric = gluNewQuadric();

    glClearColor(0, 0.3, 0.5, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.5, 0.1, 500.0);

    SceneRenderer->Bind();

    return BGE_SUCCESS;
}


bakge::Result SimpleEngine::PreRenderStage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);
}


bakge::Result SimpleEngine::PostRenderStage()
{
    glMatrixMode(GL_PROJECTION);
    AppWindow->SwapBuffers();
}


bakge::Result SimpleEngine::RenderStage()
{
    /* *
     * Usually it would be SceneRenderer->Draw(&Something)
     * But there are on shape classes YET, so just do this
     * */
    glColor3f(0.7f, 0.7f, 0.7f);
    gluSphere(Quadric, 1.0f, 32, 32);
}


bakge::Result SimpleEngine::Update(bakge::Seconds DeltaTime)
{
    /* Nothing to do really */
    return BGE_SUCCESS;
}

