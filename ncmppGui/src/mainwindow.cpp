#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "getpath.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDir>

#include <thread>

#include <lib/qtmaterialstyle.h>
#include <lib/qtmaterialtheme.h>

#define LINEEDIT_RED_STYLE "QLineEdit{color: rgb(255, 0, 0);}"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->dirChoose_button, SIGNAL(clicked()),
        this, SLOT(fileButtonClicked())
    );
    connect(
        ui->do_button, SIGNAL(clicked()),
        this, SLOT(doButtonClicked())
    );
    connect(
        ui->import_button, SIGNAL(clicked()),
        this, SLOT(importButtonClicked())
    );
    connect(
        ui->resetThreadCount_button, SIGNAL(clicked()),
        this, SLOT(resetThreadCountButtonClicked())
    );
    connect(
        ui->outDir_lineEdit, SIGNAL(textChanged(QString)),
        this, SLOT(outputDirChanged(QString))
    );

    connect(ui->input_listWidget, SIGNAL(dropEnd()), this, SLOT(updateProgressbar()));

    QtMaterialTheme* theme = new QtMaterialTheme;
    theme->setColor("text", Material::red500);
    theme->setColor("primary1", Material::red300);

    QtMaterialStyle::instance().setTheme(theme);

    updateProgressbar();

    ui->import_button->setFocus();
    ui->spin_threadCount->setValue(std::thread::hardware_concurrency());
}

void MainWindow::fileButtonClicked()
{
    QString get = QFileDialog::getExistingDirectory(
        this, QStringLiteral("输出目录"),
        get_home_path(),
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks
#ifdef Q_OS_ANDROID
        | QFileDialog::DontUseNativeDialog
#endif
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
        ui->outDir_lineEdit->setFocus();
        return;
    }

    if (!QFileInfo(out_file).isDir())
    {
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("不是目录"));
        ui->outDir_lineEdit->setFocus();
        return;
    }

    int count = this->ui->input_listWidget->getFileCount();

    if (count == 0)
    {
        QMessageBox::warning(this, QStringLiteral("提醒"), QStringLiteral("没有输入的文件"));
        ui->import_button->setFocus();
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
    ui->progressBar->setProgressType(Material::DeterminateProgress);

    unlockThread = new Unlocker;
    unlockThread->setMaxThreadCount(this->ui->spin_threadCount->value());
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
#ifdef Q_OS_ANDROID
        ,QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog
#endif
    );

    if (path.isEmpty())
    {
        return;
    }

    if (!QFileInfo::exists(path))
    {
        QMessageBox::critical(this, "错误", "目录不存在");
        return;
    }

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
    updateProgressbar();
}

void MainWindow::resetThreadCountButtonClicked()
{
    ui->spin_threadCount->setValue(std::thread::hardware_concurrency());
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

    updateProgressbar();
}

void MainWindow::updateProgressbar()
{
    if (ui->input_listWidget->count() && !ui->outDir_lineEdit->text().isEmpty())
    {
        ui->progressBar->setProgressType(Material::IndeterminateProgress);
    }
    else
    {
        ui->progressBar->setProgressType(Material::DeterminateProgress);
    }
}

void MainWindow::outputDirChanged(const QString& text)
{
    QString new_style = "";
    if (!QFile(text).exists())
    {
        new_style = LINEEDIT_RED_STYLE;
    }
    if (!QFileInfo(text).isDir() && new_style.isEmpty())
    {
        new_style = LINEEDIT_RED_STYLE;
    }
    ui->outDir_lineEdit->setStyleSheet(new_style);
    updateProgressbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}
