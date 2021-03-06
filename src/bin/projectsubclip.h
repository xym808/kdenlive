/*
Copyright (C) 2015 Jean-Baptiste Mardelle <jb@kdenlive.org>
This file is part of Kdenlive. See www.kdenlive.org.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PROJECTSUBCLIP_H
#define PROJECTSUBCLIP_H

#include "abstractprojectitem.h"
#include "definitions.h"

#include <QUrl>
#include <QMutex>

class ProjectFolder;
class ProjectClip;
class QDomElement;

namespace Mlt {
  class Producer;
  class Properties;
};


/**
 * @class ProjectSubClip
 * @brief Represents a clip in the project (not timeline).
 * 

 */

class ProjectSubClip : public AbstractProjectItem
{
    Q_OBJECT

public:
    /**
     * @brief Constructor; used when loading a project and the producer is already available.
     */
    ProjectSubClip(ProjectClip *parent, int in, int out, const QString &timecode, const QString &name = QString());
    virtual ~ProjectSubClip();

    ProjectClip *clip(const QString &id);
    ProjectFolder* folder(const QString &id);
    ProjectSubClip* subClip(int in, int out);
    ProjectClip *clipAt(int ix);
    /** @brief Recursively disable/enable bin effects. */
    void disableEffects(bool disable);
    QDomElement toXml(QDomDocument &document, bool includeMeta = false);

    /** @brief Returns the clip's duration. */
    GenTime duration() const;

    /** @brief Calls AbstractProjectItem::setCurrent and sets the bin monitor to use the clip's producer. */
    virtual void setCurrent(bool current, bool notify = true);

    /** @brief Sets thumbnail for this clip. */
    void setThumbnail(QImage);

    /** @brief Remove reference to this subclip in the master clip, to be done before a subclip is deleted. */
    void discard();
    QPoint zone() const;
    virtual QString getToolTip() const;
    virtual bool rename(const QString &name, int column);

private:
    ProjectClip *m_masterClip;
    int m_in;
    int m_out;

private slots:
    void gotThumb(int pos, QImage img);
};

#endif
