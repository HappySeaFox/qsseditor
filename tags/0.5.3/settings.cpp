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

#include <QCoreApplication>

#include "settings.h"

/*******************************************************/

class SettingsPrivate
{
public:
    QSettings *settings;
    QMap<QString, QString> translations;
    QHash<QString, QVariant> defaultValues;
};

/*******************************************************/

Settings::Settings()
{
    d = new SettingsPrivate;

    d->settings = new QSettings(QSettings::IniFormat,
                                QSettings::UserScope,
                                QCoreApplication::organizationName(),
                                QCoreApplication::applicationName());

    d->settings->setFallbacksEnabled(false);

    // save version for future changes
    d->settings->setValue("version", NVER_STRING);
}

Settings::~Settings()
{
    delete d->settings;
    delete d;
}

void Settings::addDefaultValues(const QHash<QString, QVariant> &defaultValues)
{
    QHash<QString, QVariant>::const_iterator itEnd = defaultValues.end();

    for(QHash<QString, QVariant>::const_iterator it = defaultValues.begin();it != itEnd;++it)
    {
        d->defaultValues.insert(it.key(), it.value());
    }
}

QVariant Settings::defaultValue(const QString &key) const
{
    return d->defaultValues.value(key);
}

void Settings::sync()
{
    d->settings->sync();
}

Settings* Settings::instance()
{
    static Settings *inst = new Settings;

    return inst;
}

void Settings::fillTranslations()
{
    d->translations.insert("en", "English");

    // http://www.loc.gov/standards/iso639-2/php/code_list.php
    d->translations.insert("ru",    QString::fromUtf8("Русский"));
    d->translations.insert("zh_CN", QString::fromUtf8("简体中文"));
}

QHash<QString, QVariant>& Settings::defaultValues()
{
    return d->defaultValues;
}

QSettings *Settings::settings()
{
    return d->settings;
}

bool Settings::contains(const QString &key) const
{
    return d->settings->contains(key.startsWith('/') ? ("settings" + key) : key);
}

void Settings::remove(const QString &key, Settings::SyncType sync)
{
    QSettings *s = settings();

    s->beginGroup("settings");
    s->remove(key);
    s->endGroup();

    if(sync == Sync)
        s->sync();
}

QMap<QString, QString> Settings::translations()
{
    if(d->translations.isEmpty())
        fillTranslations();

    return d->translations;
}
