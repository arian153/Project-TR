#pragma once
#include <vector>

namespace GAM400
{
    class ParticleEmitter;

    class ParticleSystem
    {
    public:
        ParticleSystem();
        ~ParticleSystem();

    private:
        std::vector<ParticleEmitter*> m_emitters;
    };
}
