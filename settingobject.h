#ifndef SETTINGOBJECT_H
#define SETTINGOBJECT_H
#include<QString>
#include<QApplication>
class SettingObject
{
public:
    SettingObject();
    QString textContext = "如果有任何好的建议,请联系我!邮箱: 1225210052@qq.com,或者在github中留言:  "
                          "https://github.com/MonoYuan/wallnote     "
                          "if you have any ideas about this, just contact me with my email: 1225210052@qq.com    "
                          "or leave the message on github: https://github.com/MonoYuan/wallnote";
    QString fontFamily = "SimSun";
    QString fontColor = "red";
    int fontSize = 40;
    int horizontal = 300;
    int vertical = 20;
    int width = 900;
    int height = 800;
    QString wallpaperPath = ":/images/images/2.jpg";
    int shadowHorizontal = 0;
    int shadowVertical = 0;
    int shadowBlur = 3;
    QString shadowColor = "black";
};

#endif // SETTINGOBJECT_H
