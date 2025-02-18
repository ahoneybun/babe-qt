#ifndef ALBUMSVIEW_H
#define ALBUMSVIEW_H

#include <QWidget>
#include <QSqlQuery>
#include <QGridLayout>
#include <QFrame>
#include <QListWidgetItem>
#include <QListWidget>
#include <QComboBox>
#include <QHeaderView>
#include <QToolTip>
#include <QDebug>
#include <QShortcut>
#include <QSplitter>

#include "scrolltext.h"
#include "album.h"
#include "babetable.h"
#include "collectionDB.h"

namespace Ui {
class AlbumsView;
}

class AlbumsView : public QWidget
{
    Q_OBJECT

public:

    explicit AlbumsView(bool extraList=false, QWidget *parent = 0);
    ~AlbumsView();
    void populateTableView(QSqlQuery query);
    void populateTableViewHeads(QSqlQuery query);
    void populateExtraList(QSqlQuery query);
    void flushGrid();
    int getAlbumSize() { return this->albumSize; }
    QSlider *slider;
    QComboBox *order;
    QFrame *utilsFrame;
    BabeTable *albumTable;
    QListWidget *grid;


    enum ALBUMSVIEW_H{ TITLE, ARTIST, ART };

private:

    int ALBUM_SIZE_BIG = BaeUtils::getWidgetSizeHint(BaeUtils::BIG_ALBUM_FACTOR,BaeUtils::BIG_ALBUM);
    int ALBUM_SIZE_MEDIUM = BaeUtils::getWidgetSizeHint(BaeUtils::MEDIUM_ALBUM_FACTOR,BaeUtils::MEDIUM_ALBUM);

    int gridSize;
    int albumSize=BaeUtils::getWidgetSizeHint(BaeUtils::MEDIUM_ALBUM_FACTOR,BaeUtils::MEDIUM_ALBUM);
    bool extraList=false;
    QList<Album*> albumsList;
    QList<QListWidgetItem*> itemsList;
    QStringList albums;
    QStringList artists;
    QWidget *albumBox_frame;
    QFrame *line_h;
    Album *cover;
    CollectionDB connection;
    Playlist *playlist;
    QListWidget *artistList;
    QToolButton *closeBtn;

public slots:

    void hideAlbumFrame();
    void changedArt_cover(QMap<int,QString> info);
    void changedArt_head(QMap<int,QString> info);
    void babeAlbum(QMap<int,QString> info);
    void setAlbumsSize(int value);


private slots:

    void getAlbumInfo(QMap<int,QString> info);
    void getArtistInfo(QMap<int,QString> info);
    void albumHover();    
    void orderChanged(QString order);
    void filterAlbum(QModelIndex index);

signals:

    void albumDoubleClicked(QMap<int,QString> info);
    void albumOrderChanged(QString order);
    void playAlbum(QMap<int,QString> info);
    void babeAlbum_clicked( QMap<int,QString> info);
    void populateCoversFinished();
    void populateHeadsFinished();


};

#endif // ALBUMSVIEW_H
