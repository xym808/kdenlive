/***************************************************************************
 *   Copyright (C) 2011 by Till Theato (root@ttill.de)                     *
 *   This file is part of Kdenlive (www.kdenlive.org).                     *
 *                                                                         *
 *   Kdenlive is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Kdenlive is distributed in the hope that it will be useful,           *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with Kdenlive.  If not, see <http://www.gnu.org/licenses/>.     *
 ***************************************************************************/

#ifndef BPOINTITEM_H
#define BPOINTITEM_H

#include "effectstack/widgets/bezier/bpoint.h"

#include <QAbstractGraphicsShapeItem>

class QGraphicsView;

class BPointItem : public QAbstractGraphicsShapeItem
{
public:
    explicit BPointItem(const BPoint &point, QGraphicsItem* parent = 0);

    BPoint getPoint() const;
    void setPoint(const BPoint &point);

    enum { Type = UserType + 11 };
    virtual int type() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    /** @brief Gets The action mode for the area @param pos +- 4. */
    int getSelection(const QPointF &pos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    BPoint m_point;
    int m_selection;
    QGraphicsView *m_view;
};

#endif
