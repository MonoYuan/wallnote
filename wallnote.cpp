#include "wallnote.h"
#include <qt_windows.h>
#include <QPixmap>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QSize>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>

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

Wallnote::Wallnote(bool isMain,int screenNumber,Wallnote* parentWallnote,QWidget *parent) : QWidget(parent) ,bkLabel(new QLabel(this))
{
    //初始配置存储统路径
    this->screenNumber = screenNumber;
    QString appPath = QApplication::applicationDirPath();
    filePath = appPath + "/data"+QString::number(screenNumber)+".dat";
    //从磁盘读取配置,并将其指针设置给SettingObj属性
    readSettingFromDisk();
    //展示壁纸
    showWallpaper();
    //初始化文本背景并展示
    initTextWindow();
    QList<QScreen *> listScreen = QGuiApplication::screens();
    /*
    两种情况:
        1: 软件运行状态下, 接入外接显示器并设置为扩展   读取是否有第二配置, 有的话加载
        2: 软件运行状态下, 点击设置, 在设置中显示多显示器配置 ---已完成
        3: 软件启动时, 如果有外接显示器, 则检测副屏配置并显示
    */
    if(isMain){
        for(int i=0;i<MAX_SCREEN_NUM;i++){
            wallnoteStateArr[i] = 0;
        }
        this->screenNumber = 0;
        //展示系统托盘图标
        initSystemIcon();
        this->setGeometry(listScreen.at(0)->geometry());
        this->wallnoteArr[0] = this;
        wallnoteStateArr[0] = 1;
        QTimer* timer = new QTimer(this);
        timer->callOnTimeout(this,&Wallnote::screenChangeListening);
        timer->start(10000);
    }else{
        qDebug("new Wallnote for the other screen is initialized!!!");
        this->setGeometry(listScreen.at(screenNumber)->geometry());
    }

}

Wallnote::~Wallnote()
{
    delete this->textBrowser;
}

void Wallnote::showWallpaper(){
    //展示桌面壁纸
    //壁纸需要嵌入SHELLDLL_Defview窗口上
    //windows默认桌面主窗口是Progman窗口
    //win10包含两个WorkerW窗口,是桌面过渡动画窗口
    //原没有WorkerW窗口时,SHELLDLL_DefView是嵌在Progman窗口上的,现在是嵌入其中一个WorkerW上
    HWND desktop = FindWindowEx(NULL,NULL,L"Progman",NULL);
    setQLabel();
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
    qDebug() << "preparing read file, filePath: " << filePath;
    QFile file(filePath);
    if(file.open(QFile::ReadOnly | QFile::Truncate)){
        QTextStream out(&file);
        this->settingObj.fontColor = out.readLine();
        this->settingObj.fontFamily = out.readLine();
        this->settingObj.fontSize = out.readLine().toInt();
        this->settingObj.horizontal = out.readLine().toInt();
        this->settingObj.vertical = out.readLine().toInt();
        this->settingObj.width = out.readLine().toInt();
        this->settingObj.height = out.readLine().toInt();
        this->settingObj.wallpaperPath = out.readLine();

        this->settingObj.shadowHorizontal = out.readLine().toInt();
        this->settingObj.shadowVertical = out.readLine().toInt();
        this->settingObj.shadowBlur = out.readLine().toInt();
        this->settingObj.shadowColor = out.readLine();

        this->settingObj.textContext = QString("").append(out.readLine());
        while(!out.atEnd()){
            settingObj.textContext.append("\n").append(out.readLine());
        }
        file.close();
    }
}
void Wallnote::loadDataForWallnote(int screenNumber){
    if(wallnoteStateArr[screenNumber]==1){
        wallnoteArr[screenNumber]->readSettingFromDisk();
        this->settingWidget->settingObj = &wallnoteArr[screenNumber]->settingObj;
    }else{
        this->settingWidget->settingObj = nullptr;
    }
}
void Wallnote::initTextWindow(){
    this->textBrowser = new QTextBrowser(this);
    this->effect = new QGraphicsDropShadowEffect(this->textBrowser);
    //this->effect->setColor();
    this->setTextWindow();
    this->textBrowser->show();
}
void Wallnote::setQLabel(){
    this->bkLabel->setPixmap(QPixmap(settingObj.wallpaperPath));
    this->bkLabel->setScaledContents(true);
}
void Wallnote::setTextWindow(){
    //设置透明背景
    textBrowser->setAttribute(Qt::WA_TranslucentBackground);
    //设置位置
    textBrowser->setGeometry(settingObj.horizontal,settingObj.vertical,settingObj.width,settingObj.height);
    //设置文本内容
    textBrowser->setText(settingObj.textContext);
    //组装并设置样式
    QString styleStr = "background-color:rgba(0,0,0,100);border:0;";
    styleStr.append(QString("color:%1;").arg(settingObj.fontColor));
    styleStr.append(QString("font-family:%1;").arg(settingObj.fontFamily));
    styleStr.append(QString("font-size:%1px;").arg(settingObj.fontSize));
    textBrowser->setStyleSheet(styleStr);
    //设置文字阴影
    effect->setOffset(settingObj.shadowHorizontal,settingObj.shadowVertical);
    effect->setColor(QColor(settingObj.shadowColor));
    effect->setBlurRadius(settingObj.shadowBlur);
    textBrowser->setGraphicsEffect(effect);
}
void Wallnote::initSystemIcon(){
    QSystemTrayIcon* tray = new QSystemTrayIcon;
    tray->setIcon(QIcon(":/icon.ico"));
    QMenu* menu = new QMenu;
    QAction* close = new QAction(QString("关闭"));
    QAction* setting = new QAction(QString("设置"));

    menu->addAction(close);
    menu->addAction(setting);

    tray->setContextMenu(menu);
    tray->show();

    connect(setting,&QAction::triggered,this,[=](){
        qDebug() << "in setting page";
        settingWidget = new SettingWidget();
        //关闭设置窗口后回收其内存, 因为其没有挂载到主Widget上
        connect(settingWidget,&SettingWidget::exitSettingWidget,this,[=](){
            delete this->settingWidget;
        });
        settingWidget->settingObj = &settingObj;
        settingWidget->loadCurValue(screenNumber);
        settingWidget->show();
        //这里需要SettingWidget中传入SettingObject的指针, 让changeText接收到并获取到对应的值,并改变主窗口的文件显示
        connect(settingWidget,&SettingWidget::signalToChangeSettings,this,&Wallnote::changeSettingsAndSave);
        connect(settingWidget,&SettingWidget::signalToChangeSettingObj,this,&Wallnote::loadDataForWallnote);
    });
    connect(close,&QAction::triggered,this,[=](){
        QApplication::quit();
    });
}
void Wallnote::changeSettingsAndSave(int screenNumber){
    //展示指定的窗口,保存指定的配置
    //如果是接入副屏后第一次设置,则需要新建一个Wallnote对象
    //对于多的副屏对象(之前建立后由于外接显示器断开导致)则在定时任务中清除多余的对象
    if(screenNumber>9){
        QMessageBox::warning(this,"最大支持"+QString::number(MAX_SCREEN_NUM)+"个屏幕显示","warning");
        return;
    }
    Wallnote* currentNote = this->wallnoteArr[screenNumber];
    if(currentNote==nullptr){
        currentNote = new Wallnote(false,screenNumber,this);
        this->wallnoteStateArr[screenNumber] = 1;
        this->wallnoteArr[screenNumber] = currentNote;
    }
    currentNote->setTextWindow();
    currentNote->setQLabel();
    currentNote->saveSettingToDisk();
}
/**
 * 按行存储配置数据
 */
void Wallnote::saveSettingToDisk(){
    QFile file(filePath);
    if(file.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream out(&file);
        out << this->settingObj.fontColor << "\n";
        out << this->settingObj.fontFamily << "\n";
        out << this->settingObj.fontSize << "\n";
        out << this->settingObj.horizontal << "\n";
        out << this->settingObj.vertical << "\n";
        out << this->settingObj.width << "\n";
        out << this->settingObj.height << "\n";
        out << this->settingObj.wallpaperPath << "\n";

        out << this->settingObj.shadowHorizontal << "\n";
        out << this->settingObj.shadowVertical << "\n";
        out << this->settingObj.shadowBlur << "\n";
        out << this->settingObj.shadowColor << "\n";

        out << this->settingObj.textContext;
        file.close();
    }
}

void Wallnote::paintEvent(QPaintEvent* event){
    this->bkLabel->resize(this->size());
}
void Wallnote::screenChangeListening(){
    QList<QScreen *> list = QGuiApplication::screens();
    int maxNum = list.size()>this->MAX_SCREEN_NUM?MAX_SCREEN_NUM:list.size();
    for(int i=0;i<maxNum;i++){
        if(wallnoteStateArr[i]==0){
            QString configFilePath = QApplication::applicationDirPath()+"/data"+QString::number(screenNumber)+".dat";
            QFile f(configFilePath);
            if(f.exists()){
                wallnoteArr[i] = new Wallnote(false,i,this);
                wallnoteStateArr[i] = 1;
                wallnoteArr[i]->show();
            }
        }
    }

}

