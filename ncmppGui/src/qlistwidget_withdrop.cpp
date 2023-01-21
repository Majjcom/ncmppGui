#include "qlistwidget_withdrop.h"

#include <QListWidgetItem>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QList>
#include <QUrl>

QListWidget_withDrop::QListWidget_withDrop(QWidget *parent)
{
    this->setParent(parent);
}


void QListWidget_withDrop::dragEnterEvent(QDragEnterEvent* ev)
{
    if (ev->mimeData()->hasUrls())
    {
        ev->acceptProposedAction();
    }
    else
    {
        ev->ignore();
    }
}

void QListWidget_withDrop::dropEvent(QDropEvent* ev)
{
    if (ev->mimeData()->hasUrls())
    {
        QList<QUrl> url_list = ev->mimeData()->urls();
        for (int i = 0; i < url_list.size(); i++)
        {
            QString name = url_list.at(i).toLocalFile();
            QFileInfo info(name);
            if (info.suffix() != "ncm" || info.isDir())
            {
                continue;
            }
            QList<QListWidgetItem*> find =this->findItems(name, Qt::MatchExactly);
            if (find.empty())
            {
                this->addItem(name);
            }
        }
    }
}

QString QListWidget_withDrop::getNextFile()
{
    QListWidgetItem* item = this->takeItem(0);
    return item->text();
}
int QListWidget_withDrop::getFileCount()
{
    return this->count();
}
