#include "olinkimageprovider.h"
#include <QImage>
#include <QSvgRenderer>
#include <QPainter>

OlinkImageProvider::OlinkImageProvider(const QString &path):
    QQuickImageProvider(QQmlImageProviderBase::Image),
    m_path(path)
{
}

OlinkImageProvider::~OlinkImageProvider()
{

}

QImage OlinkImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QSize i_size(128,128);
    if(requestedSize.isValid()){
        i_size = requestedSize;
    }
    QImage image(i_size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    QSvgRenderer renderer(m_path);
    renderer.render(&painter, id);
    *size = image.size();
    return image;
}
