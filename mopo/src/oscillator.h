/* Copyright 2013 Little IO
 *
 * mopo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mopo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mopo.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "processor.h"
#include "wave.h"

namespace mopo {

  class Oscillator : public Processor {
    public:
      enum Inputs {
        kFrequency,
        kPhase,
        kWaveform,
        kReset,
        kNumInputs
      };

      Oscillator();

      virtual Processor* clone() const { return new Oscillator(*this); }
      void preprocess();
      void process();

      inline void tick(int i) {
        mopo_float frequency = inputs_[kFrequency]->at(i);
        mopo_float phase = inputs_[kPhase]->at(i);

        offset_ += frequency / sample_rate_;
        double integral;
        offset_ = modf(offset_, &integral);
        outputs_[0]->buffer[i] =
            Wave::blwave(waveform_, offset_ + phase, frequency);
      }

    protected:
      mopo_float offset_;
      Wave::Type waveform_;
  };
} // namespace mopo

#endif // OSCILLATOR_H
