#pragma once

#include <map>

#include <kdbindings/property.h>
#include <kdbindings/property_animation.h>

namespace KDBindings {

class AnimationDriver {
public:
    void update(float deltaTime)
    {
        for (auto it = m_d->m_animations.begin(); it != m_d->m_animations.end(); ) {
            auto &[id, animation] = *it;
            const bool reachedTarget = animation->update(deltaTime);

            if (reachedTarget) {
                it = m_d->m_animations.erase(it);
            } else {
                ++it;
            }
        }
    }

    template<typename T>
    int animate(Property<T> &property, T targetValue, float duration)
    {
        const int newId = ++(m_d->m_currentId);
        m_d->m_animations[newId] = std::unique_ptr<PropertyAnimation<T>>(new PropertyAnimation<T>(property, targetValue, duration, newId));

        (void)property.destroyed().connect([newId, this] {
                m_d->m_animations.erase(newId);
        });

        return newId;
    }

    void stopAnimation(int id) {
        m_d->m_animations.erase(id);
    }

    static inline AnimationDriver &instance()
    {
        static AnimationDriver driver;
        return driver;
    }

private:
    // Pimpl to be able to pass around AnimationDriver by value with same state
    struct Private {
        std::map<int, std::unique_ptr<Animation>> m_animations;
        int m_currentId{0};
    };

    std::shared_ptr<Private> m_d{ std::make_shared<Private>() };
};
}
