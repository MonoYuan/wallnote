#ifndef WALLNOTE_H
#define WALLNOTE_H

#include <QWidget>
#include <settingobject.h>
#include <QLabel>
#include <QTextBrowser>
#include <settingwidget.h>
#include <QGraphicsDropShadowEffect>

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
    QGraphicsDropShadowEffect* effect;
    void initTextWindow();
    void setTextWindow();
    void setQLabel();
    void initSystemIcon();
    SettingWidget* settingWidget;
    SettingObject settingObj;

    //设置Widget

    void changeSettingsAndSave();

    //数据保存到本地的路径
    QString filePath;
    //从本地读取数据
    void readSettingFromDisk();
    //数据写入本地
    void saveSettingToDisk();
    void paintEvent(QPaintEvent* event)override;
};
#endif // WALLNOTE_H
