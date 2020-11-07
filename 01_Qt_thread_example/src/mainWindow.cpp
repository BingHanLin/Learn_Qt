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
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    // ui->threadProgress->setFormat(QString("working on thread %p"));

    workerObject_ = new workerObject;
    workerObject_->moveToThread(&workerThread_);
    connect(&workerThread_, &QThread::finished, workerObject_,
            &QObject::deleteLater);
    connect(workerObject_, &workerObject::resultUpdated, this,
            &mainWindow::updateThreadProgress);
    connect(workerObject_, &workerObject::message, this,
            &mainWindow::receiveMessage);

    connect(ui->startWorkerObjectBtn, &QPushButton::clicked, workerObject_,
            &workerObject::runSomeBigWork);
    connect(ui->stopWorkerObjectBtn, &QPushButton::clicked, this,
            [=]() { workerObject_->stop(); });

    workerThread_.start();

    // !! Running by slot makes workerObject::stop be in queue connection.
    // connect(ui->stopWorkerObjectBtn, &QPushButton::clicked, workerObject_,
    //         &workerObject::stop);

    connect(ui->startWorkerQThreadBtn, &QPushButton::clicked, this,
            &mainWindow::startWorkerQThread);
}

mainWindow::~mainWindow()
{
    workerThread_.quit();
    workerThread_.wait();
    delete ui;
}

void mainWindow::startWorkerQThread()
{
    workerQThread *thread = new workerQThread;
    connect(thread, &workerQThread::finished, thread, &QObject::deleteLater);
    connect(thread, &workerQThread::resultUpdated, this,
            &mainWindow::updateThreadProgress);
    connect(thread, &workerQThread::message, this, &mainWindow::receiveMessage);

    thread->start();
}

void mainWindow::updateThreadProgress(const int i)
{
    ui->threadProgress->setValue(i);
}

void mainWindow::receiveMessage(const QString &msg)
{
    ui->textBrowser->append(msg);
}