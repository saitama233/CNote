#ifndef CTEXTEDIT_H
#define CTEXTEDIT_H

#include <QTextEdit>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QImageReader>

class CTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    CTextEdit(QWidget *parent);
protected:
    bool canInsertFromMimeData(const QMimeData *source);
    void insertFromMimeData(const QMimeData *source);
private:
    void insertImage(const QUrl &url, const QMimeData *source);
    void insertFile();

};

#endif // CTEXTEDIT_H
