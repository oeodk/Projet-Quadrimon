#include "widget/ResizableQLabel.h"
#include <QRegularExpression>

ResizableQLabel::ResizableQLabel(QWidget* parent)
    : QLabel(parent)
{
    has_image_ = false;
}

void ResizableQLabel::resizeEvent(QResizeEvent* event)
{
    resizeText();
    if(has_image_)
    {
        resizeImage();
    }
}

void ResizableQLabel::resizeText()
{
    QFont basefont = font();
    const QRect baseRect = contentsRect();
    const QString baseText = text();

    if (baseText.isEmpty()) {
        return;
    }

    // Split the text into lines
    QStringList lines = baseText.split(QRegularExpression("[\n]"), Qt::SkipEmptyParts);

    int fontSizeGuess = qMax(1, basefont.pixelSize());

    for (;; ++fontSizeGuess) {
        QFont testFont(basefont);
        testFont.setPixelSize(fontSizeGuess);

        // Calculate the height of all lines combined
        int totalHeight = 0;
        int max_width = 0;
        QFontMetrics fm(testFont);
        for (const QString& line : lines) {
            totalHeight += fm.boundingRect(line).height();
            if (fm.boundingRect(line).width() > max_width)
            {
                max_width = fm.boundingRect(line).width();
            }
        }

        if (totalHeight > baseRect.height() || max_width > baseRect.width()) {
            break;
        }
    }

    // Reduce font size until all lines fit within the label height
    for (; fontSizeGuess > 1; --fontSizeGuess) {
        QFont testFont(basefont);
        testFont.setPixelSize(fontSizeGuess);

        int totalHeight = 0;
        int max_width = 0;
        QFontMetrics fm(testFont);
        for (const QString& line : lines) {
            totalHeight += fm.boundingRect(line).height();
            if (fm.boundingRect(line).width() > max_width)
            {
                max_width = fm.boundingRect(line).width();
            }
        }

        if (totalHeight <= baseRect.height() && max_width <= baseRect.width())
        {
            break;
        }
    }

    basefont.setPixelSize(fontSizeGuess);
    setFont(basefont);
}

void ResizableQLabel::setImage(const std::string& path)
{
    QImage image;
    if (image.load(path.c_str()))
    {
        has_image_ = true;
        pixmap_ = QPixmap::fromImage(image);
        setPixmap(pixmap_.scaled(width(), height(), Qt::KeepAspectRatio));
        setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else
    {
        qDebug() << "Could not load image";
    }
}
