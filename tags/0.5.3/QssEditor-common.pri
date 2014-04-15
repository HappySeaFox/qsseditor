isEmpty(TARGET) {
    error("TARGET is not defined")
}

!win32:!unix {
    error("QSS Editor must be compiled on Windows or Linux")
}

greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets

INCLUDEPATH += .
DEPENDPATH += .

#QMAKE_CXXFLAGS += -flto
#QMAKE_LFLAGS += -flto

# for testing
#QMAKE_CXXFLAGS += -pedantic -std=c++11

# translation languages
LANGUAGES=en ru zh_CN

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON *= -Wextra

VERSION=$$sprintf("%1.%2.%3", $$NVER1, $$NVER2, $$NVER3)

DEFINES += NVER1=$$NVER1
DEFINES += NVER2=$$NVER2
DEFINES += NVER3=$$NVER3
DEFINES += NVER_STRING=$$sprintf("\"\\\"%1\\\"\"", $$VERSION)

DEFINES += TARGET=$$TARGET

# require at least Windows XP
win32:DEFINES += _WIN32_WINNT=0x0501 WINVER=0x0501

# use fast string concat
DEFINES *= QT_USE_QSTRINGBUILDER

contains(QMAKE_HOST.arch, x86_64) {
    HOST64="-x86_64"
}

win32 {
    SEP="\\"
} unix {
    SEP="/"
}

# generate TRANSLATIONS
defineReplace(gentranslations) {
    for(ts, LANGUAGES) {
        TRANSLATIONS += $${_PRO_FILE_PWD_}$${SEP}ts$${SEP}$${1}_$${ts}.ts
    }
    return ( $$TRANSLATIONS )
}

# search an executable in PATH
defineReplace(findexeWin32) {
    return ( $$system(for %i in ($${1}.exe) do @echo. %~$PATH:i) )
}

defineReplace(findexeUnix) {
    return ( $$system(which $$1) )
}

# escape command to allow multiple lines in Makefile
defineReplace(mle) {
    return ( $$1$$escape_expand(\\n\\t) )
}

# check for svn
win32 {
    SVN=$$findexeWin32("svn")
} unix {
    SVN=$$findexeUnix("svn")
}

# check for gcc
win32 {
    GCC=$$findexeWin32("gcc")
} unix {
    GCC=$$findexeUnix("gcc")
}

GCCDIR=$$dirname(GCC)

win32:isEmpty(GCC) {
    error("MinGW is not found in PATH")
}

TS_PREFIX=$$lower($$TARGET)
TS_PREFIX=$$replace(TS_PREFIX, -, _)

TRANSLATIONS += $$gentranslations($$TS_PREFIX)

message(Translations for $${TS_PREFIX}: $$TRANSLATIONS)

# copy translations
!isEmpty(TRANSLATIONS) {
    QMAKE_POST_LINK += $$mle(lupdate -no-obsolete $$_PRO_FILE_ -ts $$TRANSLATIONS)
}

# lrelease for each ts
for(ts, TRANSLATIONS) {
    QM=$$replace(ts, \\.ts$, .qm)
    QM=$$replace(QM, /, $${SEP})
    QMAKE_POST_LINK += $$mle(lrelease \"$$ts\" -qm \"$$QM\")
}

win32 {
    TRANSLATIONS_DIR="$${OUT_PWD}/$(DESTDIR_TARGET)/../translations"
} unix {
    TRANSLATIONS_DIR="$${OUT_PWD}/translations"
}

win32 {
    QMAKE_POST_LINK += $$mle(if not exist \"$$TRANSLATIONS_DIR\" mkdir \"$$TRANSLATIONS_DIR\")
} unix {
    QMAKE_POST_LINK += $$mle(test -d \"$$TRANSLATIONS_DIR\" || mkdir -p \"$$TRANSLATIONS_DIR\")
}

QMFILES=

# copy .qm files
for(ts, TRANSLATIONS) {
    ts=$$replace(ts, \\.ts$, .qm)
    ts=$$replace(ts, /, $${SEP})
    QMFILES += $$ts
    QMAKE_POST_LINK += $$mle($(COPY) \"$$ts\" \"$$TRANSLATIONS_DIR\")
}

# check for upx
win32 {
    UPX=$$findexeWin32("upx")
} unix {
    UPX=$$findexeUnix("upx")
}

!isEmpty(USEUPX) {
    isEmpty(HOST64):!isEmpty(UPX) {
        message("UPX is found, will pack $$TARGET after linking")

        QMAKE_POST_LINK += $$mle($$UPX -9 \"$${OUT_PWD}/$(DESTDIR_TARGET)\")
        export(QMAKE_POST_LINK)
    } else {
        warning("UPX is not found, will not pack $$TARGET")
    }
}

# check for signtool
win32 {
    SIGNTOOL=$$findexeWin32("signtool")
    CERT=$$dirname(_PRO_FILE_)-certs\\cert.pfx
    RFC3161_SERVER="http://timestamp.comodoca.com/rfc3161"

    !isEmpty(SIGNTOOL):exists($$CERT) {
        message("Signtool and the certificate are found, will sign the $$TARGET executable")
    } else {
        warning("Signtool or the certificate is not found, will not sign the $$TARGET executable")
    }

    # sign
    !isEmpty(SIGNTOOL):exists($$CERT) {
        QMAKE_POST_LINK += $$mle($$SIGNTOOL sign /d \"Trader\'s Home Task\" /du \"$$HTTPROOT\" /f \"$$CERT\" /tr \"$$RFC3161_SERVER\" /v \"$${OUT_PWD}/$(DESTDIR_TARGET)\")
    }
}

# check for 7z
win32 {
    ZIP=$$findexeWin32("7z")
} unix {
    ZIP=$$findexeUnix("7z")
}

# INNO setup
win32 {
    INNO=$$system(echo %ProgramFiles(x86)%)\\Inno Setup 5\\iscc.exe

    !exists($$INNO) {
        INNO=$$system(echo %ProgramFiles%)\\Inno Setup 5\\iscc.exe
    }
}
