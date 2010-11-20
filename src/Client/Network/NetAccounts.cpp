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

#include "NetAccounts.hpp"

namespace Nexuz {
  namespace Network {

    // --------------------------------------------------------------------
    // Public methods
    // --------------------------------------------------------------------

    // Singleton
    NetAccounts * NetAccounts::_accounts = NULL;

    NetAccounts * NetAccounts::Instance() {
      if (_accounts == NULL) {
        _accounts = new NetAccounts();
      }
      return _accounts;
    }

    NetAccounts::~NetAccounts() {
    }

    void NetAccounts::initChat(const QString & id) {
      this -> getHost(id);
    }

    void NetAccounts::write(const QString & id, NexuzProtocol data, int size) {
      send(this -> sock, (void *) &data, size, 0);
    }

    // --------------------------------------------------------------------
    // Private methods
    // --------------------------------------------------------------------

    NetAccounts::NetAccounts() {
    }

    QString NetAccounts::getHost(const QString & id) {
      this -> manager = new QNetworkAccessManager();

      QNetworkRequest request;
      QUrl url = QUrl("http://server.nexuz.im:8365/info/" + id);
      request.setUrl(url);

      this -> reply = this -> manager -> get(request);
      connect(reply, SIGNAL(readyRead()), this, SLOT(getInfoFinished()));
    }

    bool NetAccounts::openConnection(const QString & host) {
      QStringList hostSplit = host.split(":");

      const char * hostAddr = hostSplit[0].toStdString().c_str();
      const int hostPort = hostSplit[1].toInt();

      struct sockaddr_in addr;

      this -> sock = socket(AF_INET, SOCK_STREAM, 0);
      if (this -> sock < 0) {
        perror("NetAccounts::openConnection socket");
        return false;
      }

      addr.sin_family = AF_INET;
      addr.sin_port = htons(hostPort);
      addr.sin_addr.s_addr = inet_addr(hostAddr);
      if (::connect(this -> sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror((QString("NetAccounts::openConnection connect: ") + host).toStdString().c_str());
        return false;
      }

      return true;
    }

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------

    void NetAccounts::getInfoFinished() {
      QScriptValue sv = Helper::Utils::parseJSON(QString(this -> reply -> readAll().data()));
      const QString host = sv.toVariant().toMap()["info"].toMap()["host"].toString();

      this -> openConnection(host);
    }

  }
}

