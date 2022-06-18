#ifndef SETTINGOBJECT_H
#define SETTINGOBJECT_H
//#include<QString>
#include <string>
class SettingObject
{
public:
    SettingObject();
//    QString textContext = "有问题请联系我,邮箱: 13074003055@163.com";
//    QString fontFamily = "SimSun";
//    QString fontSize = "40";
//    QString fontColor = "red";

    std::string textContext = "有问题请联系我,邮箱: 13074003055@163.com";
    std::string fontFamily = "SimSun";
    std::string fontSize = "40";
    std::string fontColor = "red";
};

#endif // SETTINGOBJECT_H
