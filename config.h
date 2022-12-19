#ifndef CONFIG_H
#define CONFIG_H
#include <QString>


class config
{
public:
    config();
    static QString HTTP_URL;
    static int TCP_PORT;
    static QString TCP_HOST;
    static QString WS_PORT;
};

#endif // CONFIG_H
