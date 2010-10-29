CONFIG      += uitools qt warn_on DEBUG_MODE #RELEASE_MODE
RESOURCES   = Nexuz.qrc

SOURCES     = src/Client/GUI/Helper/LoadUI.cpp \
              src/Client/GUI/MainWindow.cpp \
              src/Client/GUI/main.cpp

HEADERS     = src/Client/GUI/MainWindow.hpp \
              src/Client/GUI/Helper/LoadUI.hpp \
              src/Client/include.hpp

Libraries = 

StaticLibraries = 

CONFIG(DEBUG_MODE) {
  QMAKE_CXXFLAGS += -ggdb -Wall -W
  QMAKE_CFLAGS += -ggdb -Wall -W

  for(lib, Libraries) {
    LIBS += -l$$lib
  }
} else {
  QMAKE_CXXFLAGS += -O3
  QMAKE_CFLAGS += -O3
  
  for(lib, StaticLibraries) {
    LIBS += "/usr/lib/lib$$lib".a
  }
}

INCLUDEPATH = src/Client
OBJECTS_DIR = tmp/objects
MOC_DIR = tmp/moc
RCC_DIR =  tmp/rcc