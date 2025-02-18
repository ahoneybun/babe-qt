#ifndef ALBUM_H
#define ALBUM_H
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QToolButton>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QHBoxLayout>
#include <QMenu>
#include <QPainter>
#include <QFileDialog>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include "baeUtils.h"
#include "scrolltext.h"

class Album : public QLabel
{
    Q_OBJECT

public:

    explicit Album(QString imagePath, int widgetSize, int widgetRadius=0, bool isDraggable=false, QWidget *parent = 0);
    ~Album(){}
    void setArtist(const QString &artistTitle);
    void setAlbum(const QString &albumTitle);
    void setTitle(const QString &artistTitle, const QString &albumTitle="");
    void setBGcolor(const QString &bgColor);
    void titleVisible(const bool &state);
    void setTitleGeometry(const int &x, const int &y, const int &w, const int &h);
    void setSize(const int &value);

    int border_radius;
    int size;
    bool borderColor=false;
    QWidget *widget;
    QString getTitle();
    QString getArtist();
    QString getAlbum();
    QString getBGcolor();
    QPixmap image;
    QPixmap getPixmap();
    QToolButton *playBtn;

    enum albumField
    {
        ALBUM, ARTIST, ART
    };

private:

    QMap<int, QString> albumMap;
    bool draggable;
    QString imagePath;
    QString artist="";
    QString album="";
    QString bgColor="";
    ScrollText *title;
    QColor borderQColor;
    QPoint oldPos;
    QPoint startPos;
    void performDrag();

signals:

    void albumCoverClicked(QMap<int, QString> albumMap);
    void albumCoverDoubleClicked(QMap<int, QString> albumMap);
    void playAlbum( QMap<int, QString> albumMap);
    void changedArt( QMap<int, QString> albumMap);
    void babeAlbum_clicked( QMap<int, QString> albumMap);
    void albumDragged();
    void albumCoverEnter();
    void albumCoverLeft();

public slots:

    void putPixmap(const QByteArray &pix);
    void putPixmap(const QString &path);
    void putDefaultPixmap();
    void playBtn_clicked();
    void babeIt_action();
    void artIt_action();
    void removeIt_action();

protected:

    virtual void mousePressEvent (QMouseEvent * event) Q_DECL_OVERRIDE;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual bool eventFilter(QObject * watched, QEvent * event) Q_DECL_OVERRIDE;



    // virtual void  mouseMoveEvent(QMouseEvent *evt);
};

#endif // ALBUM_H
