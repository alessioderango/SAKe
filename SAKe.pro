TEMPLATE = app

QT += qml xml quick widgets
greaterThan(QT_MAJOR_VERSION, 4) :QT+= widgets printsupport declarative


#CONFIG += console

SOURCES += main.cpp \
    CustomPlotItem.cpp \
    qcustomplot.cpp \
    SAke/SAKeEA.cpp \
    SAke/SAKeController.cpp \
    SAke/eoGraphFitenessStat.cpp \
    SAKeStart.cpp \
    CustomPlotMobilityFunction.cpp \
    CustomPlotKernel.cpp \
    timesupport.cpp \
    updateprojects.cpp \
    xmlmanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CustomPlotItem.h \
    qcustomplot.h \
    SAke/Activation.h \
    SAke/eoSAKe.h \
    SAke/eoSAKeEvalFunc.h \
    SAke/eoSAKeInit.h \
    SAke/eoSAKeMutation.h \
    SAke/eoSAKeQuadCrossover.h \
    SAke/make_genotype_SAKe.h \
    SAke/make_op_SAKe.h \
    SAke/Ym.h \
   SAke/db/DBmanager.h \
    SAke/Rain.h \
    SAke/SAKeController.h \
    SAke/eoGraphFitenessStat.h \
    SAke/make_checkpoint_my.h \
    SAKeStart.h \
    MyEventFilter.h \
    CustomPlotMobilityFunction.h \
    SAke/eoGenContinueMy.h \
    SAke/make_continue_my.h \
    CustomPlotKernel.h \
    SAke/make_algo_scalar_my.h \
    SAke/eoElitistReplacement.h \
    SAke/eoMySelection.h \
    SAke/eoMySGA.h \
    timesupport.h \
    SAke/eoSGAReplacement.h \
    update.h \
    updateprojects.h \
    xmlmanager.h

CONFIG += c++11
QMAKE_CXXFLAGS += -march=i686
QMAKE_LFLAGS+= --enable-auto-import
#QMAKE_CXXFLAGS+= -fopenmp
#QMAKE_LFLAGS +=  -fopenmp
#LIBS += -fopenmp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Sake/libpqxx-4.0/src/.libs/release/ -lpqxx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Sake/libpqxx-4.0/src/.libs/debug/ -lpqxx
#else:unix: LIBS += -L$$PWD/../Sake/libpqxx-4.0/src/.libs/ -lpqxx

#INCLUDEPATH += $$PWD/../Sake/libpqxx-4.0/include
#DEPENDPATH += $$PWD/../Sake/libpqxx-4.0/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Sake/libpqxx-4.0/src/.libs/release/libpqxx.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Sake/libpqxx-4.0/src/.libs/debug/libpqxx.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Sake/libpqxx-4.0/src/.libs/release/pqxx.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Sake/libpqxx-4.0/src/.libs/debug/pqxx.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../Sake/libpqxx-4.0/src/.libs/libpqxx.a

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/PostgreSQL/9.4/lib/release/ -lpq
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/PostgreSQL/9.4/lib/debug/ -lpq
#else:unix: LIBS += -L$$PWD/../../../opt/PostgreSQL/9.4/lib/ -lpq

#INCLUDEPATH += $$PWD/../../../opt/PostgreSQL/9.4/include
#DEPENDPATH += $$PWD/../../../opt/PostgreSQL/9.4/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../opt/PostgreSQL/9.4/lib/release/libpq.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../opt/PostgreSQL/9.4/lib/debug/libpq.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../opt/PostgreSQL/9.4/lib/release/pq.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../opt/PostgreSQL/9.4/lib/debug/pq.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../opt/PostgreSQL/9.4/lib/libpq.a

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../git/paradiseo/build/lib/release/ -leo
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../git/paradiseo/build/lib/debug/ -leo
#else:unix: LIBS += -L$$PWD/../git/paradiseo/build/lib/ -leo

#INCLUDEPATH += $$PWD/../git/paradiseo/eo/src
#DEPENDPATH += $$PWD/../git/paradiseo/eo/src

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/release/libeo.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/debug/libeo.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/release/eo.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/debug/eo.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/libeo.a

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../git/paradiseo/build/lib/release/ -leoutils
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../git/paradiseo/build/lib/debug/ -leoutils
#else:unix: LIBS += -L$$PWD/../git/paradiseo/build/lib/ -leoutils

#INCLUDEPATH += $$PWD/../git/paradiseo/eo/src
#DEPENDPATH += $$PWD/../git/paradiseo/eo/src

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/release/libutils.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/debug/libutils.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/release/eoutils.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/debug/eoutils.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../git/paradiseo/build/lib/libeoutils.a








win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leo
else:unix: LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leo

INCLUDEPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src
DEPENDPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeo.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeo.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/eo.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/eod.lib
else:unix: PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeo.a





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leoutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leoutils
else:unix: LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build/lib/ -leoutils

INCLUDEPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src
DEPENDPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeoutils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeoutils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/eoutils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/eoutilsd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build/lib/libeoutils.a




#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../pqxx-4.0.1/pqxx-4.0.1/ -lpqxx
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../pqxx-4.0.1/pqxx-4.0.1/ -lpqxx
#else:unix: LIBS += -L$$PWD/../pqxx-4.0.1/pqxx-4.0.1/ -lpqxx

#INCLUDEPATH += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/include
#DEPENDPATH += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/libpqxx.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/libpqxx.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/pqxx.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/pqxxd.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../pqxx-4.0.1/pqxx-4.0.1/libpqxx.a



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw48-mt-1_60
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw48-mt-d-1_60
else:unix: LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw48-mt-1_60

INCLUDEPATH += $$PWD/../boost_1_60_0/boost_1_60_0/
DEPENDPATH += $$PWD/../boost_1_60_0/boost_1_60_0/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw48-mt-1_60.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw48-mt-d-1_60.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/boost_date_time-mgw48-mt-1_60.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/boost_date_time-mgw48-mt-d-1_60.lib
else:unix: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw48-mt-1_60.a
