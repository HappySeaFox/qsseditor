/*
 * This file is part of QssEditor.
 *
 * QssEditor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QssEditor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QssEditor. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QLibraryInfo>
#include <QApplication>
#include <QTranslator>
#include <QtGlobal>
#include <QLocale>
#include <QIcon>
#include <QDir>

#include "qsseditor.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("QssEditor");
    QCoreApplication::setOrganizationName("QssEditor");
    QCoreApplication::setApplicationVersion(NVER_STRING);

#ifdef Q_OS_UNIX
    QApplication::setWindowIcon(QIcon(":/images/qsseditor.ico"));
#endif

    // load translations
    QString locale = QLocale::system().name();
    QString ts = SETTINGS_GET_STRING(SETTING_TRANSLATION);
    QString translationsDir =
#ifdef Q_OS_WIN32
            QCoreApplication::applicationDirPath() + QDir::separator() + "translations";
#elif defined Q_OS_UNIX
            "/usr/share/qsseditor/translations";
#endif

    QString qtTranslationsDir =
#ifdef Q_OS_WIN32
            translationsDir;
#elif defined Q_OS_UNIX
            QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#endif

    qDebug("Locale \"%s\", translation \"%s\"", qPrintable(locale), qPrintable(ts));

    ts = ts.isEmpty() ? locale : (ts + ".qm");

    QTranslator translator_qsseditor;
    qDebug("Loading QSS Editor translation: %s", translator_qsseditor.load("qsseditor_" + ts, translationsDir) ? "ok" : "failed");

    QTranslator translator_qt;
    qDebug("Loading Qt translation: %s", translator_qt.load("qt_" + ts, qtTranslationsDir) ? "ok" : "failed");

    app.installTranslator(&translator_qt);
    app.installTranslator(&translator_qsseditor);

    QssEditor w;
    w.show();

    return app.exec();
}
