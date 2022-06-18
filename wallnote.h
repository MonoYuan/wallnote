#ifndef WALLNOTE_H
#define WALLNOTE_H

#include <QWidget>
#include <settingobject.h>
#include <QLabel>
#include <QTextBrowser>
#include <settingwidget.h>

class Wallnote : public QWidget
{
    Q_OBJECT

public:
    Wallnote(QWidget *parent = nullptr);
    ~Wallnote();
    //壁纸的展示之地
    QLabel* bkLabel;
    void showWallpaper();
    //文本的展示之地
    QTextBrowser* textBrowser;
    void initTextWindow();
    void setTextWindow();
    void initSystemIcon();
    void showSettingWidget();
    SettingWidget* settingWidget;
    SettingObject settingObj;

    //设置Widget

    void changeTextAndSave();

    //数据保存到本地的路径
    QString filePath;
    //从本地读取数据
    void readSettingFromDisk();
    //数据写入本地
    void saveSettingToDisk();
};
#endif // WALLNOTE_H
