#include "PixelGenerate.h"

PixelGenerate::PixelGenerate(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.LColor->setStyleSheet("background-color:rgb(255,0,0);");
	ui.RColor->setStyleSheet("background-color:rgb(0,0,0);");
	connect(ui.width_box, SIGNAL(valueChanged(int)), this, SLOT(ChangeWidth(int)));
	connect(ui.height_box, SIGNAL(valueChanged(int)), this, SLOT(ChangeHeight(int)));
	connect(ui.step_box, SIGNAL(valueChanged(int)), this, SLOT(ChangeStep(int)));
	connect(ui.CurImage, SIGNAL(valueChanged(int)), this, SLOT(ChangeCurImage(int)));
	connect(ui.ClearColor, SIGNAL(clicked()), this, SLOT(DoClear()));
	connect(ui.LColor, SIGNAL(clicked()), this, SLOT(ChangeLeft()));
	connect(ui.RColor, SIGNAL(clicked()), this, SLOT(ChangeRight()));
	connect(ui.LoadImage, SIGNAL(clicked()), this, SLOT(LoadLocalIamge()));
	connect(ui.SaveAsFile, SIGNAL(clicked()), this, SLOT(SaveMap()));
}



void PixelGenerate::ChangeWidth(int width)
{
	if (width > 0) {
		ui.pixmap->SetWidth(width);
		ui.pixmap->ResizeMap();
	}
    
	auto a = ui.pixmap->GetHeight();
	auto b = ui.pixmap->GetWidth();
	auto c = ui.pixmap->GetStep();
}

void PixelGenerate::ChangeHeight(int height)
{
	if (height > 0)
	{
		ui.pixmap->SetHeight(height);
		ui.pixmap->ResizeMap();
	}
	
	auto a = ui.pixmap->GetHeight();
	auto b = ui.pixmap->GetWidth();
	auto c = ui.pixmap->GetStep();
}

void PixelGenerate::ChangeStep(int step)
{
	if (step > 1)
	{
		ui.pixmap->SetStep(step);
		ui.pixmap->ResizeMap();
	}

	auto a = ui.pixmap->GetHeight();
	auto b = ui.pixmap->GetWidth();
	auto c = ui.pixmap->GetStep();
}

void PixelGenerate::DoClear() {
	ui.pixmap->ClearAllColor();
}

void PixelGenerate::ChangeLeft() {
	QColor getcolor = QColorDialog::getColor(Qt::red);
	if (getcolor.isValid()) {
		auto R = getcolor.red();
		auto G = getcolor.green();
		auto B = getcolor.blue();

		QString rgb = QString::number(R) + "," + QString::number(G) + "," + QString::number(B);
		ui.LColor->setStyleSheet("background-color:rgb(" + rgb + ");");
		 
		ui.pixmap->SetLeftColor(getcolor);
	}
	
}
void PixelGenerate::ChangeRight() {
	QColor color = QColorDialog::getColor(Qt::white);
	if (color.isValid()) {
		auto R = color.red();
		auto G = color.green();
		auto B = color.blue();

		QString rgb = QString::number(R) + "," + QString::number(G) + "," + QString::number(B);
		ui.RColor->setStyleSheet("background-color:rgb(" + rgb + ");");
		ui.pixmap->SetRightColor(color);
	}
}


void PixelGenerate::LoadLocalIamge() {
	QString filePath = QFileDialog::getOpenFileName(this, tr("choose image"), "", tr("Image Files(*.jpg *.png *.bmp *.pgm *.pbm *.gif);;All(*.*)"));
	if (filePath != nullptr) {
		QStringList list = filePath.split(".");
		QString suffix = list[list.size() - 1].toLower();
		if (suffix == "gif")
		{
			ImageFormat = "GIF";
			QMovie movie(filePath);
			int frameCount = movie.frameCount();
			movie.jumpToFrame(0);
			QPixmap pixmap = movie.currentPixmap();
			QImage image = pixmap.toImage();
			int width = ui.pixmap->GetWidth() < image.width() ? ui.pixmap->GetWidth() : image.width();
			int height = ui.pixmap->GetHeight() < image.height() ? ui.pixmap->GetHeight() : image.height();

			queue = PixelMatrixQueue{ frameCount ,PixelMatrix{ width, QVector<QColor>(height, Qt::black) } };
			for (int i = 0; i < frameCount; ++i)
			{
				movie.jumpToFrame(i);
				QPixmap pixmap = movie.currentPixmap();
				QImage image = pixmap.toImage();
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						queue[i][x][y] = image.pixelColor(x, y);
					}
				}
			}
			preIndex = 0;
			ui.pixmap->LoadColorMap(queue[0]);
			ui.CurImage->setMaximum(frameCount - 1);
			ui.CurImage->setValue(0);
			ui.SumImage->setText(QString("Total:") + QString::number(frameCount));
		}
		else {
			ImageFormat = "JPG";
			QPixmap pixmap(filePath);
			QImage image = pixmap.toImage();
			int width = ui.pixmap->GetWidth() < image.width() ? ui.pixmap->GetWidth(): image.width();
			int height = ui.pixmap->GetHeight() < image.height() ? ui.pixmap->GetHeight() : image.height();

			PixelMatrix map{ width, QVector<QColor>(height, Qt::black) };
			{
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						map[x][y] = image.pixelColor(x, y);
					}
				}
			}
			ui.pixmap->LoadColorMap(map);
		}
	}
	
}


void PixelGenerate::ChangeCurImage(int index) {
	//读取画布信息
	preIndex = nextIndex;
	nextIndex = index;
	auto getmap = ui.pixmap->GetMap();
	for (int y = 0; y < queue[0][0].size(); y++) {
		for (int x = 0; x < queue[0].size(); x++) {
			queue[preIndex][x][y] = getmap[x][y];
		}
	}
	//让画布显示下一个
	ui.pixmap->LoadColorMap(queue[nextIndex]);
}


void PixelGenerate::SaveMap() {
	//图片信息收集

}