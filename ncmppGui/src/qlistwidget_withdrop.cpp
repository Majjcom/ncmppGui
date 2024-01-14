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

#include "mainwindow.h"

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
            this->addFile(name);
        }
        emit dropEnd();
    }
}

QString QListWidget_withDrop::getNextFile()
{
    QListWidgetItem* item = this->takeItem(0);
    QString t = item->text();
    delete item;
    return t;
}

int QListWidget_withDrop::getFileCount()
{
    return this->count();
}

void QListWidget_withDrop::addFile(QString file)
{
    QList<QListWidgetItem*> find = this->findItems(file, Qt::MatchExactly);
    if (!find.empty())
    {
        return;
    }
    this->addItem(file);
}
