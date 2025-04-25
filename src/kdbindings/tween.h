/*
  This file is part of KDBindings.

SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
Author: Morgan Bengtsson <morgan.bengtsson@kdab.com>

SPDX-License-Identifier: MIT

Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#pragma once

namespace KDBindings {

template<typename T>
class Tween
{
public:
    explicit Tween(T startValue,
                   T targetValue,
                   float duration)
        : m_startValue(startValue)
        , m_targetValue(targetValue)
        , m_value(startValue)
        , m_duration(duration)
    {
    }

    void update(float deltaTime)
    {
        m_elapsed += deltaTime;
        m_value = m_startValue + range() * progress(); // linear ease
    }

    T startValue() const
    {
        return m_startValue;
    }

    T targetValue() const
    {
        return m_targetValue;
    }

    T value() const
    {
        return m_value;
    }

    void reset(T startValue, T targetValue, float duration)
    {
        m_startValue = startValue;
        m_value = startValue;
        m_targetValue = targetValue;
        m_duration = duration;
        m_elapsed = 0;
    }

    T range() const {
        return targetValue() - startValue();
    }

    float progress() const {
        return m_elapsed / m_duration;
    }

private:
    T m_startValue;
    T m_targetValue;
    T m_value;

    float m_elapsed{ 0.0F };
    float m_duration{ 1.0F };
};

} // namespace KDBindings
