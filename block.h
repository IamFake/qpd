#ifndef QTPRINTDOCUMENT_BLOCK_H
#define QTPRINTDOCUMENT_BLOCK_H

#include "base.h"
#include "stackable.h"
#include "text.h"
#include "document.h"

namespace Qpd {
    class Document;

    class Stackable;

    class Text;

    class Block : public Stackable {
    public:
        explicit Block(Document *root, Align talign = Align::NONE, Options topts = Options(),
                       QString const &objmark = "");

        Block(Document *root, Options topts, QString const &objMark = "") : Block(root, Align::LEFT, topts, objMark) {}

        Block(Document *root, Align talign, QDate date, Options topts = Options());

        Block(Document *root, Align talign, Options topts, Text *text);

        Block *addCell(Stackable *stack, uint width = 0);

        Block *addCell(Stackable *stack, Position tpos);

        Block *addCell(Stackable *stack, Align talign);

        Block *addCell(Stackable *stack, Position tpos, Align talign, uint width);

        Block *prependCell(Stackable *stack, uint width = 0);

        Block *prependCell(Stackable *stack, Position tpos);

        Block *prependCell(Stackable *stack, Align talign);

        Block *prependCell(Stackable *stack, Position tpos, Align talign, uint width);

        Block *addStubCell(uint width = 0);

        int getCellsCount();

        Stackable *getCell(uint idx);

        void replaceCell(uint idx, Stackable *item, bool recalc = false);

        void draw(bool last) override;

        void draw() override;

        void calcPosition(qreal width) override;

        void calcPosition() override;
    };
}

#endif //QTPRINTDOCUMENT_BLOCK_H
