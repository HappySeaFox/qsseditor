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

#include "Qsci/qsciscintilla.h"

#include "searchandreplace.h"
#include "settings.h"
#include "ui_searchandreplace.h"

SearchAndReplace::SearchAndReplace(QsciScintilla *editor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchAndReplace),
    m_editor(editor),
    m_firstFind(true)
{
    ui->setupUi(this);

    QString selectedText = m_editor->selectedText();

    ui->lineFind->setText(selectedText.isEmpty() ? SETTINGS_GET_STRING(SETTING_FIND_REPLACE_FIND_TEXT) : selectedText);
    ui->checkReplace->setChecked(SETTINGS_GET_BOOL(SETTING_FIND_REPLACE_REPLACE, false));
    ui->lineReplace->setText(SETTINGS_GET_STRING(SETTING_FIND_REPLACE_REPLAC_TEXT));

    if(SETTINGS_GET_BOOL(SETTING_FIND_REPLACE_FORWARD, true))
        ui->radioDown->setChecked(true);
    else
        ui->radioUp->setChecked(true);

    ui->checkCs->setChecked(SETTINGS_GET_BOOL(SETTING_FIND_REPLACE_CASE_SENSITIVE, false));
    ui->checkWhole->setChecked(SETTINGS_GET_BOOL(SETTING_FIND_REPLACE_WHOLE_WORDS, false));
    ui->checkRegexp->setChecked(SETTINGS_GET_BOOL(SETTING_FIND_REPLACE_REGEXP, false));

    ui->lineFind->selectAll();

    connect(this, SIGNAL(accepted()), this, SLOT(slotAccepted()));
}

SearchAndReplace::~SearchAndReplace()
{
    delete ui;
}

bool SearchAndReplace::find()
{
    return m_editor->findFirst(ui->lineFind->text(),
                               ui->checkRegexp->isChecked(),
                               ui->checkCs->isChecked(),
                               ui->checkWhole->isChecked(),
                               true);
}

bool SearchAndReplace::replaceAndNext()
{
    if(m_firstFind)
    {
        m_firstFind = false;

        if(!find())
            return false;
    }

    m_editor->replace(ui->lineReplace->text());
    return m_editor->findNext();
}

void SearchAndReplace::slotReplaceAll()
{
    if(m_firstFind)
    {
        m_firstFind = false;

        if(!find())
            return;
    }

    while(replaceAndNext())
    {}
}

void SearchAndReplace::slotAccepted()
{
    SETTINGS_SET_STRING(SETTING_FIND_REPLACE_FIND_TEXT, ui->lineFind->text(), Settings::NoSync);
    SETTINGS_SET_BOOL(SETTING_FIND_REPLACE_REPLACE, ui->checkReplace->isChecked(), Settings::NoSync);
    SETTINGS_SET_STRING(SETTING_FIND_REPLACE_REPLAC_TEXT, ui->lineReplace->text(), Settings::NoSync);
    SETTINGS_SET_BOOL(SETTING_FIND_REPLACE_FORWARD, ui->radioDown->isChecked(), Settings::NoSync);

    SETTINGS_SET_BOOL(SETTING_FIND_REPLACE_CASE_SENSITIVE, ui->checkCs->isChecked(), Settings::NoSync);
    SETTINGS_SET_BOOL(SETTING_FIND_REPLACE_WHOLE_WORDS, ui->checkWhole->isChecked(), Settings::NoSync);
    SETTINGS_SET_BOOL(SETTING_FIND_REPLACE_REGEXP, ui->checkRegexp->isChecked());
}

void SearchAndReplace::slotSearchChanged()
{
    m_firstFind = true;
}
