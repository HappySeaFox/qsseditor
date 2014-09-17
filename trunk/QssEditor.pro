TARGET = QssEditor
TEMPLATE = app
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets printsupport
mac: greaterThan(QT_MAJOR_VERSION, 4): QT *= macextras

NVER1=0
NVER2=5
NVER3=6

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
    LIBS += -lqscintilla2
}

# QScintilla files
DEFINES += SCINTILLA_QT SCI_LEXER

win32|mac {
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
SVNROOT_FOR_COMMIT="svn+ssh://dmitrykx@svn.code.sf.net/p/qsseditor/code"
SVNROOT_FOR_DOWNLOAD="http://sourceforge.net/p/qsseditor/code/HEAD/tree/trunk"
HTTPROOT="http://sourceforge.net/p/qsseditor"
DOWNLOADROOT="http://sourceforge.net/projects/qsseditor"

DEFINES += SVNROOT_FOR_DOWNLOAD=$$sprintf("\"\\\"%1\\\"\"", $$SVNROOT_FOR_DOWNLOAD)
DEFINES += HTTPROOT=$$sprintf("\"\\\"%1\\\"\"", $$HTTPROOT)
DEFINES += DOWNLOADROOT=$$sprintf("\"\\\"%1\\\"\"", $$DOWNLOADROOT)

# files to copy to the distribution
greaterThan(QT_MAJOR_VERSION, 4) {
    IMAGEPLUGINS=qico.dll qjpeg.dll
    QTLIBS=Qt5Core.dll Qt5Gui.dll Qt5Widgets.dll
    QTPLATFORMS=qminimal.dll qoffscreen.dll qwindows.dll
} else {
    IMAGEPLUGINS=qico4.dll qjpeg4.dll
    QTLIBS=QtCore4.dll QtGui4.dll
}

isEmpty(HOST64) {
    MINGW_BUILD_TYPE=dw2
} else {
    MINGW_BUILD_TYPE=seh
}

MINGWLIBS=libgcc_s_$${MINGW_BUILD_TYPE}-1.dll libwinpthread-1.dll libstdc++-6.dll

LICENSES=LICENSE.txt

tag.commands += $$mle(echo "$$VERSION"> "\"$${_PRO_FILE_PWD_}/QssEditor-version.tag\"")
tag.commands += $$mle(svn -m "\"$$VERSION file tag\"" commit "\"$${_PRO_FILE_PWD_}/QssEditor-version.tag\"")
tag.commands += $$mle(svn -m "\"$$VERSION tag\"" copy "\"$$SVNROOT_FOR_COMMIT/trunk\"" "\"$$SVNROOT_FOR_COMMIT/tags/$$VERSION\"")
QMAKE_EXTRA_TARGETS += tag

!isEmpty(ZIP) {
    message("7Z is found, will create custom dist targets")

    # source archive
    T="$${OUT_PWD}/qsseditor-$$VERSION"
    distsrc.commands += $$mle(if exist \"$$T\" rd /S /Q \"$$T\")
    distsrc.commands += $$mle(svn export $$_PRO_FILE_PWD_ \"$$T\")
    distsrc.commands += $$mle(del /F /Q qsseditor-$${VERSION}.zip)
    distsrc.commands += $$mle($$ZIP a -r -tzip -mx=9 qsseditor-$${VERSION}.zip \"$$T\")
    distsrc.commands += $$mle(rd /S /Q \"$$T\")

    QMAKE_EXTRA_TARGETS += distsrc

    # standalone binary
    T="$${OUT_PWD}/qsseditor-standalone-$$VERSION"

    distbin.commands += $$mle(if exist \"$$T\" rd /S /Q \"$$T\")
    distbin.commands += $$mle(mkdir \"$$T\")
    distbin.commands += $$mle(mkdir \"$$T/platforms\")
    distbin.commands += $$mle(mkdir \"$$T/imageformats\")
    distbin.commands += $$mle(mkdir \"$$T/translations\")

    # binary & necessary files
    distbin.commands += $$mle(copy /y \"$${OUT_PWD}/$(DESTDIR_TARGET)\" \"$$T\")

    for(ql, QTLIBS) {
        distbin.commands += $$mle(copy /y \"$$[QT_INSTALL_BINS]\\$$ql\" \"$$T\")
    }

    for(qp, QTPLATFORMS) {
        distbin.commands += $$mle(copy /y \"$$[QT_INSTALL_PLUGINS]\\platforms\\$$qp\" \"$$T/platforms\")
    }

    for(ml, MINGWLIBS) {
        distbin.commands += $$mle(copy /y \"$$GCCDIR\\$$ml\" \"$$T\")
    }

    for(ip, IMAGEPLUGINS) {
        distbin.commands += $$mle(copy /y \"$$[QT_INSTALL_PLUGINS]\\imageformats\\$$ip\" \"$$T/imageformats\")
    }

    for(qm, QMFILES) {
        distbin.commands += $$mle(copy /y \"$$qm\" \"$$T/translations\")
    }

    for(l, LANGUAGES) {
        l=$$[QT_INSTALL_TRANSLATIONS]\\qt_$${l}.qm
        exists($$l) {
            distbin.commands += $$mle(copy /y \"$$l\" \"$$T/translations\")
        }
    }

    for(lc, LICENSES) {
        distbin.commands += $$mle(copy /y \"$${_PRO_FILE_PWD_}\\$$lc\" \"$$T\")
    }

    # compress
    distbin.commands += $$mle(del /F /Q qsseditor-standalone-$${VERSION}$${HOST64}.zip)
    distbin.commands += $$mle($$ZIP a -r -tzip -mx=9 qsseditor-standalone-$${VERSION}$${HOST64}.zip \"$$T\")
    distbin.commands += $$mle(rd /S /Q \"$$T\")

    QMAKE_EXTRA_TARGETS += distbin
} else {
    warning("7Z is not found, will not create custom dist targets")
}

INNO_APPID="{{A51E7AC1-A31C-40E7-82B3-D1DF32402DF8}"

exists($$INNO) {
    message("Inno Setup is found, will create a setup file in a custom dist target")

    LANGS=$$system(dir /B \"$$INNO\\..\\Languages\")

    ISS="qsseditor-$${VERSION}.iss"

    iss.commands += $$mle(echo $${LITERAL_HASH}define MyAppName \"QSS Editor\" > $$ISS)
    iss.commands += $$mle(echo $${LITERAL_HASH}define MyAppPublisher \"Dmitry Baryshev\" >> $$ISS)
    iss.commands += $$mle(echo $${LITERAL_HASH}define MyAppURL \"$$HTTPROOT\" >> $$ISS)

    iss.commands += $$mle(echo [Setup] >> $$ISS)

    !isEmpty(HOST64) {
        iss.commands += $$mle(echo ArchitecturesAllowed=x64 >> $$ISS)
        iss.commands += $$mle(echo ArchitecturesInstallIn64BitMode=x64 >> $$ISS)
    }

    iss.commands += $$mle(echo AppId=$$INNO_APPID >> $$ISS)
    iss.commands += $$mle(echo AppName={$${LITERAL_HASH}MyAppName} >> $$ISS)
    iss.commands += $$mle(echo AppVersion=$$VERSION >> $$ISS)
    iss.commands += $$mle(echo AppPublisher={$${LITERAL_HASH}MyAppPublisher} >> $$ISS)
    iss.commands += $$mle(echo AppPublisherURL={$${LITERAL_HASH}MyAppURL} >> $$ISS)
    iss.commands += $$mle(echo AppSupportURL={$${LITERAL_HASH}MyAppURL}/wiki/discussion >> $$ISS)
    iss.commands += $$mle(echo AppUpdatesURL={$${LITERAL_HASH}MyAppURL} >> $$ISS)
    iss.commands += $$mle(echo DefaultDirName={pf}\\{$${LITERAL_HASH}MyAppName} >> $$ISS)
    iss.commands += $$mle(echo DefaultGroupName={$${LITERAL_HASH}MyAppName} >> $$ISS)
    iss.commands += $$mle(echo LicenseFile=$${_PRO_FILE_PWD_}\\LICENSE.txt >> $$ISS)
    iss.commands += $$mle(echo OutputDir=. >> $$ISS)
    iss.commands += $$mle(echo OutputBaseFilename=qsseditor-setup-$${VERSION}$${HOST64} >> $$ISS)
    iss.commands += $$mle(echo SetupIconFile=$${_PRO_FILE_PWD_}\\images\\qsseditor.ico >> $$ISS)
    iss.commands += $$mle(echo Compression=lzma >> $$ISS)
    iss.commands += $$mle(echo SolidCompression=yes >> $$ISS)
    iss.commands += $$mle(echo UninstallDisplayName={$${LITERAL_HASH}MyAppName} >> $$ISS)
    iss.commands += $$mle(echo UninstallDisplayIcon={app}\\$${TARGET}.exe >> $$ISS)
    iss.commands += $$mle(echo MinVersion="0,5.1" >> $$ISS)

    !isEmpty(SIGNTOOL):exists($$CERT) {
        iss.commands += $$mle(echo SignTool=bps sign /d \$\$qQSS Editor\$\$q /du \$\$q$$HTTPROOT\$\$q /f \$\$q$$CERT\$\$q /tr \$\$q$$RFC3161_SERVER\$\$q /v \$\$q\$\$f\$\$q >> $$ISS)
    }

    iss.commands += $$mle(echo [Languages] >> $$ISS)

    for(lng, LANGS) {
        lng = $$find(lng, .isl$)

        !isEmpty(lng) {
            lngname=$$lng
            lngname ~= s/\\./x

            exists($${_PRO_FILE_PWD_}\\isl\\$$lng) {
                F=,$${_PRO_FILE_PWD_}\\isl\\$$lng
            } else {
                F=
            }

            iss.commands += $$mle(echo Name: \"$$lngname\"; MessagesFile: \"compiler:Languages\\$$lng$$F\" >> $$ISS)
        }
    }

    iss.commands += $$mle(echo [Tasks] >> $$ISS)
    iss.commands += $$mle(echo Name: \"desktopicon\"; Description: \"{cm:CreateDesktopIcon}\"; GroupDescription: \"{cm:AdditionalIcons}\" >> $$ISS)
    iss.commands += $$mle(echo Name: \"quicklaunchicon\"; Description: \"{cm:CreateQuickLaunchIcon}\"; GroupDescription: \"{cm:AdditionalIcons}\"; OnlyBelowVersion: "0,6.1" >> $$ISS)

    iss.commands += $$mle(echo [Files] >> $$ISS)
    iss.commands += $$mle(echo Source: \"$${OUT_PWD}/$(DESTDIR_TARGET)\"; DestDir: \"{app}\"; Flags: ignoreversion >> $$ISS)

    for(lc, LICENSES) {
        iss.commands += $$mle(echo Source: \"$${_PRO_FILE_PWD_}\\$$lc\"; DestDir: \"{app}\"; Flags: ignoreversion >> $$ISS)
    }

    for(qm, QMFILES) {
        iss.commands += $$mle(echo Source: \"$$qm\"; DestDir: \"{app}/translations\"; Flags: ignoreversion >> $$ISS)
    }

    for(l, LANGUAGES) {
        l=$$[QT_INSTALL_TRANSLATIONS]\\qt_$${l}.qm
        exists($$l) {
            iss.commands += $$mle(echo Source: \"$$l\"; DestDir: \"{app}/translations\"; Flags: ignoreversion >> $$ISS)
        }
    }

    for(ql, QTLIBS) {
        iss.commands += $$mle(echo Source: \"$$[QT_INSTALL_BINS]\\$$ql\"; DestDir: \"{app}\"; Flags: ignoreversion >> $$ISS)
    }

    for(qp, QTPLATFORMS) {
        iss.commands += $$mle(echo Source: \"$$[QT_INSTALL_PLUGINS]\\platforms\\$$qp\"; DestDir: \"{app}\\platforms\"; Flags: ignoreversion >> $$ISS)
    }

    for(ip, IMAGEPLUGINS) {
        iss.commands += $$mle(echo Source: \"$$[QT_INSTALL_PLUGINS]\\imageformats\\$$ip\"; DestDir: \"{app}\\imageformats\"; Flags: ignoreversion >> $$ISS)
    }

    for(ml, MINGWLIBS) {
        iss.commands += $$mle(echo Source: \"$$GCCDIR\\$$ml\"; DestDir: \"{app}\"; Flags: ignoreversion >> $$ISS)
    }

    iss.commands += $$mle(echo [Icons] >> $$ISS)
    iss.commands += $$mle(echo Name: \"{group}\\{$${LITERAL_HASH}MyAppName}\"; Filename: \"{app}\\$${TARGET}.exe\" >> $$ISS)
    iss.commands += $$mle(echo Name: \"{group}\\{cm:UninstallProgram","{$${LITERAL_HASH}MyAppName}}\"; Filename: \"{uninstallexe}\" >> $$ISS)
    iss.commands += $$mle(echo Name: \"{commondesktop}\\{$${LITERAL_HASH}MyAppName}\"; Filename: \"{app}\\$${TARGET}.exe\"; Tasks: desktopicon >> $$ISS)
    iss.commands += $$mle(echo Name: \"{userappdata}\\Microsoft\\Internet Explorer\\Quick Launch\\{$${LITERAL_HASH}MyAppName}\"; Filename: \"{app}\\$${TARGET}.exe\"; Tasks: quicklaunchicon >> $$ISS)

    iss.commands += $$mle(echo [Run] >> $$ISS)
    iss.commands += $$mle(echo Filename: \"{app}\\$${TARGET}.exe\"; Description: \"{cm:LaunchProgram","{$${LITERAL_HASH}StringChange(MyAppName"," \'&\'"," \'&&\')}}\"; Flags: nowait postinstall skipifsilent >> $$ISS)
    iss.commands += $$mle(echo ;Filename: \"{$${LITERAL_HASH}MyAppURL}/wiki/changelog\"; Flags: nowait shellexec >> $$ISS)

    iss.commands += $$mle(echo [Code] >> $$ISS)
    iss.commands += $$mle(echo procedure CurStepChanged(CurStep: TSetupStep); >> $$ISS)
    iss.commands += $$mle(echo var >> $$ISS)
    iss.commands += $$mle(echo ResultCode: Integer; >> $$ISS)
    iss.commands += $$mle(echo Uninstall: String; >> $$ISS)
    iss.commands += $$mle(echo UninstallQuery : String; >> $$ISS)
    iss.commands += $$mle(echo begin >> $$ISS)
    iss.commands += $$mle(echo   UninstallQuery := ExpandConstant(\'Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{$${LITERAL_HASH}emit SetupSetting(\"AppId\")}_is1\'); >> $$ISS)

    iss.commands += $$mle(echo   if (CurStep = ssInstall) then begin >> $$ISS)
    iss.commands += $$mle(echo     if RegQueryStringValue(HKLM, UninstallQuery, \'UninstallString\', Uninstall) >> $$ISS)
    iss.commands += $$mle(echo        or RegQueryStringValue(HKCU, UninstallQuery, \'UninstallString\', Uninstall) then begin >> $$ISS)
    iss.commands += $$mle(echo       if not Exec(RemoveQuotes(Uninstall), \'/VERYSILENT\', \'\', SW_SHOWNORMAL, ewWaitUntilTerminated, ResultCode) then begin >> $$ISS)
    iss.commands += $$mle(echo         MsgBox(SysErrorMessage(ResultCode), mbCriticalError, MB_OK); >> $$ISS)
    iss.commands += $$mle(echo         Abort(); >> $$ISS)
    iss.commands += $$mle(echo       end; >> $$ISS)
    iss.commands += $$mle(echo     end; >> $$ISS)
    iss.commands += $$mle(echo   end; >> $$ISS)
    iss.commands += $$mle(echo end; >> $$ISS)

    QMAKE_EXTRA_TARGETS += iss
    QMAKE_EXTRA_TARGETS *= distbin

    !isEmpty(SIGNTOOL):exists($$CERT) {
        ADD="\"/sbps=$$SIGNTOOL \$\$p\""
    }

    distbin.depends += iss
    distbin.commands += $$mle(\"$$INNO\" /o. $$ADD \"$$ISS\")
    distbin.commands += $$mle(del /F /Q \"$$ISS\")
} else {
    warning("Inno Setup is not found, will not create a setup file in a custom dist target")
}
