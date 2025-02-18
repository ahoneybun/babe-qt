#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QLabel>
#include <QMovie>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QGridLayout>
#include <fstream>
#include <iostream>

#include "notify.h"
#include "baeUtils.h"
#include "youtube.h"
#include "playlist.h"
#include "about.h"
#include "collectionDB.h"
#include "pulpo/pulpo.h"


namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:

    explicit settings(QWidget *parent = 0);
    ~settings();

    const QString settingPath= BaeUtils::SettingPath;
    const QString collectionDBPath=BaeUtils::CollectionDBPath;
    const QString cachePath=BaeUtils::CachePath;
    const QString youtubeCachePath=BaeUtils::YoutubeCachePath;
    const QString extensionFetchingPath=BaeUtils::ExtensionFetchingPath;
    const QStringList formats {"*.mp4","*.mp3","*.wav","*.flac","*.ogg","*.m4a"};
    bool checkCollection();
    void createCollectionDB();
    CollectionDB &getCollectionDB();

    int getToolbarIconSize()  {return iconSize;}
    void setToolbarIconSize(const int &iconSize);

    void setSettings(QStringList setting);
    void readSettings();
    void removeSettings(QStringList setting);
    void refreshCollectionPaths();
    void collectionWatcher();
    void addToWatcher(QStringList paths);
    QStringList getCollectionPath() {return collectionPaths;}
    CollectionDB collection_db;
    bool youtubeTrackDone=false;

    enum iconSizes
    {
        s16,s22,s24
    };
    //enum albums { ALBUM_TITLE, ARTIST, ART};
    // enum artists { ARTIST_TITLE, ART};

private slots:

    void on_open_clicked();
    void on_toolbarIconSize_activated(const QString &arg1);
    void finishedAddingTracks(bool state);
    void on_pushButton_clicked();
    void handleFileChanged(QString file);
    void handleDirectoryChanged(QString dir);
    void on_collectionPath_clicked(const QModelIndex &index);
    void on_remove_clicked();

    void on_debugBtn_clicked();

    void on_ytBtn_clicked();

    void on_fetchBtn_clicked();

    void on_checkBox_stateChanged(int arg1);

public slots:

    void populateDB(QString path);
    void fetchArt();
    void refreshWatchFiles();
    void youtubeTrackReady(bool state);
    void handleDirectoryChanged_cache(QString dir);
    void handleDirectoryChanged_extension();


private:
    Ui::settings *ui;


    const QString notifyDir= BaeUtils::NotifyDir;
    const QString collectionDBName = "collection.db";
    const QString settingsName = "settings.conf";

    Notify nof;
    YouTube *ytFetch;

    int iconSize = 16;
    QStringList collectionPaths={};
    QLabel *artFetcherNotice;
    QMovie *movie;
    QString pathToRemove;
    // QFileSystemWatcher watcher;
    //QThread* thread;
    About *about_ui;
    QStringList files;
    QStringList dirs;
    QFileSystemWatcher *watcher;
    QFileSystemWatcher *extensionWatcher;
    QTimer *cacheTimer;

signals:

    void toolbarIconSizeChanged(int newSize);
    void collectionPathChanged(QString newPath);
    void collectionDBFinishedAdding(bool state);
    void fileChanged(QString url);
    void dirChanged(QString url,QString babe="0");
    void collectionPathRemoved(QString url);
    void refreshTables();

};

#endif // SETTINGS_H
