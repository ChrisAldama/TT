#include <QtWebSockets/QWebSocketServer>
#include <QObject>
#include <QUrl>
#include <memory>
#include "channel.h"
#include "websockettransport.h"
#include "websocketclientwrapper.h"



std::function<Channel::WebChannel ()> Channel::makeChannel()
{
    std::shared_ptr<QWebSocketServer>
            server(new QWebSocketServer("",QWebSocketServer::NonSecureMode));
    std::shared_ptr<WebSocketClientWrapper>
            wrapper(new WebSocketClientWrapper(server.get()));
    std::shared_ptr<QWebChannel>
            channel(new QWebChannel);

    return [=](){
        QObject::connect(wrapper.get(), &WebSocketClientWrapper::clientConnected,
                         channel.get(), &QWebChannel::connectTo);
        server->listen();
        Channel::WebChannel result = {channel,
                             server->serverUrl().toString()};
        return result;
    };
}
