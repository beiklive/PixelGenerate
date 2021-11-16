#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PixelGenerate.h"
#include<QPixmap>
#include <QPainter>
#include<QMouseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMovie>
#include <QVector>
#include <QColor>
#include <QString>
#include "Pixmap.h"
class PixelGenerate : public QMainWindow
{
    Q_OBJECT

public:

    PixelGenerate(QWidget *parent = Q_NULLPTR);

protected:

private:
	Ui::PixelGenerateClass ui;
	PixelMatrixQueue queue{ 1 ,PixelMatrix{ 1, QVector<QColor>(1, Qt::black) } };

public slots:
	void DoClear();
	void ChangeLeft();
	void ChangeRight();
	void ChangeWidth(int width);
	void ChangeHeight(int height);
	void ChangeStep(int step);
	void LoadLocalIamge();
	void ChangeCurImage(int);
};
