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

    const static int MAX_SCREEN_NUM = 10;

    Wallnote(bool isMain,int screenNumber,Wallnote* parentWallnote,QWidget *parent = nullptr);
    ~Wallnote();
    //一个数组, 用于存放主窗口(主显示器)和多个副窗口(外接显示器)地址, 这个参数对于副窗口的Wallnote类不生效
    //默认只能接入9个副屏, 每个窗口的设置由自己的settingObject控制, 大家共用主窗口的settingWidget
    //QList<Wallnote*> wallnoteList;
    Wallnote* wallnoteArr[MAX_SCREEN_NUM];
    int wallnoteStateArr[MAX_SCREEN_NUM];
    //当前的是第几个副屏
    int screenNumber;
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

    void changeSettingsAndSave(int screenNumber);

    //数据保存到本地的路径
    QString filePath;
    //从本地读取数据
    void readSettingFromDisk();
    //数据写入本地
    void saveSettingToDisk();
    void paintEvent(QPaintEvent* event)override;
    //外接显示器事件监听
    void screenChangeListening();
    void loadDataForWallnote(int screenNumber);
    void createConcreteWallnote(int screenNumber);
};
#endif // WALLNOTE_H
