#ifndef QTPRINTDOCUMENT_TABLE_H
#define QTPRINTDOCUMENT_TABLE_H

#include "base.h"
#include "block.h"
#include "document.h"

namespace Qpd {
    class Document;
    class Block;

    class Table {
        QList<Block *> rows;
        Document *root;

    public:
        static const uint bottomMargin = 15;

        explicit Table(Document *root) : root(root) {}

        uint rowCount();

        Table *addRow(Block *row);

        void draw();
    };
}

#endif //QTPRINTDOCUMENT_TABLE_H
