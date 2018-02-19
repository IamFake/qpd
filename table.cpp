#include "table.h"

using namespace Qpd;

uint Table::rowCount() {
    return uint(rows.count());
}

Table *Table::addRow(Block *row) {
    row->updateDelayedWidth();
    rows.append(row);
    return this;
}

void Table::draw() {
    if (rows.isEmpty()) return;
    qDebug() << "---- ----- ------ Start Drawing Table";

    uint tableBorder = 1;
    uint tablePadding = 5;

    Block *first = rows.first();
    first->options.setBorder(tableBorder);
    first->options.setPadding(tablePadding);

    auto fcells = first->getStack();
    for (auto cl : *fcells) {
        if (cl->options.header && cl->type == Type::BLOCK) {
            cl->options.setBorder(tableBorder);
            cl->options.setPadding(tablePadding);
        }
    }

    first->draw();
    qDebug() << "---- ----- ------ End Drawing Table header; 2: " << first->getCell(1)->getWidth();

    for (Block *c : rows) {
        if (c == first) continue;

        c->options.setBorder(tableBorder);
        c->options.setPadding(tablePadding);

        int cells = c->getCellsCount();
        for (uint i = 0; i < cells; i++) {
            qreal ccellWidth = first->getCell(i)->getContentWidth();
            qreal zcellWidth = c->getCell(i)->getContentWidth();

            if (ccellWidth != zcellWidth) {
                if (c->getCell(i)->type == Type::TEXT) {
                    c->getCell(i)->setBoxWidth(ccellWidth);
                } else {
                    c->getCell(i)->setContentWidth(ccellWidth);
                }
            }

            qDebug() << "-- Table shifting from "
                     << c->getCell(i)->getWidth()
                     << " to " << first->getCell(i)->getWidth()
                     << " result: " << c->getCell(i)->getWidth()
                     << " header? " << c->getCell(i)->options.header
                     << " type: " << (c->getCell(i)->type == Type::BLOCK ? "BLOCK" : "TEXT")
                     << " boxW: " << c->getCell(i)->getBoxWidth()
                     << " bndW: " << c->getCell(i)->getBoundWidth();
            qDebug() << "-- Table shifting ORIGINAL "
                     << " width: " << first->getCell(i)->getWidth()
                     << " header? " << first->getCell(i)->options.header
                     << " type: " << (first->getCell(i)->type == Type::BLOCK ? "BLOCK" : "TEXT")
                     << " boxW: " << first->getCell(i)->getBoxWidth()
                     << " bndW: " << first->getCell(i)->getBoundWidth()
                     << " cntW: " << first->getCell(i)->getContentWidth()
                ;

            if (c->getCell(i)->options.header && c->getCell(i)->type == Type::BLOCK) {
                c->getCell(i)->options.setBorder(tableBorder);
                c->getCell(i)->options.setPadding(tablePadding);
            }
        }

        c->calcPosition();
        c->draw();
    }

    first->root->position.y += bottomMargin;
}
