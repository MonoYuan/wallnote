#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QApplication>
#include <QDebug>

SettingWidget::SettingWidget(QWidget *parent) : QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}
void SettingWidget::loadCurValue(int currentNum){
    if(this->settingObj==nullptr){
        return;
    }
    QList<QScreen *> list = QGuiApplication::screens();
    ui->screenSelect->blockSignals(true);
    ui->screenSelect->clear();
    for(int i=0;i<list.size();i++){
        ui->screenSelect->addItem("屏幕"+QString::number(i));
    }

    ui->screenSelect->setCurrentIndex(currentNum);
    ui->screenSelect->blockSignals(false);
    ui->fontColor->setText(settingObj->fontColor);
    ui->fontFamily->setCurrentFont(QFont(settingObj->fontFamily));
    ui->textContext->setText(settingObj->textContext);
    ui->fontSize->setValue(settingObj->fontSize);
    ui->horizontal->setValue(settingObj->horizontal);
    ui->vertical->setValue(settingObj->vertical);
    ui->width->setValue(settingObj->width);
    ui->height->setValue(settingObj->height);
    ui->wallpaperText->setText(settingObj->wallpaperPath);

    ui->shadowHorizontal->setValue(settingObj->shadowHorizontal);
    ui->shadowVertical->setValue(settingObj->shadowVertical);
    ui->shadowBlur->setValue(settingObj->shadowBlur);
    ui->shadowColorText->setText(settingObj->shadowColor);
}

void SettingWidget::settingApply(){
    if(this->settingObj==nullptr){
        this->settingObj = new SettingObject();
    }
    this->settingObj->textContext = ui->textContext->toPlainText();
    this->settingObj->fontColor = ui->fontColor->text();
    this->settingObj->fontFamily = ui->fontFamily->currentFont().family();
    this->settingObj->fontSize = ui->fontSize->value();
    this->settingObj->horizontal = ui->horizontal->value();
    this->settingObj->vertical = ui->vertical->value();
    this->settingObj->width = ui->width->value();
    this->settingObj->height = ui->height->value();
    this->settingObj->wallpaperPath = ui->wallpaperText->text();

    this->settingObj->shadowHorizontal = ui->shadowHorizontal->value();
    this->settingObj->shadowVertical = ui->shadowVertical->value();
    this->settingObj->shadowBlur = ui->shadowBlur->value();
    this->settingObj->shadowColor = ui->shadowColorText->text();
}

void SettingWidget::on_pushButton_clicked()
{
    //点击应用时,如果没有对应的Wallnote,应该创建
    emit signalToChangeSettingObj(ui->screenSelect->currentIndex());
    settingApply();
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}


void SettingWidget::on_colorSelect_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red,this,tr("颜色选择"),QColorDialog::ShowAlphaChannel);
    QString rgb = QString("#%1%2%3")
            .arg(color.red(),2,16,QChar('0'))
            .arg(color.green(),2,16,QChar('0'))
            .arg(color.blue(),2,16,QChar('0'));
    settingObj->fontColor = rgb;
    ui->fontColor->setText(rgb);
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_fontSize_valueChanged(int sizeVal)
{
    settingObj->fontSize = sizeVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_horizontal_valueChanged(int horizontalVal)
{
    settingObj->horizontal = horizontalVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_vertical_valueChanged(int verticalVal)
{
    settingObj->vertical = verticalVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_width_valueChanged(int widthVal)
{
    settingObj->width = widthVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}


void SettingWidget::on_heigth_valueChanged(int heightVal)
{
    settingObj->height = heightVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_wallpaperBtn_clicked()
{
    QString wallpaperFilePath = QFileDialog::getOpenFileName(this,"选择一个图片",
                                ui->wallpaperText->text().isEmpty()?QApplication::applicationDirPath():ui->wallpaperText->text(),
                                "IMAGE(*.jpg *.png);;GIF(*.gif)");
    if(!wallpaperFilePath.isEmpty()){
        settingObj->wallpaperPath = wallpaperFilePath;
        ui->wallpaperText->setText(wallpaperFilePath);
        emit signalToChangeSettings(ui->screenSelect->currentIndex());
    }
}
void SettingWidget::closeEvent(QCloseEvent * event){
    emit exitSettingWidget();
}

void SettingWidget::on_shadowHorizontal_valueChanged(int shadowHorizontalVal)
{
    settingObj->shadowHorizontal = shadowHorizontalVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}


void SettingWidget::on_shadowVertical_valueChanged(int shadowVerticalVal)
{
    settingObj->shadowVertical = shadowVerticalVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}


void SettingWidget::on_shadowBlur_valueChanged(int shadowBlurVal)
{
    settingObj->shadowBlur = shadowBlurVal;
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}


void SettingWidget::on_shadowColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,tr("颜色选择"),QColorDialog::ShowAlphaChannel);
    QString rgb = QString("#%1%2%3")
            .arg(color.red(),2,16,QChar('0'))
            .arg(color.green(),2,16,QChar('0'))
            .arg(color.blue(),2,16,QChar('0'));
    qDebug() << "shadow color selected: " << rgb;
    settingObj->shadowColor = rgb;
    ui->shadowColorText->setText(rgb);
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_resetWallnotePath_clicked()
{
    SettingObject so;
    settingObj->wallpaperPath = so.wallpaperPath;
    ui->wallpaperText->setText(so.wallpaperPath);
    emit signalToChangeSettings(ui->screenSelect->currentIndex());
}

void SettingWidget::on_screenSelect_currentIndexChanged(int index)
{
    //1. 重新读取配置,并设置到当前对象SettingWidget的SettingObj中
    emit signalToChangeSettingObj(index);
    //2. 将当前类中的SettingObj反显到SettingWidget面板上
    loadCurValue(index);
}

