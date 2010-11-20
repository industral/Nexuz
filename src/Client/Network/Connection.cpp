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
      ::close(this -> sock);
    }

    void Connection::run() {
      struct sockaddr_in listenAddr;

      NexuzProtocol * p = new NexuzProtocol();

      int listener = socket(AF_INET, SOCK_STREAM, 0);
      if (listener < 0) {
        perror("socket");
        exit(1);
      }

      listenAddr.sin_family = AF_INET;
      listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(listener, (struct sockaddr *) &listenAddr, sizeof(listenAddr)) < 0) {
        perror("bind");
        exit(2);
      }

      QString hostName = "";
      if (this -> getIpAddress(QString("wlan0"), hostName)) {
        emit(setHost(QString("%1:%2").arg(hostName, QString::number(htons(listenAddr.sin_port)))));
      }

      listen(listener, 1);

      while (true) {

        int listenSock = accept(listener, NULL, NULL);
        if (listenSock < 0) {
          perror("accept");
          exit(3);
        }

        while (true) {
          int bytes_read = recv(listenSock, p, sizeof(NexuzProtocol), 0);
          if (bytes_read <= 0) {
            break;
          }

          cout << p -> data << endl;
        }

        ::close(listenSock);
      }

      //      ::close( listenSock);

      exec();
    }

    void Connection::init() {
      connect(this, SIGNAL(setHost(QString)), SLOT(doAuth(QString)));

      this -> start();
    }

    void Connection::auth(const QString & userName, const QString & password, const QString & host) {
      this -> manager = new QNetworkAccessManager();

      QNetworkRequest request;
      QUrl url = QUrl("http://server.nexuz.im:8365/auth");

      QByteArray data;
      data.append(QString("username=%1&password=%2&host=%3").arg(userName, password, host));

      request.setUrl(url);

      this -> reply = this -> manager -> post(request, data);
      connect(reply, SIGNAL(readyRead()), this, SLOT(authHttpFinished()));
      connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
    }

    void Connection::getRosterList(const QList<QVariant> & rosterList) {
      ::Nexuz::GUI::UI::Contacts * contacts = ::Nexuz::GUI::UI::Contacts::Instance();
      contacts -> initRoster(rosterList);
    }

    // --------------------------------------------------------------------
    // Private methods
    // --------------------------------------------------------------------

    Connection::Connection() {
    }

    bool Connection::getIpAddress(QString dev, QString & ip) {
      char ipv4[16];
      struct ifreq ifc;
      int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

      if (sockfd < 0) {
        return false;
      }

      strcpy(ifc.ifr_name, dev.toStdString().c_str());
      int res = ioctl(sockfd, SIOCGIFADDR, &ifc);
      close(sockfd);

      if (res < 0) {
        return false;
      }

      strcpy(ipv4, inet_ntoa(((struct sockaddr_in*) &ifc.ifr_addr)->sin_addr));
      ip = ipv4;

      return true;
    }

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------

    void Connection::authHttpFinished() {
      QScriptValue sv = Helper::Utils::parseJSON(QString(this -> reply -> readAll().data()));

      qDebug() << "auth: " << sv.property("status").toString();

      this -> getRosterList(sv.property("list").toVariant().toList());
    }

    void Connection::slotError(QNetworkReply::NetworkError error) {

      QMetaObject meta = QNetworkReply::staticMetaObject;
      for (int i = 0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("NetworkError")) {
          qDebug() << "Server connect:" << m.valueToKey(error);
          break;
        }
      }

    }

    void Connection::doAuth(QString host) {

      //TODO: hardcode
      Accounts * accounts = new Accounts();
      QList<AccountInfo> accountsInfo = accounts -> getList();

      for (int i = 0; i < accountsInfo.size(); ++i) {
        this -> auth(accountsInfo.at(i).userName, accountsInfo.at(i).password, host);
      }

    }

  }
}

