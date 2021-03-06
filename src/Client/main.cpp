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

//#include "Media/SoundSystem/ALSA/DSP/DSP.cpp"
//#include "Media/SoundSystem/ALSA/Capture/Capture.cpp"
//#include "Network/Connection.cpp"
//
////using namespace Nexuz::Media::Audio::SoundSystem::ALSA::DSP;
//using namespace Nexuz::Media::Audio::SoundSystem::ALSA::Capture;
//using namespace Nexuz::Network;
//
//int main() {
//  //  DSP * dsp = new DSP();
//  //
//  //  delete dsp;
//  //  dsp = NULL;
//
//  Connection * conn = new Connection();
//  conn -> openOut();
//
//  Capture * mic = new Capture();
//  mic -> init();
//  mic -> start(conn);
//
//  return 0;
//}


#include "GUI/MainWindow.hpp"
#include "Process.hpp"
#include "App/App.hpp"

using namespace Nexuz;
using namespace Nexuz::GUI;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow * mainWindow = new MainWindow();
  mainWindow -> load();

  App * application = new App();

  Process * process = Process::Instance();
  process -> init();

  //  delete mainWindow;
  //  mainWindow = NULL;

  return app.exec();
}

