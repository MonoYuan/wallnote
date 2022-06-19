#ifndef SETTINGOBJECT_H
#define SETTINGOBJECT_H
#include<QString>
#include<QApplication>
class SettingObject
{
public:
    SettingObject();
    QString textContext = "有问题请联系我,邮箱: 1225210052@qq.com";
    QString fontFamily = "SimSun";
    QString fontColor = "red";
    int fontSize = 40;
    int horizontal = 300;
    int vertical = 20;
    int width = 900;
    int height = 800;
    QString wallpaperPath = ":/images/images/2.jpg";
};

#endif // SETTINGOBJECT_H
