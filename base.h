#ifndef QTPRINTDOCUMENT_BASE_H
#define QTPRINTDOCUMENT_BASE_H

#ifndef QT_NO_DEBUG_OUTPUT
#define QT_NO_DEBUG_OUTPUT true
#endif

#include <QtGlobal>
#include <QtCore/QString>
#include <QtGui/QColor>

namespace Qpd {
    struct itemSize {
        itemSize() : h(0), w(0) {}

        explicit itemSize(qreal h, qreal w = 0) : h(h), w(w) {}

        qreal h;
        qreal w;
    };

    struct itemPosition {
        itemPosition() : x(0), y(0) {}

        explicit itemPosition(qreal x, qreal y = 0) : x(x), y(y) {}

        qreal x;
        qreal y;
    };

    enum class Position {
        INLINE = 1,
        LEFT,
        CENTER,
        RIGHT,

        EMPTY
    };
    enum class Align {
        NONE = 1,
        LEFT,
        CENTER,
        RIGHT,

        EMPTY
    };

    enum class Type {
        NONE = 1,
        TEXT,
        BLOCK,
        TABLE
    };

    enum class Orientation {
        Portrait,
        Landscape
    };

    struct Options {
        qreal width = 0;
        qreal height = 0;
        bool underline = false;
        bool inlined = false;
        bool boundline = false;

        struct Margins {
            Margins() :
                top(0),
                left(0),
                right(0),
                bottom(0) {}

            explicit Margins(int t, int l = 0, int r = 0, int b = 0) :
                top(t),
                left(l),
                right(r),
                bottom(b) {}

            int top;
            int left;
            int right;
            int bottom;
        } margins{0, 0, 0, 0};

        struct Borders {
            Borders() :
                top(0),
                left(0),
                right(0),
                bottom(0) {}

            explicit Borders(uint t, uint l = 0, uint r = 0, uint b = 0) :
                top(t),
                left(l),
                right(r),
                bottom(b) {}

            uint top;
            uint left;
            uint right;
            uint bottom;
            QColor color{0, 0, 0, 254};
        } border{0, 0, 0, 0};

        struct Paddings {
            Paddings() :
                top(0),
                left(0),
                right(0),
                bottom(0) {}

            explicit Paddings(uint t, uint l = 0, uint r = 0, uint b = 0) :
                top(t),
                left(l),
                right(r),
                bottom(b) {}

            uint top;
            uint left;
            uint right;
            uint bottom;
        } padding{0, 0, 0, 0};

        bool row = false;
        bool header = false;
        bool fluid = false;

        Options &setInlined() {
            inlined = true;
            return *this;
        }

        Options &setWidth(qreal newWidth) {
            width = newWidth;
            return *this;
        }

        Options &setHeight(qreal newHeight) {
            height = newHeight;
            return *this;
        }

        Options &setBorder(uint newBorder) {
            border.top = border.left = border.right = border.bottom = newBorder;
            return *this;
        }

        Options &setBorderColor(QColor &&color) {
            border.color = color;
            return *this;
        }

        Options &setBorderColor(QColor &color) {
            border.color = color;
            return *this;
        }

        Options &setMargin(int value) {
            margins.top = margins.left = margins.right = margins.bottom = value;
            return *this;
        }

        Options &setMarginLeft(int value) {
            margins.left = value;
            return *this;
        }

        Options &setMarginRight(int value) {
            margins.right = value;
            return *this;
        }

        Options &setMarginBottom(int value) {
            margins.bottom = value;
            return *this;
        }

        Options &setMarginTop(int value) {
            margins.top = value;
            return *this;
        }

        Options &setPadding(uint value) {
            padding.top = padding.left = padding.right = padding.bottom = value;
            return *this;
        }

        Options &setPaddingLeft(uint value) {
            padding.left = value;
            return *this;
        }

        Options &setPaddingRight(uint value) {
            padding.right = value;
            return *this;
        }

        Options &setPaddingBottom(uint value) {
            padding.bottom = value;
            return *this;
        }

        Options &setPaddingTop(uint value) {
            padding.top = value;
            return *this;
        }

        Options &setUnderline(bool value = true) {
            underline = value;
            return *this;
        }

        Options &setBoundline(bool value = true) {
            boundline = value;
            return *this;
        }

        Options &setFillWidth(bool value) {
            row = value;
            return *this;
        }

        Options &setHeader(bool value) {
            header = value;
            return *this;
        }

        Options &setFluid(bool value = true) {
            fluid = value;
            return *this;
        }
    };
}

#endif //QTPRINTDOCUMENT_BASE_H
