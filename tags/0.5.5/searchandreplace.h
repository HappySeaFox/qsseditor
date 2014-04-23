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

#ifndef SEARCHANDREPLACE_H
#define SEARCHANDREPLACE_H

#include <QDialog>

class QsciScintilla;

namespace Ui
{
    class SearchAndReplace;
}

class SearchAndReplace : public QDialog
{
    Q_OBJECT

public:
    explicit SearchAndReplace(QsciScintilla *editor, QWidget *parent = 0);
    ~SearchAndReplace();

private slots:
    bool find();
    bool replaceAndNext();
    void slotReplaceAll();
    void slotAccepted();
    void slotSearchChanged();

private:
    Ui::SearchAndReplace *ui;
    QsciScintilla *m_editor;
    bool m_firstFind;
};

#endif // SEARCHANDREPLACE_H
