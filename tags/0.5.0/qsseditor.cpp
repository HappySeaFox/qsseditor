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
#include "options.h"
#include "project.h"
#include "tools.h"
#include "about.h"
#include "ui_qsseditor.h"

QssEditor::QssEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QssEditor),
    m_changed(false)
{
    ui->setupUi(this);

    // some default values
    QHash<QString, QVariant> defaultValues;

    defaultValues.insert(SETTING_PREVIEW_DELAY, 750);

    Settings::instance()->addDefaultValues(defaultValues);

    resetWindowTitle();

    // icons
    ui->toolOpen->setIcon(QIcon::fromTheme("document-open", QIcon(":/images/open.png")));
    ui->toolSave->setIcon(QIcon::fromTheme("document-save", QIcon(":/images/save.png")));
    ui->toolSaveAs->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/images/saveas.png")));
    ui->toolClose->setIcon(QIcon::fromTheme("window-close", QIcon(":/images/close.png")));
    ui->toolUndo->setIcon(QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png")));
    ui->toolRedo->setIcon(QIcon::fromTheme("edit-redo", QIcon(":/images/redo.png")));
    ui->toolOptions->setIcon(QIcon::fromTheme("preferences-system", QIcon(":/images/options.png")));

    // application shortcuts
    new QShortcut(QKeySequence::Quit, this, SLOT(slotQuit()));
    new QShortcut(QKeySequence::Find, this, SLOT(slotFind()));
    new QShortcut(QKeySequence::FindNext, this, SLOT(slotFindNext()));
    new QShortcut(QKeySequence::HelpContents, this, SLOT(slotAbout()));

    // shortcuts
    ui->toolOpen->setShortcut(QKeySequence::Open);
    ui->toolSave->setShortcut(QKeySequence::Save);
    ui->toolSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->toolClose->setShortcut(QKeySequence::Close);

    // built-in Qt icon
    ui->toolAboutQt->setIcon(QIcon(":/trolltech/qmessagebox/images/qtlogo-64.png"));

    // menu for toolbutton
    QMenu *toolButtonMenu = new QMenu(this);
    toolButtonMenu->addAction("Item1");
    toolButtonMenu->addSeparator();
    toolButtonMenu->addAction("Item2");
    ui->toolButton->setMenu(toolButtonMenu);

    m_timerDelayedApply = new QTimer(this);
    m_timerDelayedApply->setSingleShot(true);
    connect(m_timerDelayedApply, SIGNAL(timeout()), this, SLOT(slotApplyCss()));
    resetPreviewDelay();

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
    qDebug("Opening style");

    if(!m_project.setFilePath(fileName))
    {
        showError(tr("Cannot open style:") + ' ' + m_project.error());
        return;
    }

    if(!updateProjectPath(fileName, ForbidNonExistent))
        return;

    ui->text->setText(m_project.qss());

    m_changed = false;
    ui->toolSave->setEnabled(false);
    ui->toolClose->setEnabled(true);

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
        showError(tr("Cannot save style:") + ' ' + m_project.error());
        return false;
    }

    m_changed = false;

    ui->toolSave->setEnabled(false);
    ui->toolClose->setEnabled(true);

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

bool QssEditor::updateProjectPath(const QString &newPath, CheckPathPolicy policy)
{
    if(newPath.isEmpty())
        return false;

    QFileInfo fi(newPath);

    if(policy == ForbidNonExistent && (!fi.exists() || !fi.isReadable()))
    {
        showError(tr("Cannot open style. The file doesn't exist or not readable"));
        return false;
    }

    if(!QDir::setCurrent(fi.absolutePath()))
    {
        showError(tr("Cannot change directory"));
        return false;
    }

    m_lastFileName = QDir::toNativeSeparators(fi.absoluteFilePath());

    setWindowTitle(m_lastFileName);

    return true;
}

void QssEditor::showError(const QString &err)
{
    qWarning("%s", qPrintable(err));
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

        if(!ui->toolOpen->menu())
            ui->toolOpen->setMenu(new QMenu(ui->toolOpen));

        ui->toolOpen->menu()->addAction(QDir::toNativeSeparators(file), this, SLOT(slotOpenFromHistoryMenu()));
    }
}

void QssEditor::saveLastFiles()
{
    QStringList files;

    if(ui->toolOpen->menu())
    {
        const QList<QAction *> actions = ui->toolOpen->menu()->actions();

        foreach(QAction *a, actions)
        {
            files.append(a->text());
        }

        files.removeDuplicates();

        // maximum history size
        while(files.size() > 15)
            files.removeLast();
    }

    SETTINGS_SET_STRING_LIST(SETTING_LAST_FILES, files);
    SETTINGS_SET_STRING(SETTING_LAST_FILE, m_lastFileName);
}

void QssEditor::appendCurrentProjectToHistory()
{
    if(m_lastFileName.isEmpty())
        return;

    if(!ui->toolOpen->menu())
        ui->toolOpen->setMenu(new QMenu(ui->toolOpen));

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

void QssEditor::resetWindowTitle()
{
    setWindowTitle(tr("QSS Editor") + " v" + NVER_STRING);
}

void QssEditor::resetPreviewDelay()
{
    int delay = SETTINGS_GET_INT(SETTING_PREVIEW_DELAY);

    if(delay < 100 || delay > 5000)
        delay = 750;

    m_timerDelayedApply->setInterval(delay);
}

void QssEditor::slotCssChanged()
{
    m_changed = true;
    ui->toolSave->setEnabled(true);
    ui->toolClose->setEnabled(true);
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

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open style"), QString(), tr("Qt Style Sheets (*.qss)"));

    if(fileName.isEmpty())
        return;

    open(fileName);
}

void QssEditor::slotSave()
{
    qDebug("Saving style");

    if(m_lastFileName.isEmpty())
        slotSaveAs();
    else
        save();
}

void QssEditor::slotSaveAs()
{
    qDebug("Saving style as");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save style as"), QString(), tr("Qt Style Sheets (*.qss)"));

    if(fileName.isEmpty())
        return;

    if(!updateProjectPath(fileName, AllowNonExistent))
        return;

    save();
}

void QssEditor::slotClose()
{
    qDebug("Closing");

    if(!continueWhenUnsaved())
        return;

    m_lastFileName.clear();
    ui->text->clear();
    m_changed = false;
    m_project.setFilePath(QString());

    ui->toolSave->setEnabled(false);
    ui->toolClose->setEnabled(false);

    resetWindowTitle();
}

void QssEditor::slotOptions()
{
    qDebug("Options");

    Options opt(this);

    if(opt.exec() == QDialog::Accepted)
    {
        opt.saveSettings();
        resetPreviewDelay();
    }
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
    if(QCoreApplication::arguments().size() > 1)
        open(QCoreApplication::arguments().at(1));
    else if(SETTINGS_GET_BOOL(SETTING_OPEN_LAST_FILE))
    {
        QString file = SETTINGS_GET_STRING(SETTING_LAST_FILE);

        if(!file.isEmpty())
            open(file);
    }
}

void QssEditor::slotOpenFromHistoryMenu()
{
    QAction *a = qobject_cast<QAction *>(sender());

    if(!a)
    {
        qWarning("Cannot cast to QAction");
        return;
    }

    if(!continueWhenUnsaved())
        return;

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

void QssEditor::slotAbout()
{
    About a(this);
    a.exec();
}

void QssEditor::slotAboutQt()
{
    QMessageBox::aboutQt(this);
}
