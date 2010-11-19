/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef GLSLENGINE_H
#define GLSLENGINE_H

#include "glsl.h"
#include "glslmemorypool.h"
#include <QtCore/qstring.h>
#include <QtCore/qset.h>

namespace GLSL {

class GLSL_EXPORT DiagnosticMessage
{
public:
    enum Kind {
        Warning,
        Error
    };

    DiagnosticMessage();

    Kind kind() const;
    void setKind(Kind kind);

    bool isError() const;
    bool isWarning() const;

    QString fileName() const;
    void setFileName(const QString &fileName);

    int line() const;
    void setLine(int line);

    QString message() const;
    void setMessage(const QString &message);

private:
    QString _fileName;
    QString _message;
    Kind _kind;
    int _line;
};


class GLSL_EXPORT Engine
{
public:
    Engine();
    ~Engine();

    const QString *identifier(const QString &s);
    const QString *identifier(const char *s, int n);
    QSet<QString> identifiers() const;

    MemoryPool *pool();

    QList<DiagnosticMessage> diagnosticMessages() const;
    void clearDiagnosticMessages();
    void addDiagnosticMessage(const DiagnosticMessage &m);

private:
    QSet<QString> _identifiers;
    MemoryPool _pool;
    QList<DiagnosticMessage> _diagnosticMessages;
};

} // namespace GLSL

#endif // GLSLENGINE_H
