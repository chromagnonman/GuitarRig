#pragma once

#include "AudioEffect.h"

namespace Effects {

    class Overdrive : public AudioEffect 
    {
    public:
        virtual ~Overdrive() = default;
        void process(float* buf, size_t num) override;
    };
}
