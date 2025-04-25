/*
  This file is part of KDBindings.

SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
Author: Morgan Bengtsson <morgan.bengtsson@kdab.com>

SPDX-License-Identifier: MIT

Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kdbindings/tween.h>
#include <kdbindings/property.h>

namespace KDBindings {

class Animation
{
public:
    virtual ~Animation() = default;
    virtual bool update(float deltaTime) = 0;
};

template<typename T>
class PropertyAnimation : public Animation
{
public:
    bool update(float deltaTime) override
    {
        m_tween.update(deltaTime);
        m_property.set(m_tween.value());
        return m_tween.progress() >= 1.0F;
    }

    void set(T targetValue, float duration)
    {
        m_tween.reset(m_property.get(), targetValue, duration);
    }

private:
    PropertyAnimation(Property<T> &property, T targetValue, float duration, int id)
        : m_property(property)
        , m_tween(m_property.get(), targetValue, duration)
        , m_id(id) { };

    Property<T> &m_property;
    Tween<T> m_tween;
    int m_id = -1;

    friend class AnimationDriver;
};

} // namespace KDBindings
