#include "Pixmap.h"

Pixmap::Pixmap(QWidget* parent)
	: QWidget(parent)
{
}

void Pixmap::SetStep(int step)
{
	m_step = step;
}

void Pixmap::SetWidth(int width)
{
	m_width = width;
	SetSize();
}

void Pixmap::SetHeight(int heigth)
{
	m_height = heigth;
	SetSize();
}

void Pixmap::SetSize()
{
	PixelMatrix temp{ std::move(map) };
	map = PixelMatrix(GetWidth(), QVector<QColor>(GetHeight()));

	for (int i = 0; i < temp.length() && i < GetWidth(); ++i)
	{
		for (int j = 0; j < temp[i].length() && j < GetHeight(); ++j)
		{
			map[i][j] = temp[i][j];
		}
	}
}

void Pixmap::DrawMap()
{
	update();
}

void Pixmap::ResizeMap()
{
	DrawMap();
}

int Pixmap::GetWidth() const
{
	return m_width;
}

int Pixmap::GetHeight() const
{
	return m_height;
}

int Pixmap::GetStep() const
{
	return m_step;
}

int Pixmap::NumToPixel(int num)
{

	return num * GetStep();
}

QPoint Pixmap::PixelToNum(QPoint mouse)
{
	auto x = mouse.x() / GetStep();
	auto y = mouse.y() / GetStep();
	return QPoint(x, y);
}

void Pixmap::SetLeftColor(QColor c)
{
	LeftColor = c;
}

void Pixmap::SetRightColor(QColor c)
{
	RightColor = c;
}

void Pixmap::ClearAllColor()
{
	for (int i = 0; i < map.length() && i < GetWidth(); ++i)
	{
		for (int j = 0; j < map[i].length(); ++j)
		{
			map[i][j] = BackColor;
		}
	}
	update();
}

void Pixmap::LoadColorMap(PixelMatrix e)
{
	for (int i = 0; i < e.length() && i < GetWidth(); ++i)
	{
		for (int j = 0; j < e[i].length(); ++j)
		{
			map[i][j] = e[i][j];
		}
	}
	update();
}

PixelMatrix Pixmap::GetMap() const
{
	return map;
}


void Pixmap::mousePressEvent(QMouseEvent* event)
{
	m_isMouseDown = true;
	m_isLButtonDown = event->button() == Qt::LeftButton;
	auto mousepos = PixelToNum(event->pos());
	if (mousepos.x() >= 0 && mousepos.x() < GetWidth() && mousepos.y() >= 0 && mousepos.y() < GetHeight())
	{
		if (m_isLButtonDown)
		{
			map[mousepos.x()][mousepos.y()] = LeftColor;
		}
		else
		{
			map[mousepos.x()][mousepos.y()] = RightColor;
		}
		update();
	}

}

void Pixmap::mouseMoveEvent(QMouseEvent* event)
{
	auto mousepos = PixelToNum(event->pos());
	if (mousepos.x() >= 0 && mousepos.x() < GetWidth() && mousepos.y() >= 0 && mousepos.y() < GetHeight())
	{
		if (m_isMouseDown)
		{
			if (m_isLButtonDown)
			{
				map[mousepos.x()][mousepos.y()] = LeftColor;
			}
			else
			{
				map[mousepos.x()][mousepos.y()] = RightColor;
			}
			update();
		}
		else
		{
			return QWidget::mouseMoveEvent(event);
		}
	}
	
}

void Pixmap::mouseReleaseEvent(QMouseEvent* event)
{
	m_isMouseDown = false;
	m_isLButtonDown = false;
}


void Pixmap::paintEvent(QPaintEvent*)
{
	QPainter painter{ this };

	painter.setPen(QPen(Qt::transparent));
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetHeight(); j++)
		{
			painter.setBrush(QBrush(map[i][j], Qt::SolidPattern));
			painter.drawRect(i * GetStep(), j * GetStep(), GetStep(), GetStep());
		}
	}

	painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
	for (int i = 0; i <= GetWidth(); i += 1)
	{
		painter.drawLine(QPoint(NumToPixel(i), 0), QPoint(NumToPixel(i), NumToPixel(GetHeight())));
	}
	for (int i = 0; i <= GetHeight(); i += 1)
	{
		painter.drawLine(QPoint(0, NumToPixel(i)), QPoint(NumToPixel(GetWidth()), NumToPixel(i)));
	}

}
