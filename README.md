# Qpd: Qt Print Document library

Qpd library allowing programmatically create simple documents and print to
QPrinter (on real printer or to PDF files).

Wide range of examples can be found in wrap.cpp file.

By default debug output is turned off in base.h by defining
QT_NO_DEBUG_OUTPUT macro, comment it if you need debug output during
calculation and drawing (it's a bit chaotic).

@todo improve docs

## Qpd::Document
Document class holds current position and dimensions of the page. Also
Document becomes a parent for all other elements and delete they
automatically while destruction phase.

Every element should be instantiated with Document as a parent.  
To draw element to QPainter you must call **draw** method on him.

    auto doc = new Qpd::Document();
    doc->printStart(true, QGuiApplication::applicationDirPath() + "/test.qpd.pdf");
    ...
    doc->printEnd();

#### Qpd::Document::printStart
Configuring printer and painter

**arguments**
- PDF **bool** (print to pdf or to printer)
- Filename **QString** PDF file name

#### Qpd::Document::printEnd
Call *end* on painter (end drawing and start actual printing)

## Qpd::Text
Text is basic element which draw a string.

You could create Text with QString or with QStringList

`Text(Document *root, Position tpos, QString const &text, Options opts = Options());`  
`Text(Document *root, Position tpos, QStringList &textList, Options opts = Options());`

Can have margins (through Qpd::Options)

    auto doc = new Qpd::Document();
    doc->printStart(true, QGuiApplication::applicationDirPath() + "/test.qpd.pdf");
     
    (new Text(doc, Position::CENTER, "String to draw"))->draw();
     
    doc->printEnd();

## Qpd::Block
Block is responsible for positioning and grouping of Qpd::Text or other
Qpd::Block elements.

All Block childs would have equal width (if width of child wasn't set
explicitly)

Can have borders, margins, paddings, child alignment.

    Block(Document *root, Options topts, QString const &objMark = "");
    Block(Document *root, Align talign, QDate date, Options topts = Options());
    Block(Document *root, Align talign, Options topts, Text *text);

**arguments**
- root **Qpd::Document** document
- topts **Qpd::Options** options for current block
- talign **Qpd::Align** alignment for current block
- text **Qpd::Text** shorthand if we need only one text node in block 
- objMark **QString** mark for object (for debug)  


Example:

    auto doc = new Qpd::Document();
    doc->printStart(true, QGuiApplication::applicationDirPath() + "/test.qpd.pdf");
     
    (new Block(doc))
    ->addCell(
        new Text(doc, Position::EMPTY, "String to draw")
    )
    ->addCell(
        new Text(doc, Position::EMPTY, "Second string to draw")
    )
    ->draw();
     
    doc->printEnd();

`Qpd::Block::addCell(Stackable *stack, uint width = 0)`  
Add cell (child) and set explicit width to it

`Qpd::Block::addCell(Stackable *stack, Position tpos)`  
Add cell (child) and set explicit position to it

`Qpd::Block::addCell(Stackable *stack, Align talign)`  
Add cell (child) and set explicit align to it

`Qpd::Block::addCell(Stackable *stack, Position tpos, Align talign, uint width)`  
Add cell (child) and set explicitly all args

`Qpd::Block::prependCell(...)`  
Same as for addCell

## Qpd::Table
Table just makes sure that *width* of all added Qpd::Block's (and their
top-most cells) are the same.

### Qpd::Position
Used to alignment **Text** by horizontal

### Qpd::Align
Used to alignment **Block** cells (childs) by horizontal.

For example *inline* Text can't be aligned by Position, only by Align
inside of block

### Qpd::Options
Some of option's methods

`Qpd::Options::setInlined`  
Make node **inline**, e.g. width can be shrink to width of the real content

`Qpd::Options::setWidth`  
Set width explicitly (otherwise it will be calculated automatically) 

`Qpd::Options::setUnderline`  
Set underline for text content

`Qpd::Options::setBoundline`  
Set underline for box

`Qpd::Options::setHeader`  
Set **Block** cell to be *header*, e.g. if parent Block have paddings -
*header cell* would ignore that padding and stick to parent borders

`Qpd::Options::setFillWidth`  
Set **Block** cell to have 100% width of parent, displacing the remaining
cells to next row (some sort of emulation of colspan in html tables)
