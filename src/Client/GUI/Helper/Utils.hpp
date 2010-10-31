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

#ifndef _NEXUZ_GUI_HELPER_UTILS_HPP_
#define _NEXUZ_GUI_HELPER_UTILS_HPP_

#include <include.hpp>

namespace Nexuz {
  namespace GUI {
    namespace Helper {

      /**
       * Utils class.
       */
      class Utils {
        public:
          /**
           * Default constructor.
           */
          Utils();

          /**
           * Default destructor.
           */
          ~Utils();

          /**
           * Help to load UI resource files. Very simple in use:
           * @code
           * QWidget * widget = LoadUI::loadUI(":/forms/designer/Collection.ui");
           * @endcode
           * Next, you can access any elements in widget:
           * @code
           * widget -> findChild < QPushButton * > ("closeButton");
           * @endcode
           *
           * @param uiPath path to UI resource file.
           *
           * @return QWidget pointer.
           */
          static QWidget * loadUI(const QString & uiPath);

          /**
           * Show/Hide layout.
           *
           * @param widget widget object
           * @param layoutName layout name
           * @param show show or hide all widgets in layout
           */
          static void toggleLayout(QWidget * widget, QString layoutName, bool show);
        private:
      };

    }
  }
}

#endif
