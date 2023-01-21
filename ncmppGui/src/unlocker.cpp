#include "unlocker.h"

#include "ncmdump.h"

Unlocker::Unlocker(QObject *parent)
{
    this->setParent(parent);
}

void Unlocker::setUp(QListWidget_withDrop* list_obj_, QString out_dir_)
{
    this->list_obj = list_obj_;
    this->out_dir = out_dir_;
}

void Unlocker::run()
{
    int count = this->list_obj->getFileCount();
    for (int i = 0; i < count; i++)
    {
        using std::string;
        QString file = this->list_obj->getNextFile();
        string src = file.toUtf8().toStdString();
        string tgt = this->out_dir.toUtf8().toStdString();
        ncm::ncmDump(src, tgt);
        this->unlocked(i + 1, count);
    }
    this->exit();
}
