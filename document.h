#ifndef QTPRINTDOCUMENT_DOCUMENT_H
#define QTPRINTDOCUMENT_DOCUMENT_H

#include "base.h"
#include "stackable.h"

#include <QtCore/QObject>
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>

namespace Qpd {
    class Stackable;

    class Document : public QObject {
    Q_OBJECT
    public:
        itemSize size;
        itemPosition position;

        QString defaultFontFamily = "Courier New";
        uint defaultFontPixelSize = 13;

        uint pages = 1;

        QList<Stackable *> stack;

        QPrinter *printer = nullptr;
        QPainter *painter = nullptr;
        QPrintPreviewDialog *preview = nullptr;

        explicit Document(QObject *parent = nullptr);

        ~Document() override;

        void printStart(bool pdf, QString const &pdfFilename = "");

        void printEnd();

        bool switchOrientation(Orientation newOrientation);

        bool setPageMargins(QMarginsF margins);

        bool setPageMargins(QMarginsF margins, QPageLayout::Unit unit);

        void newPage();

        void font(QString const &fontName, int pixelSize = 0, bool bold = false, bool italic = false);

        uint getPageCount() const;

    signals:

        void printingStart();

        void printingEnd();
    };
}

#endif //QTPRINTDOCUMENT_DOCUMENT_H
