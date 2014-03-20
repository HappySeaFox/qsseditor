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

#include "searchandreplace.h"
#include "qscilexerqss.h"
#include "qsseditor.h"
#include "settings.h"
#include "project.h"
#include "ui_qsseditor.h"

QssEditor::QssEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QssEditor),
    m_changed(false)
{
    ui->setupUi(this);

    setWindowTitle(tr("QSS Editor") + ' ' + NVER_STRING);

    // application shortcuts
    new QShortcut(QKeySequence::Quit, this, SLOT(slotQuit()));
    new QShortcut(QKeySequence::Find, this, SLOT(slotFind()));
    new QShortcut(QKeySequence::FindNext, this, SLOT(slotFindNext()));

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
    QMdiSubWindow *mdi = ui->mdiArea->addSubWindow(new QLabel("MDI", ui->mdiArea));
    mdi->resize(160, 80);

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

    if(!updateProjectPath(fileName))
        return;

    m_project.setFilePath(m_lastFileName);

    if(!m_project.error().isEmpty())
    {
        showError(m_project.error());
        return;
    }

    ui->text->setText(m_project.qss());

    m_changed = false;
    ui->toolSave->setEnabled(false);

    appendCurrentProjectToHistory();

    // apply QSS right now
    m_timerDelayedApply->start(0);
}

bool QssEditor::save()
{
    if(m_lastFileName.isEmpty())
        return false;

    m_project.setQss(ui->text->text());

    if(!m_project.saveAs(m_lastFileName))
    {
        showError(m_project.error());
        return false;
    }

    m_changed = false;

    ui->toolSave->setEnabled(false);

    appendCurrentProjectToHistory();

    return true;
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
                                                tr("This will discard all the unsaved changes"),
                                                QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Ok);
}

bool QssEditor::updateProjectPath(const QString &newPath)
{
    if(newPath.isEmpty())
        return false;

    QFileInfo fi(newPath);

    m_lastFileName = QDir::toNativeSeparators(fi.absoluteFilePath());

    setWindowTitle(m_lastFileName);

    if(!QDir::setCurrent(fi.absolutePath()))
    {
        qWarning("Cannot change directory");
        QMessageBox::warning(this, tr("Warning"), tr("Cannot change directory"));
        return false;
    }

    return true;
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
        if(!QFile::exists(file))
            continue;

        ui->toolOpen->menu()->addAction(QDir::toNativeSeparators(file), this, SLOT(slotOpenFromHistoryMenu()));
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

void QssEditor::appendCurrentProjectToHistory()
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
    ui->toolButton->menu()->setStyleSheet(ui->widgetAllWidgets->styleSheet());
}

void QssEditor::slotOpen()
{
    if(!continueWhenUnsaved())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), QString(), tr("Qt Style Sheets (*.qss)"));

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

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save project as"), QString(), tr("Qt Style Sheets (*.qss)"));

    if(fileName.isEmpty())
        return;

    if(!updateProjectPath(fileName))
        return;

    save();
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

void QssEditor::slotFind()
{
    SearchAndReplace sar(ui->text, this);
    sar.exec();
}

void QssEditor::slotFindNext()
{
    ui->text->findNext();
}
