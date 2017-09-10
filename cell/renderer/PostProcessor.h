#ifndef CELL_POST_PROCESSOR_H
#define CELL_POST_PROCESSOR_H

#include <vector>

#include <math/linear_algebra/vector.h>

namespace Cell
{
    class Texture;
    class RenderTarget;
    class Shader;
    class Renderer;
    class Camera;

    class PostProcessor
    {
        friend Renderer;
    public:
        // resulting post-processor intermediate outputs
        Texture* SSAOOutput;
        Texture* BloomOutput;

        // toggles
        bool Sepia    = false;
        bool Vignette = false;
        bool Bloom    = true;
        bool SSAO     = true;
        bool TXAA     = true;
        bool SSR      = true;

        // ssao
        int SSAOKernelSize;
    private:
        // global post-process state
        Shader*       m_PostProcessShader;
        RenderTarget* m_RTOutput;

        // ssao
        RenderTarget* m_SSAORenderTarget;
        Shader* m_SSAOShader;
        Shader* m_SSAOBlur;
        std::vector<math::vec3> m_SSAOKernel;
        Texture* m_SSAONoise;
        // bloom
        Shader* m_BloomBlur;
        // blur
        Shader* m_OnePassGaussianShader;

    public:
        PostProcessor();
        ~PostProcessor();

        // process stages
        void ProcessPreLighting(Renderer* renderer, RenderTarget* gBuffer, Camera *camera);

        // blit all combined post-processing steps to default framebuffer
        void Blit(Renderer* renderer, Texture* soruce);

    private:
        //void blur();
    };
}
#endif