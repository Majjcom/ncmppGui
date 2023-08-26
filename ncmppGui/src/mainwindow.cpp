#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include "ncmdump.h"

#include "getpath.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->dirChoose_button, SIGNAL(clicked()),
        this, SLOT(fileButtonClicked())
    );
    this->connect(ui->do_button, SIGNAL(clicked()),
        this, SLOT(doButtonClicked())
    );
    this->connect(ui->import_button, SIGNAL(clicked()),
        this, SLOT(importButtonClicked())
    );
}

void MainWindow::fileButtonClicked()
{
    QString get = QFileDialog::getExistingDirectory(
        this, QStringLiteral("输出目录"),
        get_home_path(),
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks
    );
    if (get.length() != 0)
    {
        ui->outDir_lineEdit->setText(get);
    }
}

void MainWindow::doButtonClicked()
{
    QString out_file = this->ui->outDir_lineEdit->text();
    if (!QFile(out_file).exists())
    {
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("输出目录不存在"));
        return;
    }

    if (!QFileInfo(out_file).isDir())
    {
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("不是目录"));
        return;
    }

    int count = this->ui->input_listWidget->getFileCount();

    if (count == 0)
    {
        QMessageBox::warning(this, QStringLiteral("提醒"), QStringLiteral("没有输入的文件"));
        return;
    }

    if (this->unlockThread != nullptr)
    {
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("解锁正在运行"));
        return;
    }

    ui->do_button->setEnabled(false);
    ui->dirChoose_button->setEnabled(false);
    ui->outDir_lineEdit->setReadOnly(true);
    ui->input_listWidget->setDragDropMode(QListWidget::NoDragDrop);

    unlockThread = new Unlocker;
    unlockThread->setUp(this->ui->input_listWidget, out_file);
    unlockThread->start();

    connect(this->unlockThread, SIGNAL(unlocked(int, int)),
        this, SLOT(unlocked(int, int))
    );
    connect(this->unlockThread, SIGNAL(finished()),
        this, SLOT(threadFinished())
    );


}

void MainWindow::importButtonClicked()
{
    QString path = QFileDialog::getExistingDirectory(
        this,
        QStringLiteral("选择ncm文件所在的目录"),
        get_home_path()
    );

    QDir root_dir(path);
    QStringList files = root_dir.entryList(QDir::Files);
    for (QString& name : files)
    {
        QFileInfo info(name);
        if (info.suffix() == "ncm")
        {
            QString ab_path = root_dir.absoluteFilePath(name);
            ui->input_listWidget->addFile(ab_path);
        }
    }
}

void MainWindow::unlocked(int count, int total)
{
    float v = float(count) / float(total) * 100.0f;
    ui->progressBar->setValue(int(v));
}

void MainWindow::threadFinished()
{
    this->disconnect(this->unlockThread);

    unlockThread->deleteLater();
    unlockThread = nullptr;

    QMessageBox::information(this, QStringLiteral("完成"), QStringLiteral("解锁已完成"));
    ui->progressBar->setValue(0);
    ui->outDir_lineEdit->setReadOnly(false);
    ui->dirChoose_button->setEnabled(true);
    ui->do_button->setEnabled(true);
    ui->input_listWidget->setDragDropMode(QListWidget::InternalMove);
}

MainWindow::~MainWindow()
{
    delete ui;
}
