#include "stackable.h"

using namespace Qpd;

Stackable::Stackable(
    Document *root,
    QString const &tdata,
    Position tpos,
    Options toptions,
    Type ttype
) :
    root(root),
    position(tpos),
    align(Align::NONE),
    options(toptions),
    textData(tdata),
    type(ttype) {
    if (textData.isEmpty()) {
        textData = " ";
    }

    pos.x = 0;
    pos.y = root->position.y;

    root->stack.append(this);
}

Stackable::Stackable(
    Document *root,
    Align talign,
    Options toptions
) :
    root(root),
    position(Position::LEFT),
    align(talign),
    options(toptions),
    type(Type::NONE) {
    if (textData.isEmpty()) {
        textData = " ";
    }

    pos.x = 0;
    pos.y = root->position.y;

    root->stack.append(this);
}

bool Stackable::fitH() const { return pos.y + getBoxHeight() <= root->size.h; }

bool Stackable::fitW() const { return pos.x + getBoxWidth() <= root->size.w; }

qreal Stackable::getContentWidth() const { return sizeContent.w; }

qreal Stackable::getContentHeight() const { return sizeContent.h; }

qreal Stackable::getBoxWidth() const { return getContentWidth() + getPaddingsHorizontal() + getBordersHorizontal(); }

qreal Stackable::getBoxHeight() const { return getContentHeight() + getPaddingsVertical() + getBordersVertical(); }

qreal Stackable::getBoundWidth() const { return sizeBoundaries.w; }

qreal Stackable::getBoundHeight() const { return sizeBoundaries.h; }

qreal Stackable::getWidth() const {
    return getBoxWidth() + getMarginsHorizontal();
}

qreal Stackable::getHeight() const {
    return getBoxHeight() + getMarginsVertical();
}

qreal Stackable::getChildsWidth() const {
    return sizeChilds.w;
}

qreal Stackable::getChildsHeight() const {
    return sizeChilds.h;
}

int Stackable::getMarginsVertical() const {
    return options.margins.top + options.margins.bottom;
}

int Stackable::getMarginsHorizontal() const {
    return options.margins.left + options.margins.right;
}

uint Stackable::getPaddingsVertical() const {
    if (type == Type::BLOCK) {
        uint rows = rowCount();
        uint total = (options.padding.top + options.padding.bottom) * rows;

        return total;
    } else {
        return options.padding.top + options.padding.bottom;
    }
}

uint Stackable::getPaddingsHorizontal() const {
    if (type == Type::BLOCK) {
        uint longestRow = longestRowCells();
        uint total = (options.padding.left + options.padding.right) * longestRow;

        return total;
    } else {
        return options.padding.left + options.padding.right;
    }
}

uint Stackable::getBordersVertical() const {
    if (type == Type::BLOCK) {
        uint rows = rowCount();
        uint total = options.border.top + options.border.bottom;
        uint borderMax = qMax(options.border.top, options.border.bottom);

        total += borderMax * (rows - 1);

        return total;
    } else {
        return options.border.top + options.border.bottom;
    }
}

uint Stackable::getBordersHorizontal() const {
    if (type == Type::BLOCK) {
        uint longestRow = longestRowCells();
        uint total = 0;
        uint borderMax = qMax(options.border.left, options.border.right);

        total = (borderMax * (longestRow - 1)) + options.border.left + options.border.right;

        return total;
    } else {
        return options.border.left + options.border.right;
    }
}

void Stackable::setBoxWidth(qreal width, bool silent) {
    auto prevW = getBoxWidth();

    qreal newWidth = width > 0 ? qMin(root->size.w, width) : root->size.w;
    newWidth -= getMarginsHorizontal();
    newWidth -= getPaddingsHorizontal();
    newWidth -= getBordersHorizontal();

    setContentWidth(newWidth);
    setBoundWidth(newWidth);

    if (width > 0 && !silent) {
        qDebug() << "Stackable: setBoxWidth for "
                 << (type == Type::BLOCK ? "BLOCK" : (type == Type::TEXT ? "TEXT" : "UNK")) <<
                 " to requested " << width << " and prev " << prevW << " with result: bw: " << getBoxWidth() << " cw: "
                 << getContentWidth() << " bndw:" << getBoundWidth() << " :: " << mark;
        customWidth = true;
    }
}

void Stackable::setBoxHeight(qreal height, bool silent) {
    qreal newHeight = height > 0 ? qMin(root->size.h, height) : root->size.h;
    newHeight -= getMarginsVertical();
    newHeight -= getPaddingsVertical();
    newHeight -= getBordersVertical();

    setContentHeight(newHeight);
    setBoundHeight(newHeight);

    qDebug() << "Stackable: setBoxHeight for "
             << (type == Type::BLOCK ? "BLOCK" : (type == Type::TEXT ? "TEXT" : "UNK"))
             << " to requested " << height << " with result: bh: " << getBoxHeight() << " ch: "
             << getContentHeight() << " :: " << mark;
    if (height > 0 && !silent) {
        customWidth = true;
    }
}

void Stackable::setBoundWidth(qreal width) { sizeBoundaries.w = width; }

void Stackable::setBoundHeight(qreal height) { sizeBoundaries.h = height; }

void Stackable::setContentWidth(qreal width) {
    if (width > 0) {
        qDebug() << "Stackable: setContentWidth for "
                 << (type == Type::BLOCK ? "BLOCK" : (type == Type::TEXT ? "TEXT" : "UNK"))
                 << " to requested " << width << " :: " << mark;
    }
    sizeContent.w = width;
}

void Stackable::setContentHeight(qreal height) {
    if (height > 0) {
        qDebug() << "Stackable: setContentHeight for "
                 << (type == Type::BLOCK ? "BLOCK" : (type == Type::TEXT ? "TEXT" : "UNK"))
                 << " to requested " << height << " :: " << mark;
    }
    sizeContent.h = height;
}

void Stackable::setChildsWidth(qreal width) {
    sizeChilds.w = width;
}

void Stackable::setChildsHeight(qreal height) {
    sizeChilds.h = height;
}

/**
 * When we "blind" we do not change root's position after rendering.
 **/
void Stackable::setBlindMode(bool bl) { blindMode = bl; }

void Stackable::setPosition(Position tpos) { position = tpos; }

void Stackable::newPage() {
    root->newPage();
    pos.x = pos.y = 0;
}

void Stackable::setDelayedWidth(qreal width) {
    qDebug() << "=% Set delayed width to " << width;
    delayedWidth = width;
    delayedCustomWidth = true;
}

void Stackable::updateDelayedWidth() {
    if (delayedCustomWidth) {
        qDebug() << "=%% Activate Delayed witdh " << delayedWidth;
        delayedCustomWidth = false;
        setBoxWidth(delayedWidth);
    }
}

void Stackable::resetDelayedWidth() {
    if (delayedCustomWidth) {
        delayedCustomWidth = false;
    }
}

void Stackable::forceChildRecalc() {
    for (auto ch : cells) {
        ch->customWidth = false;
        ch->forceChildRecalc();
    }
}

uint Stackable::longestRowCells() const {
    uint current = 0;
    uint max = 0;

    if (cells.size() > 1) {
        for (Stackable *st : cells) {
            current++;

            if (st->options.row) {
                current = 0;
                continue;
            }

            if (current > max) {
                max = current;
            }
        }
    }

    if (max == 0) max = 1;

    return max;
}

uint Stackable::rowCount() const {
    uint current = 1;

    if (cells.size() > 1) {
        for (Stackable *st : cells) {
            if (st->options.row) {
                current++;
            }
        }
    }

    return current;
}
