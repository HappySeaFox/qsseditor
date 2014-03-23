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

#include "project.h"

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
    enum CheckPathPolicy { AllowNonExistent, ForbidNonExistent };
    bool updateProjectPath(const QString &newPath, CheckPathPolicy policy);
    void showError(const QString &err);
    void restoreLastFiles();
    void saveLastFiles();
    void appendCurrentProjectToHistory();
    void resetWindowTitle();
    void resetPreviewDelay();

private slots:
    void slotCssChanged();
    void slotApplyCss();
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotClose();
    void slotOptions();
    void slotProgress();
    void slotQuit();
    void slotDelayedOpen();
    void slotOpenFromHistoryMenu();
    void slotFind();
    void slotFindNext();
    void slotAbout();
    void slotAboutQt();

private:
    Ui::QssEditor *ui;
    QTimer *m_timerDelayedApply;
    bool m_changed;
    QString m_lastFileName;
    Project m_project;
};

#endif // QSSEDITOR_H
