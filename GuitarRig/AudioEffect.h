#pragma once

#include <memory>

namespace Effects {

    enum class Pedals : size_t 
    {
        OVERDRIVE = 0,
        DISTORTION,
        REVERB, 
        FUZZY,
        FILTER,
        CHORUS,
        DELAY,
        WAH
    };

    class AudioEffect 
    {
    public:
      virtual ~AudioEffect() = default;
      virtual void process(float* buf, size_t num) = 0;
      std::shared_ptr<AudioEffect>& nextEffect() { return m_next; }

    protected:
      std::shared_ptr<AudioEffect> m_next {nullptr};
    };

}
