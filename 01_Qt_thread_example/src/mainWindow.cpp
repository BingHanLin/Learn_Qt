#include "mainWindow.h"
#include "./ui_mainWindow.h"
// #include "workderQThread.hpp"
#include "workerObject.hpp"

#include <QPushButton>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    ui->threadProgress->setAlignment(Qt::AlignCenter);
    // ui->threadProgress->setFormat(QString("working on thread %p"));

    worker_ = new workerObject;
    worker_->moveToThread(&workerThread_);
    connect(&workerThread_, &QThread::finished, worker_, &QObject::deleteLater);
    connect(worker_, &workerObject::resultUpdated, this,
            &mainWindow::updateThreadProgress);
    workerThread_.start();

    connect(ui->startBtn, &QPushButton::clicked, worker_,
            &workerObject::runSomeBigWork);

    connect(ui->stopBtn, &QPushButton::clicked, this,
            [=]() { worker_->stop(); });
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
