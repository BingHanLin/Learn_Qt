
#include "workerQThread.hpp"

#include <QMutex>
#include <QObject>

void workerQThread::run()
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

void workerQThread::stop()
{
    QMutexLocker locker(&stopMutex_);
    isStopped_ = true;
}
