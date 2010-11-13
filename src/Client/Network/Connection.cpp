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

#include "Connection.hpp"

namespace Nexuz {
  namespace Network {

    // --------------------------------------------------------------------
    // Public methods
    // --------------------------------------------------------------------

    // Singleton
    Connection * Connection::_connection = NULL;

    Connection * Connection::Instance() {
      if (_connection == NULL) {
        _connection = new Connection();
      }
      return _connection;
    }

    Connection::~Connection() {
      ::close(sock);
    }

    void Connection::init() {
      struct sockaddr_in addr;

      this -> sock = socket(AF_INET, SOCK_STREAM, 0);
      if (this -> sock < 0) {
        perror("socket");
        exit(1);
      }

      addr.sin_family = AF_INET;
      addr.sin_port = htons(3425);
      addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
      if (::connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
      }
    }

    void Connection::write(NexuzProtocol data, int size) {
      send(sock, (void *) &data, size, 0);
    }

    bool Connection::auth(const QString & userName, const QString & password) {
      this -> manager = new QNetworkAccessManager();

      QNetworkRequest request;
      QUrl url = QUrl("http://server.nexuz.im:8365/auth");

      QByteArray data;
      data.append(QString("userName=%1&password=%2").arg(userName, password));

      request.setUrl(url);

      this -> reply = this -> manager -> post(request, data);
      connect(reply, SIGNAL(readyRead()), this, SLOT(httpFinished()));
      connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));

      return true;
    }

    // --------------------------------------------------------------------
    // Private methods
    // --------------------------------------------------------------------

    Connection::Connection(QWidget *parent) :
      QWidget(parent) {
    }

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------

    void Connection::httpFinished() {
      QScriptValue sv = Helper::Utils::parseJSON(QString(this -> reply -> readAll().data()));

      qDebug() << sv.property("0").property("couchdb").toString();

      //      if (sc.property("result").isArray()) {
      //        QScriptValueIterator it(sc.property("result"));
      //        while (it.hasNext()) {
      //          it.next();
      //          qDebug("Nick %s", it.value().property("nick").toString().toStdString().c_str());
      //        }
      //      }
    }

    void Connection::slotError(QNetworkReply::NetworkError error) {

      QMetaObject meta = QNetworkReply::staticMetaObject;
      for (int i = 0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("NetworkError")) {
          cerr << m.valueToKey(error) << endl;
          break;
        }
      }

    }

  }
}

