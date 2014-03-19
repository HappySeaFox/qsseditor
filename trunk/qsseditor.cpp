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

#include <QMdiSubWindow>
#include <QApplication>
#include <QKeySequence>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QCloseEvent>
#include <QShortcut>
#include <QSettings>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QMenu>
#include <QDir>

#include "qscilexerqss.h"
#include "qsseditor.h"
#include "settings.h"
#include "ui_qsseditor.h"

QssEditor::QssEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QssEditor),
    m_changed(false)
{
    ui->setupUi(this);

    // application shortcuts
    new QShortcut(QKeySequence::Quit, this, SLOT(slotQuit()));

    // shortcuts
    ui->toolOpen->setShortcut(QKeySequence::Open);
    ui->toolSave->setShortcut(QKeySequence::Save);
    ui->toolSaveAs->setShortcut(QKeySequence::SaveAs);

    // set some sizes
    const int buttonSize = 22;

    QWidgetList buttons = QWidgetList()
                             << ui->toolOpen
                             << ui->toolSave
                             << ui->toolSaveAs
                             << ui->toolExportQss
                             << ui->toolOptions;

    foreach(QWidget *w, buttons)
    {
        w->setFixedSize(buttonSize, buttonSize);
    }

    // menu fot toolbutton
    QMenu *toolButtonMenu = new QMenu(this);
    toolButtonMenu->addAction("Item1");
    toolButtonMenu->addSeparator();
    toolButtonMenu->addAction("Item2");
    ui->toolButton->setMenu(toolButtonMenu);

    toolButtonMenu = new QMenu(this);
    ui->toolOpen->setMenu(toolButtonMenu);

    m_timerDelayedApply = new QTimer(this);
    m_timerDelayedApply->setInterval(750);
    m_timerDelayedApply->setSingleShot(true);
    connect(m_timerDelayedApply, SIGNAL(timeout()), this, SLOT(slotApplyCss()));

    QTimer *timerProgress = new QTimer(this);
    timerProgress->setInterval(500);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(slotProgress()));
    timerProgress->start();

    ui->splitter->setCollapsible(0, false);
    ui->splitter->setStretchFactor(0, 1);

    // splitter size
    QList<int> list = QList<int>() << width()/2 << width()/2;
    ui->splitter->setSizes(list);

    // some MDI windows
    QMdiSubWindow *mdi1 = ui->mdiArea->addSubWindow(new QLabel("MDI", ui->mdiArea));
    QMdiSubWindow *mdi2 = ui->mdiArea->addSubWindow(new QLineEdit("MDI", ui->mdiArea));

    mdi1->move(0, 0);
    mdi2->move(0, 60);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
    ui->tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
    ui->tree->header()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
#endif

    ui->tree->topLevelItem(0)->setExpanded(true);

    ui->text->setCaretLineVisible(true);
    ui->text->setCaretLineBackgroundColor(QColor("gainsboro"));

    ui->text->setAutoIndent(true);
    ui->text->setIndentationGuides(false);
    ui->text->setIndentationsUseTabs(true);
    ui->text->setIndentationWidth(4);

    ui->text->setMarginsBackgroundColor(QColor("gainsboro"));
    ui->text->setMarginLineNumbers(1, true);
    ui->text->setMarginWidth(1, 50);

    ui->text->setAutoCompletionSource(QsciScintilla::AcsAll);
    ui->text->setAutoCompletionReplaceWord(true);
    ui->text->setAutoCompletionCaseSensitivity(false);
    ui->text->setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
    ui->text->setAutoCompletionThreshold(0);

    ui->text->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    ui->text->setMatchedBraceBackgroundColor(Qt::yellow);
    ui->text->setUnmatchedBraceForegroundColor(Qt::blue);

    // QSS lexer
    QsciLexerQSS *lexQss = new QsciLexerQSS(this);
    ui->text->setLexer(lexQss);

    ui->text->setFocus();
    ui->text->installEventFilter(this);

    restoreLastFiles();

    if(QCoreApplication::arguments().size() > 1)
        QTimer::singleShot(0, this, SLOT(slotDelayedOpen()));
}

QssEditor::~QssEditor()
{
    delete ui;
}

bool QssEditor::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);

        if(ke)
        {
            if((ke->modifiers() == Qt::CTRL) && (ke->key() == Qt::Key_Space))
            {
                ui->text->autoCompleteFromAll();
                return true;
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

void QssEditor::closeEvent(QCloseEvent *e)
{
    if(continueWhenUnsaved())
    {
        saveLastFiles();
        e->accept();
    }
    else
        e->ignore();
}

void QssEditor::open(const QString &fileName)
{
    qDebug("Opening project");

    QSettings settings(fileName, QSettings::IniFormat);

    if(settings.status() != QSettings::NoError)
    {
        showError(tr("Cannot open file:") + ' ' + settingsErrorToString(settings.status()));
        return;
    }

    updateProjectPath(fileName);

    ui->text->setText(settings.value("css").toString());

    m_changed = false;
    ui->toolSave->setEnabled(false);

    appendToHistoryCurrentProject();
}

bool QssEditor::save()
{
    if(m_lastFileName.isEmpty())
        return false;

    QSettings settings(m_lastFileName, QSettings::IniFormat);

    settings.setFallbacksEnabled(false);
    settings.remove(QString());

    settings.setValue("css", ui->text->text());
    settings.sync();

    if(settings.status() != QSettings::NoError)
    {
        showError(tr("Cannot save file:") + ' ' + settingsErrorToString(settings.status()));
        return false;
    }

    m_changed = false;

    ui->toolSave->setEnabled(false);

    appendToHistoryCurrentProject();

    return false;
}

QString QssEditor::settingsErrorToString(int status)
{
    switch(status)
    {
        case QSettings::NoError:
        return tr("No error");

        case QSettings::AccessError:
        return tr("File access error");

        case QSettings::FormatError:
        return tr("Malformed file");

        default:
        return tr("Unknown error");
    }
}

bool QssEditor::continueWhenUnsaved()
{
    return (!m_changed || QMessageBox::question(this,
                                                tr("Warning"),
                                                tr("All unsaved changes will be lost. Continue?"),
                                                QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes);
}

void QssEditor::updateProjectPath(const QString &newPath)
{
    QFileInfo fi(newPath);

    m_lastFileName = fi.absoluteFilePath();

    setWindowTitle(m_lastFileName);

    if(!QDir::setCurrent(fi.absolutePath()))
    {
        qWarning("Cannot change directory");
        QMessageBox::warning(this, tr("Warning"), tr("Cannot change directory"));
    }
}

void QssEditor::showError(const QString &err)
{
    QMessageBox::critical(this, tr("Error"), err);
}

void QssEditor::restoreLastFiles()
{
    QStringList files = SETTINGS_GET_STRING_LIST(SETTING_LAST_FILES);

    files.removeDuplicates();

    foreach(QString file, files)
    {
        ui->toolOpen->menu()->addAction(file, this, SLOT(slotOpenFromHistoryMenu()));
    }
}

void QssEditor::saveLastFiles()
{
    const QList<QAction *> actions = ui->toolOpen->menu()->actions();
    QStringList files;

    foreach(QAction *a, actions)
    {
        files.append(a->text());
    }

    files.removeDuplicates();

    SETTINGS_SET_STRING_LIST(SETTING_LAST_FILES, files);
}

void QssEditor::appendToHistoryCurrentProject()
{
    if(m_lastFileName.isEmpty())
        return;

    QList<QAction *> actions = ui->toolOpen->menu()->actions();
    QAction *movedAction = 0;

    // already first element
    if(!actions.isEmpty() && actions.first()->text() == m_lastFileName)
        return;

    foreach(QAction *a, actions)
    {
        if(a->text() == m_lastFileName)
        {
            ui->toolOpen->menu()->removeAction(a);
            movedAction = a;
            break;
        }
    }

    ui->toolOpen->menu()->insertAction(!actions.isEmpty() ? actions.first() : 0,
                                       movedAction ? movedAction : new QAction(m_lastFileName, ui->toolOpen->menu()));
}

void QssEditor::slotCssChanged()
{
    m_changed = true;
    ui->toolSave->setEnabled(true);
    m_timerDelayedApply->start();
}

void QssEditor::slotApplyCss()
{
    ui->widgetAllWidgets->setStyleSheet(ui->text->text());
}

void QssEditor::slotOpen()
{
    if(!continueWhenUnsaved())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), QString(), tr("QSS Editor Projects (*.qep)"));

    if(fileName.isEmpty())
        return;

    open(fileName);
}

void QssEditor::slotSave()
{
    qDebug("Saving project");

    if(m_lastFileName.isEmpty())
        slotSaveAs();
    else
        save();
}

void QssEditor::slotSaveAs()
{
    qDebug("Saving project as");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save project as"), QString(), tr("QSS Editor Projects (*.qep)"));

    if(fileName.isEmpty())
        return;

    updateProjectPath(fileName);
    save();
}

void QssEditor::slotExportQss()
{
    qDebug("Export QSS");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Export QSS"), QString(), tr("QSS files (*.qss)"));

    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        showError(tr("Cannot open file: ") + ' ' + file.errorString());
        return;
    }

    QByteArray qss = ui->text->text().toAscii();

    if(file.write(qss, qss.length()) != qss.length())
    {
        showError(tr("Cannot export QSS: ") + ' ' + file.errorString());
        return;
    }
}

void QssEditor::slotOptions()
{
    qDebug("Options");
}

void QssEditor::slotProgress()
{
    int value = ui->progressBar->value();

    if(value == ui->progressBar->maximum())
        value = 0;
    else
        value++;

    ui->progressBar->setValue(value);
}

void QssEditor::slotQuit()
{
    qApp->quit();
}

void QssEditor::slotDelayedOpen()
{
    open(QCoreApplication::arguments().at(1));
}

void QssEditor::slotOpenFromHistoryMenu()
{
    QAction *a = qobject_cast<QAction *>(sender());

    if(!a)
    {
        qWarning("Cannot cast to QAction");
        return;
    }

    open(a->text());
}
