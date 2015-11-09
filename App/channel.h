#ifndef CHANNEL_H
#define CHANNEL_H

#include <functional>
#include <memory>
#include <QWebChannel>



namespace Channel {

    struct WebChannel{
        std::shared_ptr<QWebChannel> channel;
        QString url;

    };

    std::function<WebChannel ()> makeChannel();

}
#endif // CHANNEL_H
