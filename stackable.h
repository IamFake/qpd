#ifndef QTPRINTDOCUMENT_STACKABLE_H
#define QTPRINTDOCUMENT_STACKABLE_H

#include "base.h"
#include "document.h"

#include <QObject>
#include <QDebug>
#include <QDate>
#include <QMarginsF>
#include <QFileDialog>

namespace Qpd {
    class Document;

    class Stackable {
        itemSize sizeContent;
        itemSize sizeBoundaries;
        itemSize sizeChilds;

        qreal delayedWidth = 0;

    protected:
        QList<Stackable *> cells;

        uint longestRowCells() const;
        uint rowCount() const;

        bool delayedCustomWidth = false;

    public:
        Document *root;
        itemPosition pos;
        Position position;
        Align align;
        Options options;
        bool blindMode = false;
        bool customWidth = false;
        bool calcDone = false;
        QString textData;
        QRect textRect;
        Type type;
        QString mark;

        explicit Stackable(
            Document *root,
            QString const &tdata = "",
            Position tpos = Position::LEFT,
            Options toptions = Options(),
            Type ttype = Type::NONE
        );

        Stackable(
            Document *root,
            Align talign,
            Options toptions = Options()
        );

        virtual ~Stackable() = default;

        virtual void draw(bool last) = 0;

        virtual void draw() = 0;

        virtual void calcPosition(qreal width) = 0;

        virtual void calcPosition() = 0;

        bool fitH() const;

        bool fitW() const;

        qreal getContentWidth() const;

        qreal getContentHeight() const;

        qreal getBoxWidth() const;

        qreal getBoxHeight() const;

        qreal getBoundWidth() const;

        qreal getBoundHeight() const;

        qreal getWidth() const;

        qreal getHeight() const;

        qreal getChildsWidth() const;

        qreal getChildsHeight() const;

        int getMarginsVertical() const;

        int getMarginsHorizontal() const;

        uint getPaddingsVertical() const;

        uint getPaddingsHorizontal() const;

        uint getBordersVertical() const;

        uint getBordersHorizontal() const;

        void setBoxWidth(qreal width, bool silent = false);

        void setBoxHeight(qreal height, bool silent = false);

        void setBoundWidth(qreal width);

        void setBoundHeight(qreal width);

        void setContentWidth(qreal width);

        void setContentHeight(qreal height);

        void setChildsWidth(qreal width);

        void setChildsHeight(qreal height);

        void setBlindMode(bool bl);

        void setPosition(Position tpos);

        void newPage();

        void setDelayedWidth(qreal width);

        void updateDelayedWidth();

        void resetDelayedWidth();

        void forceChildRecalc();

        QList<Stackable *> *getStack() { return &cells; }
    };
}

#endif //QTPRINTDOCUMENT_STACKABLE_H
