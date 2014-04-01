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

#include "about.h"
#include "tools.h"

#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    setObjectName("about");

    setWindowTitle(Tools::aboutQssEditorTitle());

    ui->setupUi(this);

    ui->label->setPixmap(QIcon(":/images/qsseditor.ico").pixmap(48, 48));
    ui->labelVersion->setText(QString("QSS Editor %1").arg(NVER_STRING));

    ui->labelCopyright->setText(QString("(C) 2014 %1 &lt;<a href=\"mailto:linuxsquirrel.dev@gmail.com\">"
                                        "linuxsquirrel.dev@gmail.com</a>&gt;").arg(tr("Dmitry Baryshev")));
}

About::~About()
{
    delete ui;
}
