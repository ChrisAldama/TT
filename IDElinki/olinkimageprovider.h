#ifndef OLINKIMAGEPROVIDER_H
#define OLINKIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class OlinkImageProvider : public QQuickImageProvider
{
public:
    OlinkImageProvider(const QString &path = ":/Images/figuras.svg");
    ~OlinkImageProvider();
    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QString m_path;
};

#endif // OLINKIMAGEPROVIDER_H
