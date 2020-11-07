#include "workerObject.hpp"

#include <QMutexLocker>
#include <QThread>

void workerObject::runSomeBigWork()
{
    const QString msg =
        QString("%1->%2, thread id:%3")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg(reinterpret_cast<int>(QThread::currentThreadId()));
    emit message(msg);

    {
        QMutexLocker locker(&stopMutex_);
        isStopped_ = false;
    }

    /* expensive or blocking operation ... */
    for (int i = 1; i <= 100; i++)
    {
        {
            QMutexLocker locker(&stopMutex_);
            if (isStopped_) return;
        }

        const QString msg =
            QString("Run %1 step, thread id:%2")
                .arg((int)i)
                .arg(reinterpret_cast<int>(QThread::currentThreadId()));
        emit message(msg);

        QThread::msleep(100);
        emit resultUpdated(i);
    }
}

void workerObject::stop()
{
    QMutexLocker locker(&stopMutex_);

    emit message(QString("%1->%2,thread id:%3")
                     .arg(__FUNCTION__)
                     .arg(__FILE__)
                     .arg(reinterpret_cast<int>(QThread::currentThreadId())));

    isStopped_ = true;
}
