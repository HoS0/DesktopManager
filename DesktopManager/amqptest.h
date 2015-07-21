#ifndef AMQPTEST_H
#define AMQPTEST_H

#include <QObject>

%NAMESPACE_BEGIN%class amqptest : public QObject
{%Q_OBJECT%
public:
    amqptest(%CTORSIG%);
    ~amqptest();

private:
    
};

%NAMESPACE_END%#endif // AMQPTEST_H
