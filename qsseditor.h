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

#ifndef QSSEDITOR_H
#define QSSEDITOR_H

#include <QWidget>

class QTimer;

namespace Ui
{
    class QssEditor;
}

class QssEditor : public QWidget
{
    Q_OBJECT

public:
    explicit QssEditor(QWidget *parent = 0);
    ~QssEditor();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void closeEvent(QCloseEvent *);

private:
    void open(const QString &fileName);
    bool save();
    QString settingsErrorToString(int);
    bool continueWhenUnsaved();
    void updateProjectPath(const QString &newPath);
    void showError(const QString &err);
    void restoreLastFiles();
    void saveLastFiles();
    void appendToHistoryCurrentProject();

private slots:
    void slotCssChanged();
    void slotApplyCss();
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotExportQss();
    void slotOptions();
    void slotProgress();
    void slotQuit();
    void slotDelayedOpen();
    void slotOpenFromHistoryMenu();

private:
    Ui::QssEditor *ui;
    QTimer *m_timerDelayedApply;
    bool m_changed;
    QString m_lastFileName;
};

#endif // QSSEDITOR_H
