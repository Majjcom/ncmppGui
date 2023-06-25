#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include "ncmdump.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(this->ui->dirChoose_button, SIGNAL(clicked()),
                  this, SLOT(fileButtonClicked()));
    this->connect(this->ui->do_button, SIGNAL(clicked()),
                  this, SLOT(doButtonClicked()));
}

void MainWindow::fileButtonClicked()
{
    QString get = QFileDialog::getExistingDirectory(this, QStringLiteral("输出目录"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (get.length() != 0)
    {
        this->ui->outDir_lineEdit->setText(get);
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

    this->ui->do_button->setEnabled(false);
    this->ui->dirChoose_button->setEnabled(false);
    this->ui->outDir_lineEdit->setReadOnly(true);
    this->ui->input_listWidget->setDragDropMode(QListWidget::NoDragDrop);

    this->unlockThread = new Unlocker;
    this->unlockThread->setUp(this->ui->input_listWidget, out_file);
    this->unlockThread->start();

    this->connect(this->unlockThread, SIGNAL(unlocked(int, int)),
                  this, SLOT(unlocked(int, int)));
    this->connect(this->unlockThread, SIGNAL(finished()),
                  this, SLOT(threadFinished()));


}

void MainWindow::unlocked(int count, int total)
{
    float v = float(count)/ float(total) * 100.0f;
    this->ui->progressBar->setValue(int(v));
}

void MainWindow::threadFinished()
{
    this->disconnect(this->unlockThread);

    this->unlockThread->deleteLater();
    this->unlockThread = nullptr;

    QMessageBox::information(this, QStringLiteral("完成"), QStringLiteral("解锁已完成"));
    this->ui->progressBar->setValue(0);
    this->ui->outDir_lineEdit->setReadOnly(false);
    this->ui->dirChoose_button->setEnabled(true);
    this->ui->do_button->setEnabled(true);
    this->ui->input_listWidget->setDragDropMode(QListWidget::InternalMove);
}

MainWindow::~MainWindow()
{
    delete ui;
}
