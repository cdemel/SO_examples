#include "listerrs.h"
#include <QDebug>

void ListErrs::go(QNetworkReply *, QList<QSslError> errors) {
    for (int i = 0; i < errors.size(); i++) {
        qDebug() << "SSL Error number " << i << ": " << (errors[i]).errorString();
    }
}
