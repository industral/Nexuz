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

#include "Utils.hpp"

namespace Nexuz {
  namespace GUI {
    namespace Helper {

      Utils::Utils() {
      }

      Utils::~Utils() {
      }

      QWidget * Utils::loadUI(const QString & uiPath) {
        QUiLoader loader;

        QFile file(uiPath);
        if (file.open(QFile::ReadOnly) == true) {
          QWidget * widget = loader.load(&file, 0);

          file.close();
          return widget;
        } else {
          cerr << "Couldn't find specified file: " << uiPath.toStdString() << endl;
          cerr << "Maybe it missed in qrc file, or wrong pointed it's path" << endl;
          exit(1);
        }
      }

      void Utils::toggleLayout(QWidget * widget, QString layoutName, bool show) {
        QBoxLayout * layerWidget = widget -> findChild<QBoxLayout *> (layoutName);

        // run across all widgets and set them visible/unvisible
        for (int i = 0; i < layerWidget -> count(); ++i) {
          layerWidget -> itemAt(i) -> widget() -> setVisible(show);
        }
      }

      void Utils::toggleLayout(QWidget * widget, const QList<QString> & layoutList, bool show) {
        for (int i = 0; i < layoutList.size(); ++i) {
          toggleLayout(widget, layoutList.at(i), show);
        }
      }

      void Utils::toggleWidget(QWidget * widget, QString widgetName, bool show) {
        QWidget * toggledWidget = widget -> findChild<QWidget *> (widgetName);
        toggledWidget -> setVisible(show);
      }

      void Utils::toggleWidget(QWidget * widget, const QList<QString> & widgetList, bool show) {
        for (int i = 0; i < widgetList.size(); ++i) {
          toggleWidget(widget, widgetList.at(i), show);
        }
      }

    }
  }
}
