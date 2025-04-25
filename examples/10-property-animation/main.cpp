/*
  This file is part of KDBindings.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Morgan Bengtsson <morgan.bengtsson@kdab.com>

  SPDX-License-Identifier: MIT

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <kdbindings/animation_driver.h>
#include <kdbindings/property.h>
#include <kdbindings/property_animation.h>

using namespace KDBindings;

int main()
{
    constexpr float value = 0.0F;
    constexpr float targetValue = 10.0F;
    constexpr float duration = 10.0F;

    Property<float> animatedProperty(value);
    (void)animatedProperty.valueChanged().connect([](float value) {
        std::cout << value << std::endl;
    });

    auto &driver = AnimationDriver::instance();

    auto updateDriverNumTimes = [&](int num){
        constexpr float deltaTime = 1.0F;

        for (int i = 0; i < num; i++) {
            driver.update(deltaTime);
        }
    };

    driver.animate(animatedProperty, targetValue, duration);

    updateDriverNumTimes(10);

    auto animationId = driver.animate(animatedProperty, 0.0F, duration);

    updateDriverNumTimes(5);

    driver.stopAnimation(animationId);

    updateDriverNumTimes(5);

    {
        Property<float> outOfScopeProperty(value);
        driver.animate(outOfScopeProperty, targetValue, duration);
    }

    updateDriverNumTimes(10);

    return 0;
}
