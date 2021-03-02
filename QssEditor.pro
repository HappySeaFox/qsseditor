TARGET = QssEditor
TEMPLATE = app
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets printsupport

mac {
    greaterThan(QT_MAJOR_VERSION, 4): QT *= macextras
}

NVER1=0
NVER2=6
NVER3=1

include($$_PRO_FILE_PWD_/QssEditor-common.pri)

SOURCES += main.cpp \
        qsseditor.cpp \
    qscilexerqss.cpp \
    project.cpp \
    settings.cpp \
    searchandreplace.cpp \
    options.cpp \
    about.cpp

HEADERS += qsseditor.h \
    qscilexerqss.h \
    project.h \
    settings.h \
    searchandreplace.h \
    options.h \
    about.h \
    tools.h

FORMS += qsseditor.ui \
    searchandreplace.ui \
    options.ui \
    about.ui

RESOURCES += qsseditor.qrc

RC_FILE = qsseditor.rc

unix:!mac {
    CONFIG += qscintilla2
}

QSCINTILLA_INTERNAL=$$(QSCINTILLA_INTERNAL)
equals(QSCINTILLA_INTERNAL, 1)|win32|mac {
    message("Using internal QScintilla")

    # QScintilla files
    DEFINES += SCINTILLA_QT SCI_LEXER

    INCLUDEPATH += $$_PRO_FILE_PWD_/qscintilla $$_PRO_FILE_PWD_/qscintilla/include $$_PRO_FILE_PWD_/qscintilla/lexlib $$_PRO_FILE_PWD_/qscintilla/Qt4Qt5 $$_PRO_FILE_PWD_/qscintilla/src
    DEPENDPATH += $$_PRO_FILE_PWD_/qscintilla $$_PRO_FILE_PWD_/qscintilla/include $$_PRO_FILE_PWD_/qscintilla/lexlib $$_PRO_FILE_PWD_/qscintilla/Qt4Qt5 $$_PRO_FILE_PWD_/qscintilla/src

    HEADERS += \
            qscintilla/Qt4Qt5/Qsci/qsciglobal.h \
            qscintilla/Qt4Qt5/Qsci/qsciscintilla.h \
            qscintilla/Qt4Qt5/Qsci/qsciscintillabase.h \
            qscintilla/Qt4Qt5/Qsci/qsciabstractapis.h \
            qscintilla/Qt4Qt5/Qsci/qsciapis.h \
            qscintilla/Qt4Qt5/Qsci/qscicommand.h \
            qscintilla/Qt4Qt5/Qsci/qscicommandset.h \
            qscintilla/Qt4Qt5/Qsci/qscidocument.h \
            qscintilla/Qt4Qt5/Qsci/qscilexer.h \
            qscintilla/Qt4Qt5/Qsci/qscilexercss.h \
            qscintilla/Qt4Qt5/Qsci/qscilexercustom.h \
            qscintilla/Qt4Qt5/Qsci/qscimacro.h \
            qscintilla/Qt4Qt5/Qsci/qsciprinter.h \
            qscintilla/Qt4Qt5/Qsci/qscistyle.h \
            qscintilla/Qt4Qt5/Qsci/qscistyledtext.h \
            qscintilla/Qt4Qt5/ListBoxQt.h \
            qscintilla/Qt4Qt5/SciClasses.h \
            qscintilla/Qt4Qt5/SciNamespace.h \
            qscintilla/Qt4Qt5/ScintillaQt.h \
            qscintilla/include/ILexer.h \
            qscintilla/include/Platform.h \
            qscintilla/include/SciLexer.h \
            qscintilla/include/Scintilla.h \
            qscintilla/include/ScintillaWidget.h \
            qscintilla/lexlib/Accessor.h \
            qscintilla/lexlib/CharacterCategory.h \
            qscintilla/lexlib/CharacterSet.h \
            qscintilla/lexlib/LexAccessor.h \
            qscintilla/lexlib/LexerBase.h \
            qscintilla/lexlib/LexerModule.h \
            qscintilla/lexlib/LexerNoExceptions.h \
            qscintilla/lexlib/LexerSimple.h \
            qscintilla/lexlib/OptionSet.h \
            qscintilla/lexlib/PropSetSimple.h \
            qscintilla/lexlib/StyleContext.h \
            qscintilla/lexlib/SubStyles.h \
            qscintilla/lexlib/WordList.h \
            qscintilla/src/AutoComplete.h \
            qscintilla/src/CallTip.h \
            qscintilla/src/CaseConvert.h \
            qscintilla/src/CaseFolder.h \
            qscintilla/src/Catalogue.h \
            qscintilla/src/CellBuffer.h \
            qscintilla/src/CharClassify.h \
            qscintilla/src/ContractionState.h \
            qscintilla/src/Decoration.h \
            qscintilla/src/Document.h \
            qscintilla/src/Editor.h \
            qscintilla/src/ExternalLexer.h \
            qscintilla/src/FontQuality.h \
            qscintilla/src/Indicator.h \
            qscintilla/src/KeyMap.h \
            qscintilla/src/LineMarker.h \
            qscintilla/src/Partitioning.h \
            qscintilla/src/PerLine.h \
            qscintilla/src/PositionCache.h \
            qscintilla/src/RESearch.h \
            qscintilla/src/RunStyles.h \
            qscintilla/src/ScintillaBase.h \
            qscintilla/src/Selection.h \
            qscintilla/src/SplitVector.h \
            qscintilla/src/Style.h \
            qscintilla/src/UnicodeFromUTF8.h \
            qscintilla/src/UniConversion.h \
            qscintilla/src/ViewStyle.h \
            qscintilla/src/XPM.h

    SOURCES += \
            qscintilla/Qt4Qt5/qsciscintilla.cpp \
            qscintilla/Qt4Qt5/qsciscintillabase.cpp \
            qscintilla/Qt4Qt5/qsciabstractapis.cpp \
            qscintilla/Qt4Qt5/qsciapis.cpp \
            qscintilla/Qt4Qt5/qscicommand.cpp \
            qscintilla/Qt4Qt5/qscicommandset.cpp \
            qscintilla/Qt4Qt5/qscidocument.cpp \
            qscintilla/Qt4Qt5/qscilexer.cpp \
            qscintilla/Qt4Qt5/qscilexercss.cpp \
            qscintilla/Qt4Qt5/qscilexercustom.cpp \
            qscintilla/Qt4Qt5/qscimacro.cpp \
            qscintilla/Qt4Qt5/qsciprinter.cpp \
            qscintilla/Qt4Qt5/qscistyle.cpp \
            qscintilla/Qt4Qt5/qscistyledtext.cpp \
            qscintilla/Qt4Qt5/MacPasteboardMime.cpp \
            qscintilla/Qt4Qt5/InputMethod.cpp \
            qscintilla/Qt4Qt5/SciClasses.cpp \
            qscintilla/Qt4Qt5/ListBoxQt.cpp \
            qscintilla/Qt4Qt5/PlatQt.cpp \
            qscintilla/Qt4Qt5/ScintillaQt.cpp \
            qscintilla/lexers/LexCSS.cpp \
            qscintilla/lexlib/Accessor.cpp \
            qscintilla/lexlib/CharacterCategory.cpp \
            qscintilla/lexlib/CharacterSet.cpp \
            qscintilla/lexlib/LexerBase.cpp \
            qscintilla/lexlib/LexerModule.cpp \
            qscintilla/lexlib/LexerNoExceptions.cpp \
            qscintilla/lexlib/LexerSimple.cpp \
            qscintilla/lexlib/PropSetSimple.cpp \
            qscintilla/lexlib/StyleContext.cpp \
            qscintilla/lexlib/WordList.cpp \
            qscintilla/src/AutoComplete.cpp \
            qscintilla/src/CallTip.cpp \
            qscintilla/src/CaseConvert.cpp \
            qscintilla/src/CaseFolder.cpp \
            qscintilla/src/Catalogue.cpp \
            qscintilla/src/CellBuffer.cpp \
            qscintilla/src/CharClassify.cpp \
            qscintilla/src/ContractionState.cpp \
            qscintilla/src/Decoration.cpp \
            qscintilla/src/Document.cpp \
            qscintilla/src/Editor.cpp \
            qscintilla/src/ExternalLexer.cpp \
            qscintilla/src/Indicator.cpp \
            qscintilla/src/KeyMap.cpp \
            qscintilla/src/LineMarker.cpp \
            qscintilla/src/PerLine.cpp \
            qscintilla/src/PositionCache.cpp \
            qscintilla/src/RESearch.cpp \
            qscintilla/src/RunStyles.cpp \
            qscintilla/src/ScintillaBase.cpp \
            qscintilla/src/Selection.cpp \
            qscintilla/src/Style.cpp \
            qscintilla/src/UniConversion.cpp \
            qscintilla/src/ViewStyle.cpp \
            qscintilla/src/XPM.cpp
}

OTHER_FILES += \
    LICENSE.txt \
    README.txt

# distribution
HTTPROOT="https://github.com/smoked-herring/qsseditor"
DEFINES += HTTPROOT=$$sprintf("\"\\\"%1\\\"\"", $$HTTPROOT)
