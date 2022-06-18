#include "wallnote.h"
#include <qt_windows.h>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <fstream>
/**
 * 1. 应用启动时从文件系统拿到当前配置,并通过这个配置展示文本
 * 2. 点击设置时, 将当前配置设置给SettingWidget并反显
 * 3. 点击应用时, 将设置的配置保存到本地,并应用到展示文本中
 * Wallnote App的作用:
 *      1. 展示壁纸
 *      2. 从本地获取配置
 *      3. 展示文本框
 *      4. 将配置保存到本地
 *      5. 打开设置Widget
 *      6. 将配置设置给 设置Widget 并反显
 */

Wallnote::Wallnote(QWidget *parent)
    : QWidget(parent)
    ,bkLabel(new QLabel(this))
{
    //展示壁纸
    showWallpaper();
    //初始配置存储统路径
    QString appPath = QApplication::applicationDirPath();
    filePath = appPath + "/data.dat";
    //从磁盘读取配置,并将其指针设置给SettingObj属性
    readSettingFromDisk();
    //初始化文本背景并展示
    initTextWindow();
    //展示系统托盘图标
    initSystemIcon();
}

Wallnote::~Wallnote()
{
}

void Wallnote::showWallpaper(){
    //展示桌面壁纸
    HWND desktop = FindWindowEx(NULL,NULL,L"Progman",NULL);
    bkLabel->setPixmap(QPixmap(":/images/images/2.jpg"));
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setWindowState(Qt::WindowMaximized);
    showFullScreen();
    //有时候图片显示在桌面上了,但是桌面上的图标看不到了, 这段代码就是让桌面的图标显示
    PDWORD_PTR result = nullptr;
    HWND hWorkerW = nullptr;
    HWND hDefView = nullptr;
    SendMessageTimeout(FindWindow(L"Progman",NULL), 0x52c, 0, 0, SMTO_NORMAL, 1000, result);
    hWorkerW = FindWindowEx(NULL, NULL, L"WorkerW", NULL);
    while ((!hDefView) && hWorkerW) {
        hDefView = FindWindowEx(hWorkerW, NULL, L"SHELLDLL_DefView", NULL);
        hWorkerW = FindWindowEx(NULL, hWorkerW, L"WorkerW", NULL);
    }

    ShowWindow(hWorkerW,0);
    if(desktop){
        SetParent((HWND)this->winId(),desktop);
    }
}
void Wallnote::readSettingFromDisk(){
    std::ifstream ifs(filePath.toStdString(),std::ios::in|std::ios::binary);
    if(!ifs.is_open()){
        qDebug() << "open file " << filePath << " failed\n";
    }else{
        ifs >> this->settingObj.fontSize;
        ifs >> this->settingObj.fontColor;
        ifs >> this->settingObj.fontFamily;
        ifs >> this->settingObj.textContext;
        ifs.close();
        qDebug() << "read file from " << filePath << "success!";
        qDebug() << "read file complete!";
    }
}
void Wallnote::initTextWindow(){
    this->textBrowser = new QTextBrowser(this);
    this->setTextWindow();
    this->textBrowser->show();
}
void Wallnote::setTextWindow(){
    //设置透明背景
    textBrowser->setAttribute(Qt::WA_TranslucentBackground);
    //设置位置
    textBrowser->setGeometry(400,20,950,950);
    //设置文本内容
    textBrowser->setText(QString::fromStdString(settingObj.textContext));
    //组装并设置样式
    QString styleStr = "background-color:rgba(0,0,0,100);border:0;";
    styleStr.append(QString("color:%1;").arg(QString::fromStdString(settingObj.fontColor)));
    styleStr.append(QString("font-family:%1;").arg(QString::fromStdString(settingObj.fontFamily)));
    styleStr.append(QString("font-size:%1px;").arg(QString::fromStdString(settingObj.fontSize)));
    textBrowser->setStyleSheet(styleStr);
}
void Wallnote::initSystemIcon(){
    QSystemTrayIcon* tray = new QSystemTrayIcon;
    tray->setIcon(QIcon(":/images/images/icon.png"));
    QMenu* menu = new QMenu;
    QAction* close = new QAction(QString("关闭"));
    QAction* setting = new QAction(QString("设置"));

    menu->addAction(close);
    menu->addAction(setting);

    tray->setContextMenu(menu);
    tray->show();

    connect(setting,&QAction::triggered,this,&Wallnote::showSettingWidget);

}

void Wallnote::showSettingWidget(){
    settingWidget = new SettingWidget();
    settingWidget->settingObj = &settingObj;
    settingWidget->loadCurValue();
    settingWidget->show();
    //这里需要SettingWidget中传入SettingObject的指针, 让changeText接收到并获取到对应的值,并改变主窗口的文件显示
    connect(settingWidget,&SettingWidget::signalToChangeText,this,&Wallnote::changeTextAndSave);
}
void Wallnote::changeTextAndSave(){
    setTextWindow();
    saveSettingToDisk();
}
void Wallnote::saveSettingToDisk(){

    SettingObject obj;
    obj.fontColor = this->settingObj.fontColor;
    obj.fontSize = this->settingObj.fontSize;
    obj.fontFamily = this->settingObj.fontFamily;
    obj.textContext = this->settingObj.textContext;
    qDebug() << "prepare save file to data.dat";
    std::ofstream ofs(filePath.toStdString(),std::ios::out|std::ios::trunc);
    ofs << this->settingObj.fontSize;
    ofs << this->settingObj.fontColor;
    ofs << this->settingObj.fontFamily;
    ofs << this->settingObj.textContext;

    ofs.close();
    qDebug() << "setting save to " << filePath << "success!";
}
