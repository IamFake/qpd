#include <QDebug>
#include <QProcess>
#include <QGuiApplication>

#include "wrap.h"
#include "text.h"
#include "block.h"
#include "table.h"

using namespace Qpd;

void Wrap::start() {
    auto doc = new Qpd::Document();
    doc->printStart(true, QGuiApplication::applicationDirPath() + "/test.qpd.pdf");
    print(doc->painter, doc);
    doc->printEnd();

    qDebug() << "Here is " << QGuiApplication::applicationDirPath() + "/test.qpd.pdf";

    // xdg-open for Linux
    // @todo add for windows
    QProcess::startDetached("xdg-open " + QGuiApplication::applicationDirPath() + "/test.qpd.pdf");

    emit finished();
}

void Wrap::print(QPainter *p, Document *doc) {
    auto table1 = new Qpd::Table(doc);

    table1
        ->addRow(
            (new Qpd::Block(doc))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::CENTER, "Column 1", Qpd::Options().setBorder(1))
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Align::NONE, Qpd::Options().setBorder(1).setHeader(true)))
                        ->addCell(
                            (new Qpd::Block(doc, Qpd::Options().setFillWidth(true)))
                                ->addCell(
                                    new Qpd::Text(
                                        doc,
                                        Qpd::Position::CENTER,
                                        "sub col 0"
                                    )
                                )
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::CENTER, "sub col 1")
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::CENTER, "sub col 2")
                        )
                )
        )
        ->addRow(
            (new Qpd::Block(doc))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "row 1 (w bound line)",
                                  Options().setMarginTop(10).setMarginBottom(10).setMarginLeft(25).setBoundline())
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Align::NONE, Qpd::Options().setBorder(1).setHeader(true)))
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "sub row 1", Options().setMarginTop(20))
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "sub row 2")
                        )
                )
        )
        ->addRow(
            (new Qpd::Block(doc))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "row 2 (w underline)",
                                  Options().setMarginTop(0).setMarginBottom(10).setMarginLeft(20).setUnderline())
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Align::NONE, Qpd::Options().setBorder(1).setHeader(true)))
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "1000", Options().setMarginTop(10))
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "1000")
                        )
                )
        )
        ->addRow(
            (new Qpd::Block(doc))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "row 3",
                                  Options().setMarginTop(10).setMarginBottom(0).setMarginLeft(15))
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Align::NONE, Qpd::Options().setBorder(1).setHeader(true)))
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "1000")
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "9 874 159")
                        )
                )
        )
        ->addRow(
            (new Qpd::Block(doc))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "row 4")
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Align::NONE, Qpd::Options().setBorder(1).setHeader(true)))
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "1000", Options().setMarginTop(30))
                        )
                        ->addCell(
                            new Qpd::Text(doc, Qpd::Position::LEFT, "1000")
                        )
                )
        )
        ->draw();

    auto table2 = new Qpd::Table(doc);

    table2
        ->addRow(
            (new Qpd::Block(doc, Options().setPadding(0), "R-0"))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::CENTER,
                                  "A quasar is an active galactic nucleus of very high luminosity. A quasar consists of a "
                                      "supermassive black hole surrounded by an orbiting accretion disk of gas.")
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 40, 254)),
                                    "R-1"))
                        ->addCell(
                            (new Qpd::Block(doc, Qpd::Options().setFillWidth(true), "R-2"))
                                ->addCell(
                                    new Qpd::Text(
                                        doc,
                                        Qpd::Position::CENTER,
                                        "As gas in the accretion disk falls toward the black hole, energy is released in "
                                            "the form of electromagnetic radiation.",
                                        Options().setUnderline(true)
                                    )
                                )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "Quasars emit energy across the electromagnetic spectrum and can be observed at radio, "
                                    "infrared, visible, ultraviolet, and X-ray wavelengths.",
                                Options().setFillWidth(true).setUnderline(true)
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "String 1",
                                Options().setUnderline()
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "Another string",
                                Options().setUnderline()
                            )
                        )
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 240, 254))))
                        ->addCell(
                            (new Qpd::Block(doc, Qpd::Options().setFillWidth(true)))
                                ->addCell(
                                    new Qpd::Text(
                                        doc,
                                        Qpd::Position::CENTER,
                                        "The most powerful quasars have luminosities exceeding 1041 W, thousands of times greater "
                                            "than the luminosity of a large galaxy such as the Milky Way."
                                    )
                                )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "Sub col 1"
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "Sub col 2"
                            )
                        )
                )
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::CENTER,
                                  "The term \"quasar\" originated as a contraction of \"quasi-stellar radio source\", "
                                      "because quasars were first identified as sources of radio-wave emission, and in "
                                      "photographic images at visible wavelengths they resembled point-like stars.")
                )
        )
        ->addRow(
            (new Qpd::Block(doc, Options().setPadding(0)))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::CENTER, "1250")
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 40, 254))))
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "444"
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "555"
                            )
                        )
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 240, 254))))
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "777"
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::CENTER,
                                "888"
                            )
                        )
                )
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::CENTER, "6500")
                )
        )
        ->addRow(
            (new Qpd::Block(doc, Options().setPadding(0)))
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "1 000 240")
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 40, 254))))
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::LEFT,
                                "6 802"
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::LEFT,
                                "4 550"
                            )
                        )
                )
                ->addCell(
                    (new Qpd::Block(doc, Qpd::Options().setHeader(true).setBorderColor(QColor(240, 40, 240, 254))))
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::LEFT,
                                "10 250"
                            )
                        )
                        ->addCell(
                            new Qpd::Text(
                                doc,
                                Qpd::Position::LEFT,
                                "21 240"
                            )
                        )
                )
                ->addCell(
                    new Qpd::Text(doc, Qpd::Position::LEFT, "600 512")
                )
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered very long long text, like long long unsigned int but "
            "not only 64 bits, with additional characters to make this column really tall"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1).setHeader(true).setWidth(350)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1).setHeader(true).setWidth(150)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text 2", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #4"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #5"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #6"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "B Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(7).setHeader(true).setWidth(350)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->addCell(
            (new Block(doc, Align::EMPTY,
                       Options().setBorder(7).setHeader(true).setWidth(150).setBorderColor(QColor(240, 90, 210, 254))))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text 2", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #4"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #5"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #6"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "B Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY,
                       Options().setBorder(1).setPadding(5).setHeader(true).setBorderColor(QColor(240, 90, 210, 254))))
                ->addCell(new Text(doc, Position::CENTER, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::RIGHT, "sub cell #3"))
        )
        ->addCell(
            (new Block(doc, Align::EMPTY,
                       Options().setBorder(1).setPadding(5).setHeader(true).setBorderColor(QColor(160, 90, 240, 254))))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text 2", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #4"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #5"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #6"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "B Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY,
                       Options().setBorder(1).setPadding(5).setHeader(true).setWidth(300).setBorderColor(
                           QColor(240, 90, 210, 254))))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->addCell(
            (new Block(doc, Align::EMPTY,
                       Options().setBorder(1).setPadding(5).setHeader(true).setWidth(100).setBorderColor(
                           QColor(160, 90, 240, 254))))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text 2", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #4"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #5"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #6"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "B Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(5).setPadding(5).setHeader(true).setWidth(300)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(5).setPadding(5).setHeader(true).setWidth(100)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text 2", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #4"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #5"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #6"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25).setPadding(5)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text z"))
        ->addCell(
            (new Block(doc, Align::RIGHT,
                       Options().setBorder(2).setBorderColor(QColor(150, 24, 78, 254)).setPadding(10)
                           .setMargin(5).setHeader(true)))
                ->addCell(
                    new Text(doc, Position::RIGHT, "Header text fst\nwith new\nline", Options().setFillWidth(true)))
                ->addCell(
                    new Text(doc, Position::LEFT, "Header text snd\nwith new\nline", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "cell #1", Options().setUnderline(true)))
                ->addCell(new Text(doc, Position::EMPTY, "cell #2", Options().setUnderline(true)))
                ->addCell(new Text(doc, Position::EMPTY, "cell #3", Options().setUnderline(true)))
                ->addCell(new Text(doc, Position::EMPTY, "cell #4", Options().setUnderline(true)))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25), "outer"))
        ->addCell(new Text(doc, Position::CENTER, "Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1).setMargin(10).setPadding(10), "inner"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #0", Options().setUnderline()))
                ->addCell(new Text(doc, Position::RIGHT, "sub cell #1", Options().setUnderline()))
                ->addCell(new Text(doc, Position::CENTER, "#2", Options().setUnderline()))
                ->addCell(new Text(doc, Position::LEFT, "sub cell #3", Options().setUnderline()))
        )
        ->draw();

    (new Block(doc, Options().setMarginBottom(25).setMarginLeft(25).setBorder(1)))
        ->addCell(
            new Text(doc, Position::LEFT, "String to left")
        )
        ->addCell(
            new Block(doc, Align::RIGHT, Options(),
                      new Text(doc, Position::CENTER, "Centered string aligned to right",
                               Options().setWidth(200).setUnderline())
            )
        )
        ->draw();

    (new Qpd::Text(doc, Qpd::Position::LEFT, "1. Основная территория",
                   Qpd::Options().setMarginBottom(8).setMarginLeft(25)))
        ->draw();

    (new Qpd::Block(doc, Qpd::Options().setMarginBottom(25).setBorder(1)))
        ->addStubCell()
        ->addCell(
            new Qpd::Text(
                doc,
                Qpd::Position::INLINE,
                "Зазюков А.Ю.",
                Qpd::Options().setUnderline()
            ),
            Qpd::Align::CENTER
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text"))
        ->addCell(
            (new Block(doc, Align::NONE, Options().setBorder(1).setHeader(false)))
                ->addCell(new Text(doc, Position::RIGHT, "Header text\nwith new line", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text"))
        ->addCell(
            (new Block(doc, Align::RIGHT, Options().setBorder(1).setHeader(true).setPadding(5)))
                ->addCell(new Text(doc, Position::CENTER, "Header text\nwith new line", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text z"))
        ->addCell(
            (new Block(doc, Align::RIGHT, Options().setBorder(1).setPadding(5).setMargin(5)))
                ->addCell(new Text(doc, Position::EMPTY, "cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "cell #3"))
                ->addCell(new Text(doc, Position::EMPTY, "cell #4"))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text z"))
        ->addCell(
            (new Block(doc, Align::RIGHT, Options().setBorder(1).setPadding(5)))
                ->addCell(new Text(doc, Position::CENTER, "Header text"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text z"))
        ->addCell(
            (new Block(doc, Align::RIGHT, Options().setBorder(1).setWidth(250)))
                ->addCell(new Text(doc, Position::CENTER, "Header text s\nwith new line", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text",
                                   Options().setFillWidth(true).setMarginBottom(55)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1", Options().setMarginBottom(15)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))

        )
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1).setMarginBottom(25)))
        ->addCell(new Text(doc, Position::CENTER, "A Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1).setHeader(true)))
                ->addCell(new Text(doc, Position::EMPTY, "set Fill Width text", Options().setFillWidth(true)))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))
        )
        ->addCell(new Text(doc, Position::EMPTY, "Last cell text"))
        ->draw();

    (new Block(doc, Align::EMPTY, Options().setBorder(1)))
        ->addCell(new Text(doc, Position::CENTER, "Centered text"))
        ->addCell(
            (new Block(doc, Align::EMPTY, Options().setBorder(1)))
                ->addCell(
                    (new Block(doc, Align::EMPTY/*, Options().setFillWidth(true)*/))
                        ->addCell(new Text(doc, Position::CENTER, "setFillWidth text", Options().setFillWidth(true)))
                )
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #1"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #2"))
                ->addCell(new Text(doc, Position::EMPTY, "sub cell #3"))

        )
        ->draw();

    QString text = "String with new line symbol\nhere: %1";

    Block *bl0 = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(4));
    bl0->mark = "outer first";
    Block *bl1 = new Block(doc);
    bl1->mark = "bl0 first cell";
    bl1->options.fluid = true;
    Block *bl3 = new Block(doc, Align::RIGHT, Options().setBorder(1).setPadding(10));
    bl3->mark = "bl0 last cell";

    Block *date = new Block(doc, Align::CENTER, QDate::currentDate());
    date->mark = "bl0 date";

    QString tx3_4 = "СТРОКА\nС длиннющим переносом";
    QString tx3_5 = "Трам пам пам asdf asdf asf sef asdf asdf asdf asdf as";

    Text *t1 = new Text(doc, Position::INLINE, "111111");
    Text *t2 = new Text(doc, Position::INLINE, "222222");
    Text *t3_4 = new Text(doc, Position::INLINE, tx3_4);
    Text *t3_5 = new Text(doc, Position::INLINE, tx3_5);

    bl1->addCell(t1);
    bl1->addCell(t2);

    bl3->addCell(t3_4);
    bl3->addCell(t3_5);

    bl0->addCell(bl1);
    bl0->addCell(date);
    bl0->addCell(bl3);
    bl0->draw();

    QString zx = "Эйнштейну принадлежит решающая роль в популяризации и введении в научный оборот новых физических концепций и теорий.";
    Text *z1 = new Text(doc, Position::LEFT, "333333");
    z1->mark = "z1";
    Text *z2 = new Text(doc, Position::INLINE, "sdfasefasf");
    z2->mark = "z2";
    Text *z3 = new Text(doc, Position::CENTER, zx);
    z3->mark = "z3";

    Block *bl5 = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(10));
    bl5->addCell(z1)->addCell(z2)->addCell(z3)->draw();

    for (int i = 0; i < 9; i += 3) {
        QString localText = text.arg(i);

        Block *blk = new Block(doc);

        Options t3opts;
        t3opts.setUnderline().setMarginBottom(25);

        Text *t1 = new Text(doc, Position::LEFT, localText);
        Text *t2 = new Text(doc, Position::CENTER, localText);
        Text *t3 = new Text(doc, Position::RIGHT, localText, t3opts);

        blk->addCell(t1);
        blk->addCell(t2);
        blk->addCell(t3);

        blk->draw();
    }

    doc->switchOrientation(Orientation::Landscape);

    auto table3 = new Table(doc);

    Block *testBlock = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(4));

    QString tt1 = "Test string 1";
    Text *te1 = new Text(doc, Position::LEFT, tt1);

    QString tt2 = "Test string 2";
    Text *te2 = new Text(doc, Position::LEFT, tt2);

    QString tt3 = "Test string 3";
    Text *te3 = new Text(doc, Position::LEFT, tt3);

    testBlock->addCell(te1, 150);
    testBlock->addCell(te2);
    testBlock->addCell(te3, 150);
//    testBlock->draw();

    Block *stestBlock = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(4));

    QString stt1 = "Test string 4";
    Text *ste1 = new Text(doc, Position::LEFT, stt1);

    QString stt2 = "Test string 5";
    Text *ste2 = new Text(doc, Position::LEFT, stt2);

    QString stt3 = "Test string 6";
    Text *ste3 = new Text(doc, Position::LEFT, stt3);

    stestBlock->addCell(ste1);
    stestBlock->addCell(ste2);
    stestBlock->addCell(ste3);
//    stestBlock->draw();

    Block *ztestBlock = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(4));

    QString ztt1 = "Test string 7";
    Text *zte1 = new Text(doc, Position::LEFT, ztt1);

    QString ztt2 = "Test string 8";
    Text *zte2 = new Text(doc, Position::LEFT, ztt2);

    QString ztt3 = "Test string 9";
    Text *zte3 = new Text(doc, Position::LEFT, ztt3);

    ztestBlock->addCell(zte1);
    ztestBlock->addCell(zte2);
    ztestBlock->addCell(zte3);

    Block *ktestBlock = new Block(doc, Align::NONE, Options().setBorder(1).setPadding(4));

    QString ktt1 = "Test string 10";
    Text *kte1 = new Text(doc, Position::LEFT, ktt1);

    QString ktt2 = "Test string 11";
    Text *kte2 = new Text(doc, Position::LEFT, ktt2);

    QString ktt3 = "Test string 12";
    Text *kte3 = new Text(doc, Position::LEFT, ktt3);

    ktestBlock->addCell(kte1);
    ktestBlock->addCell(kte2);
    ktestBlock->addCell(kte3);

    table3->addRow(testBlock);
    table3->addRow(stestBlock);
    table3->addRow(ztestBlock);
    table3->addRow(ktestBlock);
    table3->draw();

    qDebug() << "Draw DONE........";
}