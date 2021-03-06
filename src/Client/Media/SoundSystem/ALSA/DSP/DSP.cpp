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

#include "DSP.hpp"

namespace Nexuz {
  namespace Media {
    namespace Audio {
      namespace SoundSystem {
        namespace ALSA {
          namespace DSP {

            DSP::DSP() {
            }

            DSP::~DSP() {
            }

            int DSP::init(const string &driver) {
              string defaultDevice = defaultDev;

              if (!driver.empty()) {
                defaultDevice = driver;
              }

              int err = -1;
              if ((err = snd_pcm_open(&this -> handle, defaultDev.c_str(),
                  SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
                cout << "Playback open error: " << snd_strerror(err) << endl;
                exit(EXIT_FAILURE);
              }
              return true;
            }

            bool DSP::close() {
              return true; // TODO:fix
            }

            bool DSP::setAudioParams(const int &channels,
                const int &sampleRate, const int &bitsPerSample) {
              _snd_pcm_format format;

              cout << "SET AUDIO PARAMS: " << endl;

              if (bitsPerSample == 8) {
                format = SND_PCM_FORMAT_S8;
              } else if (bitsPerSample == 16) {
                format = SND_PCM_FORMAT_S16;
              } else if (bitsPerSample == 24) {
                format = SND_PCM_FORMAT_S24;
              } else if (bitsPerSample == 32) {
                format = SND_PCM_FORMAT_S32;
              }

              int err = NULL;

              if ((err = snd_pcm_set_params(this -> handle, format,
                  SND_PCM_ACCESS_RW_INTERLEAVED, channels, sampleRate, 0,
                  500000)) < 0) {
                cerr << "Playback open error: " << snd_strerror(err) << endl;
                return false;
              }
              return true;
            }

            long DSP::write(void *buf, const int &bufSize) {
              return (snd_pcm_writei(this -> handle, buf, bufSize / 4));
            }

          //            list <string> getAvailableDriverList() {
          //
          //            }

          }
        }
      }
    }
  }
}
