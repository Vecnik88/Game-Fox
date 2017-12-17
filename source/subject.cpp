#include "include/subject.h"

Subject::Subject(const QString &typeSrc,
                 const QString &pathSrc,
                       QWidget *parent):
                       QFrame(parent)
{
    type = typeSrc;
    path = pathSrc;

    setMinimumSize(100, 150);
    setMaximumSize(100, 150);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    subject = new QLabel(this);
    subject->setPixmap(QPixmap(PATH_IMAGE));
    subject->show();
    subject->setAttribute(Qt::WA_DeleteOnClose);
}

Subject::~Subject()
{
    delete subject;
}

const QString &Subject::getPath()
{
    return path;
}

const QString &Subject::getType()
{
    return type;
}

void Subject::setParametrs(const QString &typeSrc,
                           const QString &pathSrc)
{
    path = pathSrc;
    type = typeSrc;
}

void Subject::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
        QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
        if (!child) {
            qDebug() << "<Subject::mousePressEvent> child is null" << endl;
            return;
        }

        QPixmap pixmap = *child->pixmap();

        QByteArray buffer;
        QDataStream dataStream(&buffer, QIODevice::WriteOnly);
        dataStream << pixmap << 1 << type << QPoint(1000, 1000);

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", buffer);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());
        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        child->setPixmap(tempPixmap);
        drag->exec(Qt::CopyAction);
        child->show();
        child->setPixmap(pixmap);
    }
}

void Subject::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - dragStartPosition).manhattanLength()
       < QApplication::startDragDistance())
        return;
}



