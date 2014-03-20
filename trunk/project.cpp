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

#include <QDataStream>
#include <QByteArray>
#include <QRegExp>
#include <QDebug>
#include <QFile>

#include "project.h"

Project::Project(const QString &filePath)
{
    setFilePath(filePath);
}

bool Project::setFilePath(const QString &filePath)
{
    static const QRegExp rx("/\\*\\s+QssEditor:\\s+([a-zA-Z0-9+\\/=]+)\\s+\\*/\\s+");

    m_valid = false;
    m_version = -1;
    m_error.clear();

    if(filePath.isEmpty())
        return false;

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
    {
        m_error = file.errorString();
        return false;
    }

    m_qss = file.readAll();
    file.close();

    if(rx.indexIn(m_qss) == 0)
    {
        QByteArray ba = QByteArray::fromBase64(rx.cap(1).toAscii());
        QDataStream ds(&ba, QIODevice::ReadOnly);

        ds.setVersion(QDataStream::Qt_4_8);

        ds >> m_version;

        if(ds.status() != QDataStream::Ok)
        {
            m_error = dataStreamErrorToString(ds.status());
            return false;
        }

        m_qss = m_qss.mid(rx.matchedLength());

        qDebug("Loaded project version %d", m_version);
    }
    else
        qDebug("QssEditor project header is not found");

    return true;
}

bool Project::saveAs(const QString &filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        m_error = file.errorString();
        return false;
    }

    QByteArray ba;
    QDataStream ds(&ba, QIODevice::ReadWrite);

    ds.setVersion(QDataStream::Qt_4_8);

    qDebug("Saving project with version %d", m_version);

    ds << m_version;

    if(ds.status() != QDataStream::Ok)
    {
        m_error = dataStreamErrorToString(ds.status());
        return false;
    }

    ba = "/* QssEditor: " + ba.toBase64() + " */\n" + m_qss.toAscii();

    if(file.write(ba) != ba.length())
    {
        m_error = file.errorString();
        return false;
    }

    return true;
}

QString Project::dataStreamErrorToString(int status)
{
    switch(status)
    {
        case QDataStream::ReadPastEnd:
            return QObject::tr("The data stream has read past the end of the data");

        case QDataStream::ReadCorruptData:
            return QObject::tr("The data stream has read corrupt data");

        case QDataStream::WriteFailed:
            return QObject::tr("The data stream cannot write to the underlying device");

        default:
            return QObject::tr("Unknown error");

    }
}
