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

#include "Capture.hpp"

namespace Nexuz {
  namespace Media {
    namespace Audio {
      namespace SoundSystem {
        namespace ALSA {
          namespace Capture {

            Capture::Capture() {
            }

            Capture::~Capture() {
            }

            int Capture::init(const string &driver) {

              int err = -1;
              if ((err = snd_pcm_open(&this -> handle, driver.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
                cerr << "Capture open error: " << snd_strerror(err) << endl;
                exit(EXIT_FAILURE);
              }

              if ((err = snd_pcm_set_params(this -> handle, SND_PCM_FORMAT_S16, SND_PCM_ACCESS_RW_INTERLEAVED, 2,
                  44100, 0, 500000)) < 0) {
                cerr << "Capture set params error: " << snd_strerror(err) << endl;
                return false;
              }

              return true;
            }

            bool Capture::start() {
              snd_pcm_uframes_t frames = 32;
              int size = frames * 4;
              int rc;

              char * buffer = (char *) malloc(size);

              while (1) {
                rc = snd_pcm_readi(handle, buffer, frames);
                if (rc == -EPIPE) {
                  /* EPIPE means overrun */
                  fprintf(stderr, "overrun occurred\n");
                  snd_pcm_prepare(handle);
                } else if (rc < 0) {
                  fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
                } else if (rc != (int) frames) {
                  fprintf(stderr, "short read, read %d frames\n", rc);
                }
                rc = write(1, buffer, size);
                if (rc != size)
                  fprintf(stderr, "short write: wrote %d bytes\n", rc);
              }

            }

            bool stop() {
              //              snd_pcm_drain( handle);
              //              snd_pcm_close(handle);
              //              free( buffer);
            }

          }
        }
      }
    }
  }
}
