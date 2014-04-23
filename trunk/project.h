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

#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Project
{
public:
    Project();

    bool setFilePath(const QString &filePath);

    bool saveAs(const QString &filePath);

    void setQss(const QString &qss);

    QString qss() const;

    qint32 version() const;

    QString error() const;

    QString dataStreamErrorToString(int status);

private:
    QString m_qss;
    qint32 m_version;
    QString m_error;
};

inline
void Project::setQss(const QString &qss)
{
    m_qss = qss;
}

inline
QString Project::qss() const
{
    return m_qss;
}

inline
qint32 Project::version() const
{
    return m_version;
}

inline
QString Project::error() const
{
    return m_error;
}

#endif // PROJECT_H
