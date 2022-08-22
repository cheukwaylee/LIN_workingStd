#ifndef IAUDIOOBJECTMANAGER_H
#define IAUDIOOBJECTMANAGER_H

#pragma once

#include "AudioObject.h"

namespace holoplot
{
    struct Id
    {
        int val;
    };

    struct Position
    {
        enum val
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G
        };
    };

    class AudioObject
    {
    public:
        AudioObject(Id id, Position position)
            : m_id(id), m_position(position) {}

        Id m_id;
        Position m_position;
    };

    class IAudioObjectManager
    {
    public:
        virtual ~IAudioObjectManager() = default;
        // execute() = 0
        virtual void add(const AudioObject &) = 0;
        virtual void remove(const Id &) = 0;
        virtual void changePosition(const Id &, const Position &) = 0;

        virtual void undo() = 0;
    };
}

#endif