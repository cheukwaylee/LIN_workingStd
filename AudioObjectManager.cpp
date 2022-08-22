#include "AudioObjectManager.h"

namespace holoplot
{
    AudioObjectManager::AudioObjectManager()
    {
    }

    AudioObjectManager::~AudioObjectManager()
    {
    }

    void AudioObjectManager::add(const AudioObject &obj)
    {
        mlAudioObj.push_back(obj);
    }

    void AudioObjectManager::remove(const Id &obj_id)
    {
        // seach list
        // del from list
    }

    void AudioObjectManager::changePosition(const Id &obj_id, const Position &obj_pos)
    {
        // search in list
        // change
    }

    void AudioObjectManager::undo()
    {
    }
}
