#ifndef AUDIOOBJECTMANAGER_H
#define AUDIOOBJECTMANAGER_H

#pragma once

#include "IAudioObjectManager.h"
#include <list>
#include <stack>

namespace holoplot
{
    class AudioObjectManager : public IAudioObjectManager
    {
    public:
        AudioObjectManager();
        ~AudioObjectManager();

        void add(const AudioObject &);
        void remove(const Id &);
        void changePosition(const Id &, const Position &);
        void undo();

    private:
        std::list<AudioObject> mlAudioObj;
        std::stack<> msHistory;
    };

} // namespace holoplot

#endif