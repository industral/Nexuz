/*******************************************************************************
 * Copyright (c) 2010, Alex Ivasyuv                                            *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 *                                                                             *
 * 1. Redistributions of source code must retain the above copyright           *
 *    notice, this list of conditions and the following disclaimer.            *
 * 2. Redistributions in binary form must reproduce the above copyright        *
 *    notice, this list of conditions and the following disclaimer in the      *
 *    documentation and/or other materials provided with the distribution.     *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY Alex Ivasyuv ''AS IS'' AND ANY                 *
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE      *
 * DISCLAIMED. IN NO EVENT SHALL Alex Ivasyuv BE LIABLE FOR ANY DIRECT,        *
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES          *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;*
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF    *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.           *
 ******************************************************************************/

#ifndef _NEXUZ_MEDIA_AUDIO_SOUNDYSTEM_ABSTRACTDSP_HPP_
#define _NEXUZ_MEDIA_AUDIO_SOUNDYSTEM_ABSTRACTDSP_HPP_

#include "../../../include.hpp"

using namespace std;

namespace Nexuz {
  namespace Media {
    namespace Audio {
      namespace SoundSystem {
        class AbstractDSP {
          public:

            /*
             * Default constructor.
             */
            AbstractDSP() {
            }

            virtual ~AbstractDSP() {
            }

            virtual int init(const string &driver) = 0;
            virtual bool close() = 0;
            virtual bool setAudioParams(const int &channels,
                const int &sampleRate, const int &bitsPerSample) = 0;
            virtual long write(void *buf, const int &bufSize) = 0;

            /**
             * Get a list of available devices for audio driver.
             * e.g. "/dev/dsp" or "default".
             * return a list of available devices.
             */
            //            virtual list <string> getAvailableDriverList() = 0;

          protected:
          private:
        };
      }
    }
  }
}

#endif
