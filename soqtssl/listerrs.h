#include <QObject>
#include <QList>
#include <QSslError>
#include <QNetworkReply>

class ListErrs : public QObject {
    Q_OBJECT
public:
public slots:
    void go(QNetworkReply *, QList<QSslError> errors);
};

