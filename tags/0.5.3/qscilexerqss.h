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

#ifndef QSCILEXERQSS_H
#define QSCILEXERQSS_H

#include "Qsci/qscilexercss.h"

class QsciLexerQSS : public QsciLexerCSS
{
public:
    QsciLexerQSS(QObject *parent = 0);

    virtual const char *keywords(int set) const;
    virtual QFont defaultFont(int style) const;
};

#endif // QSCILEXERQSS_H
