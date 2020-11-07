#include "mainWindow.h"
#include "./ui_mainWindow.h"
#include "workerObject.hpp"
#include "workerQThread.hpp"


#include <QPushButton>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    ui->threadProgress->setAlignment(Qt::AlignCenter);
    // ui->threadProgress->setFormat(QString("working on thread %p"));

    workerObject_ = new workerObject;
    workerObject_->moveToThread(&workerThread_);
    connect(&workerThread_, &QThread::finished, workerObject_,
            &QObject::deleteLater);
    connect(workerObject_, &workerObject::resultUpdated, this,
            &mainWindow::updateThreadProgress);
    connect(workerObject_, &workerObject::message, this,
            &mainWindow::receiveMessage);
    workerThread_.start();

    connect(ui->startBtn, &QPushButton::clicked, workerObject_,
            &workerObject::runSomeBigWork);

    connect(ui->stopBtn, &QPushButton::clicked, this,
            [=]() { workerObject_->stop(); });

    // workerQThread *workerQThread_ = new workerQThread(this);
    // connect(workerQThread_, &WorkerThread::finished, workerQThread_,
    //         &QObject::deleteLater);
    // connect(workerQThread_, &workerQThread::resultUpdated, this,
    //         &mainWindow::updateThreadProgress);

    // workerQThread_->start();
}

mainWindow::~mainWindow()
{
    workerThread_.quit();
    workerThread_.wait();
    delete ui;
}

void mainWindow::updateThreadProgress(const int i)
{
    ui->threadProgress->setValue(i);
}

void mainWindow::receiveMessage(const QString &msg)
{
    ui->textBrowser->append(msg);
}