#pragma once

#include "AudioEffect.h"

namespace Effects {

    class Reverb : public AudioEffect 
    {
     public:
        virtual ~Reverb() = default;
        void process(float* buf, size_t num) override;
    };
}  // namespace Effects
