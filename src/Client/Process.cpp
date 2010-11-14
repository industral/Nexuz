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

#include "Process.hpp"

namespace Nexuz {

  // --------------------------------------------------------------------
  // Public methods
  // --------------------------------------------------------------------

  // Singleton
  Process * Process::_process = NULL;

  Process * Process::Instance() {
    if (_process == NULL) {
      _process = new Process();
    }
    return _process;
  }

  Process::~Process() {
  }

  void Process::init() {
    this -> conn = Network::Connection::Instance();
    this -> conn -> init();
  }

  void Process::auth(int port) {
qDebug() << "auth";



//    //TODO: hardcode
//    Accounts * accounts = new Accounts();
//    QList<AccountInfo> accountsInfo = accounts -> getList();
//
//    for (int i = 0; i < accountsInfo.size(); ++i) {
//      this -> conn -> auth(accountsInfo.at(i).userName, accountsInfo.at(i).password);
//    }
  }

  // --------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------

  Process::Process() {
  }

}
