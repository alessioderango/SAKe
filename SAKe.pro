#-------------------------------------------------
#
# Project created by QtCreator 2017-07-22T12:10:17
#
#-------------------------------------------------

QT += core gui
QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SAKe2
TEMPLATE = app
QMAKE_CXXFLAGS+= -fopenmp
LIBS += -fopenmp
QT += opengl
DEFINES += QCUSTOMPLOT_USE_OPENGL
LIBS += -lOpengl32
CONFIG += console
CONFIG += c++14


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    TreeModel.cpp \
    xmlmanager.cpp \
    qcustomplot.cpp \
    HandlerCSV.cpp \
    SAke/eoGraphFitenessStat.cpp \
    SAke/SAKeController.cpp \
    SAke/SAKeEA.cpp \
    validation.cpp \
    ValidationController.cpp \
    Regression.cpp \
    Regression/funtciontype.cpp \
    Regression/make_OneMax.cpp \
    Regression/OneMaxEA.cpp \
    Regression/parameters.cpp \
    Regression/regressioncontroller.cpp \
    CustomPlotRegression.cpp \
    CustomPlotRegressionPreviewKernel.cpp \
    controlpoints.cpp \
    Regression/Genotype.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    TreeModel.h \
    xmlmanager.h \
    qcustomplot.h \
    Rain.h \
    HandlerCSV.h \
    SAke/db/DBmanager.h \
    SAke/Activation.h \
    SAke/eoElitistReplacement.h \
    SAke/eoGenContinueMy.h \
    SAke/eoGraphFitenessStat.h \
    SAke/eoMySelection.h \
    SAke/eoMySGA.h \
    SAke/eoSAKe.h \
    SAke/eosakedettournamentselect.h \
    SAke/eoSAKeEvalFunc.h \
    SAke/eoSAKeInit.h \
    SAke/eoSAKeMutation.h \
    SAke/eoSAKeQuadCrossover.h \
    SAke/eosakestochtournamentselect.h \
    SAke/eoSGAGenerational.h \
    SAke/eoSGAGenerationalMultiObjects.h \
    SAke/eoSGASteadyState.h \
    SAke/eoSGASteadyStateMultiObjects.h \
    SAke/make_algo_scalar_my.h \
    SAke/make_checkpoint_my.h \
    SAke/make_continue_my.h \
    SAke/make_genotype_SAKe.h \
    SAke/make_op_SAKe.h \
    SAke/make_pop_my.h \
    SAke/Rain.h \
    SAke/SAKeController.h \
    SAke/selectiondeltacr.h \
    SAke/selectionfitness.h \
    SAke/selectionmomentoprimoordine.h \
    SAke/selectionsize.h \
    SAke/selectionstrategy.h \
    SAke/Ym.h \
    Activation.h \
    validation.h \
    ValidationController.h \
    myvalidatordouble.h \
    Regression.h \
    SAke/eoSAKeEvalFuncEqualWeights.h \
    SAke/eoSAKeEvalFuncAUCROC.h \
    SAke/eoSAKeEvalFuncGMDn.h \
    Regression/eoGenContinueMy.h \
    Regression/eoGraphFitenessStat.h \
    Regression/eoMySGA.h \
    Regression/eoOneMax.h \
    Regression/eoOneMaxEvalFunc.h \
    Regression/eoOneMaxInit.h \
    Regression/eoOneMaxMutation.h \
    Regression/eoOneMaxQuadCrossover.h \
    Regression/eoSGAGenerational.h \
    Regression/eoSGASteadyState.h \
    Regression/funtciontype.h \
    Regression/make_algo_scalar_my.h \
    Regression/make_checkpoint_my.h \
    Regression/make_continue_my.h \
    Regression/make_genotype_OneMax.h \
    Regression/make_op_OneMax.h \
    Regression/parameters.h \
    Regression/regressioncontroller.h \
    CustomPlotRegression.h \
    CustomPlotRegressionPreviewKernel.h \
    controlpoints.h \
    utilis.h \
    Regression/Genotype.h

FORMS    += mainwindow.ui \
    dialog.ui \
    fitnessplot.ui \
    validation.ui \
    regression.ui

DISTFILES +=

RESOURCES += \
    myresource.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leo
else:unix: LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leo

INCLUDEPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src
DEPENDPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeo.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeo.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/eo.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/eod.lib
else:unix: PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeo.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leoutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leoutils
else:unix: LIBS += -L$$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/ -leoutils

INCLUDEPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src
DEPENDPATH += $$PWD/../paradiseo-master/paradiseo-master/eo/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeoutils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeoutils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/eoutils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/eoutilsd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../paradiseo-master/paradiseo-master/build5.3/lib/libeoutils.a


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw53-mt-1_60
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw53-mt-d-1_60
else:unix: LIBS += -L$$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/ -lboost_date_time-mgw53-mt-1_60

INCLUDEPATH += $$PWD/../boost_1_60_0/boost_1_60_0/
DEPENDPATH += $$PWD/../boost_1_60_0/boost_1_60_0/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw53-mt-1_60.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw53-mt-d-1_60.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/boost_date_time-mgw53-mt-1_60.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/boost_date_time-mgw53-mt-d-1_60.lib
else:unix: PRE_TARGETDEPS += $$PWD/../boost_1_60_0/boost_1_60_0/stage/lib/libboost_date_time-mgw53-mt-1_60.a
