#ifndef QTPRINTDOCUMENT_TEXT_H
#define QTPRINTDOCUMENT_TEXT_H

#include "base.h"
#include "document.h"
#include "stackable.h"

namespace Qpd {
    class Document;

    class Stackable;

    class Text : public Stackable {
    public:

        static constexpr int TextWordWrap = Qt::TextWordWrap;
        static constexpr int TextWrapAnywhere = Qt::TextWrapAnywhere;
        static constexpr int AlignCenter = Qt::AlignCenter;
        static constexpr int AlignHCenter = Qt::AlignHCenter;

        static int defaultCenterFlag;
        static int defaultTextWrap;

        Text(Document *root, Position tpos, QString const &text, Options opts = Options());

        Text(Document *root, Position tpos, QStringList &textList, Options opts = Options());

        void draw(bool last) override;

        void draw() override;

        void calcPosition(qreal width) override;

        void calcPosition() override;

        uint getTextOpts();
    };
}

#endif //QTPRINTDOCUMENT_TEXT_H
