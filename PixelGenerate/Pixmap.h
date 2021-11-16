#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QVector>

using PixelMatrix = QVector<QVector<QColor>>;
using PixelMatrixQueue = QVector<PixelMatrix>;
class Pixmap : public QWidget
{
	Q_OBJECT

public:

	Pixmap(QWidget *parent);
	//ˢ�»���
	void DrawMap();
	void ResizeMap();
	//��ȡ������������
	int GetWidth() const;
	int GetHeight() const;
	int GetStep() const;
	//��ֵת��
	int NumToPixel(int num);
	QPoint PixelToNum(QPoint mouse);
	//��������
	void SetStep(int step);
	void SetWidth(int width);
	void SetHeight(int heigth);
	void SetLeftColor(QColor);
	void SetRightColor(QColor);

	//��������
	void ClearAllColor();
	void LoadColorMap(PixelMatrix);
	PixelMatrix GetMap() const;




	~Pixmap() = default;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent*) override;

	bool m_isMouseDown{ false };
	bool m_isLButtonDown{ false };
private:

	//������ʼ����
	int m_width = 32;
	int m_height = 8;
	int m_step = 20;

	//��ʼ��ɫ
	QColor GridColor = Qt::gray;
	QColor BackColor = Qt::black;
	QColor LeftColor = Qt::red;
	QColor RightColor = BackColor;

	//����
	PixelMatrix map{ m_width, QVector<QColor>(m_height, BackColor) };


public slots:

	void SetSize();
};
