/***************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
**
** Non-Open Source Usage
**
** Licensees may use this file in accordance with the Qt Beta Version
** License Agreement, Agreement version 2.2 provided with the Software or,
** alternatively, in accordance with the terms contained in a written
** agreement between you and Nokia.
**
** GNU General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the packaging
** of this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
**
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt GPL Exception
** version 1.2, included in the file GPL_EXCEPTION.txt in this package.
**
***************************************************************************/
/*
  Copyright 2005 Roberto Raggi <roberto@kdevelop.org>

  Permission to use, copy, modify, distribute, and sell this software and its
  documentation for any purpose is hereby granted without fee, provided that
  the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
  KDEVELOP TEAM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
  AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PP_MACRO_H
#define PP_MACRO_H

#include <CPlusPlusForwardDeclarations.h>

#include <QByteArray>
#include <QVector>
#include <QString>

namespace CPlusPlus {

class CPLUSPLUS_EXPORT Macro
{
public:
    QByteArray name;
    QByteArray definition;
    QVector<QByteArray> formals;
    QByteArray fileName;
    int line;
    Macro *next;
    unsigned hashcode;

    union
    {
        unsigned state;

        struct
        {
            unsigned hidden: 1;
            unsigned function_like: 1;
            unsigned variadics: 1;
        };
    };

    inline Macro():
            line(0),
            next(0),
            hashcode(0),
            state(0)
    { }

    QString toString() const
    {
        QString text;
        if (hidden)
            text += QLatin1String("#undef ");
        else
            text += QLatin1String("#define ");
        text += QString::fromUtf8(name.constData(), name.size());
        if (function_like) {
            text += QLatin1Char('(');
            bool first = true;
            foreach (const QByteArray formal, formals) {
                if (! first)
                    text += QLatin1String(", ");
                else
                    first = false;
                text += QString::fromUtf8(formal.constData(), formal.size());
            }
            if (variadics)
                text += QLatin1String("...");
            text += QLatin1Char(' ');
        }
        text += QLatin1Char(' ');
        text += QString::fromUtf8(definition.constData(), definition.size());
        return text;
    }
};

} // namespace CPlusPlus

#endif // PP_MACRO_H
