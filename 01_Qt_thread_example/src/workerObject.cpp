#include "workerObject.hpp"

#include <QMutexLocker>
#include <QThread>

void workerObject::runSomeBigWork()
{
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

        QThread::msleep(500);
        emit resultUpdated(i);
    }
}

void workerObject::stop()
{
    QMutexLocker locker(&stopMutex_);
    // emit message(QString("%1->%2,thread id:%3")
    //                  .arg(__FUNCTION__)
    //                  .arg(__FILE__)
    //                  .arg((int)QThread::currentThreadId()));
    isStopped_ = true;
}
