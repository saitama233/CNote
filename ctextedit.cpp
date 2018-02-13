#include "ctextedit.h"

CTextEdit::CTextEdit(QWidget* parent)
    :QTextEdit(parent)
{

}

bool CTextEdit::canInsertFromMimeData(const QMimeData *source)
{
    return QTextEdit::canInsertFromMimeData(source) || source->hasImage();
}

void CTextEdit::insertFromMimeData(const QMimeData *source)
{
    //我测试的时候hasUrl()需要在hasImage()后，不然无法执行hasImage(),因为图片也包含url
    if (source->hasImage()) {
        foreach (QUrl url, source->urls()) {
            insertImage(url, source);
        }
        qDebug() << "There is a image：" << source->urls();
    } else if (source->hasUrls()) {
        foreach (QUrl url, source->urls()) {
            QFileInfo fileinfo(url.toString());
            if (QImageReader::supportedImageFormats().contains(fileinfo.suffix().toLower().toLatin1())) {
                qDebug() << "There is a imagefile：" << source->urls();
                insertImage(url, source);
            } else {
                qDebug() << "There is a file：" << source->urls();
                insertFile();
            }
        }
    } else {
        qDebug() << "QTextEdit::insertFromMimeData(source)";
        QTextEdit::insertFromMimeData(source);
    }
}

void CTextEdit::insertImage(const QUrl &url, const QMimeData *source)
{
    this->document()->addResource(QTextDocument::ImageResource, url, source->imageData());
    QTextImageFormat imageformat;
    imageformat.setName(url.toString());
    this->textCursor().insertImage(imageformat);
}

void CTextEdit::insertFile()
{

}
