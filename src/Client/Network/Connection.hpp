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

#ifndef _NEXUZ_NETWORK_CONNECTION_HPP_
#define _NEXUZ_NETWORK_CONNECTION_HPP_

#include <include.hpp>
#include "Helper/Utils.hpp"
#include "../Process.hpp"
#include "../App/Accounts.hpp"
#include "../GUI/UI/UI_Contacts.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Nexuz {
  namespace Network {

    class Connection: public QThread {
      Q_OBJECT

      public:
        static Connection * Instance();

        ~Connection();

        void init();

        void auth(const QString & userName, const QString & password, const QString & host);
        void getRosterList(const QList < QVariant > & rosterList);
        void run();
      signals:
        void setHost(QString);
      private slots:
        void authHttpFinished();
        void slotError(QNetworkReply::NetworkError err);
        void doAuth(QString);
      private:
        Connection();

        static Connection * _connection;

        bool getIpAddress(QString dev, QString & ip);

        int sock;
        int port;

        QNetworkReply *reply;
        QNetworkAccessManager * manager;
    };

  }
}

#endif
