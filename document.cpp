#include "document.h"
#include "text.h"
#include "block.h"
#include "table.h"

#include <QThread>

using namespace Qpd;

Document::Document(QObject *parent) : QObject(parent) {}

Document::~Document() {
    qDebug() << "Qpd::Document destruct...";
    for (Stackable *item : stack) {
        delete item;
    }

    delete painter;
    delete printer;
}

void Document::previewDialogInit() {
    auto localPrinter = new QPrinter();
    preview = new QPrintPreviewDialog(localPrinter);

    QObject::connect(preview, &QPrintPreviewDialog::paintRequested, [this] (QPrinter * actualPrinter) {
        printerPreviewInit(actualPrinter);
        emit dialogIsReady(this);
    });
    QObject::connect(preview, &QPrintPreviewDialog::finished, [this] {
        preview->deleteLater();

        emit printingEnd();
        deleteLater();
    });

    preview->open();
}

void Document::printerPreviewInit(QPrinter * actualPrinter) {
    printer = actualPrinter;

    preparePaint(false, "");
}

void Document::previewDialogPaintEnd() const {
    painter->end();
}

void Document::printerStandardInit(bool pdf, QString const &pdfFilename) {
    printer = new QPrinter();

    preparePaint(pdf, pdfFilename);
}

void Document::printerStandardEnd() {
    painter->end();

    emit printingEnd();
    deleteLater();
}

void Document::preparePaint(bool pdf, QString const &pdfFilename) {
    QPageLayout layout;
    layout.setUnits(QPageLayout::Millimeter);
    layout.setPageSize(QPageSize(QPageSize::A4));
    layout.setOrientation(QPageLayout::Portrait);
    layout.setMargins(QMargins(7, 7, 7, 7));

    printer->setPageLayout(layout);

    emit printingStart();

    if (pdf) {
        printer->setOutputFormat(QPrinter::PdfFormat);
        printer->setOutputFileName(pdfFilename);
        printer->setFontEmbeddingEnabled(true);
    } else {
        printer->setOutputFormat(QPrinter::NativeFormat);
    }

    if (!printer->isValid()) {
        qDebug() << "Printer is INVALID in printRun";
        return;
    }

    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.h = paintRect.height();
    size.w = paintRect.width();
    qDebug() << "set sizes for painting to: " << size.h << " x " << size.w;

    painter = new QPainter();
    bool printStarted = painter->begin(printer);
    if (!printStarted) {
        qDebug() << "Painter is not ACTIVE, probably due to not valid printer";
        return;
    }

    QFont font(defaultFontFamily);
    font.setPixelSize(defaultFontPixelSize);
    painter->setFont(font);

    QPen pen;
    pen.setColor(QColor(0, 0, 0, 254));
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(1);
    pen.setCosmetic(true);

    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);

    painter->setRenderHints(
            QPainter::TextAntialiasing |
            QPainter::HighQualityAntialiasing,
            true
    );
    painter->setRenderHints(
            QPainter::Antialiasing | QPainter::SmoothPixmapTransform,
            false
    );

    position.x = position.y = 0;
}

bool Document::switchOrientation(Orientation newOrientation) {
    if (newOrientation != Orientation::Landscape && newOrientation != Orientation::Portrait) {
        newOrientation = Orientation::Portrait;
    }

    QPageLayout::Orientation translate;
    if (newOrientation == Orientation::Portrait) {
        translate = QPageLayout::Portrait;
    } else {
        translate = QPageLayout::Landscape;
    }

    bool switchResult = printer->setPageOrientation(translate);
    if (switchResult) {
        this->newPage();

        QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
        size.w = paintRect.width();
        size.h = paintRect.height();
    }

    return switchResult;
}

bool Document::setPageMargins(QMarginsF margins) {
    bool setMargins = printer->setPageMargins(margins);

    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.w = paintRect.width();
    size.h = paintRect.height();

    return setMargins;
}

bool Document::setPageMargins(QMarginsF margins, QPageLayout::Unit unit) {
    bool setMargins = printer->setPageMargins(margins, unit);

    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.w = paintRect.width();
    size.h = paintRect.height();

    return setMargins;
}

void Document::newPage() {
    printer->newPage();
    position.x = position.y = 0;
    pages++;
}

void Document::font(QString const &fontName, int pixelSize, bool bold, bool italic) {
    if (pixelSize == 0) {
        pixelSize = defaultFontPixelSize;
    }

    QFont font(fontName);
    font.setPixelSize(pixelSize);
    font.setBold(bold);
    font.setItalic(italic);

    painter->setFont(font);
}

uint Document::getPageCount() const {
    return pages;
}