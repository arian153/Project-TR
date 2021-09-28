#include "AudioResource.hpp"

namespace GAM400
{
    AudioResource::AudioResource(const std::wstring& path)
        : Resource(path)
    {
        m_type = eResourceType::Audio;
    }

    AudioResource::~AudioResource()
    {
    }

    void AudioResource::Initialize()
    {
    }

    void AudioResource::Shutdown()
    {
    }
}
