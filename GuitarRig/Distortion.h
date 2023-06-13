#pragma once

#include "AudioEffect.h"

namespace Effects {

    class Distortion : public AudioEffect 
    {
     public:
        virtual ~Distortion() = default;
        void process(float* buf, size_t num) override;
    };
}  // namespace Effects

