#ifndef EPUBEXPORTSCRIBUSDOC_H
#define EPUBEXPORTSCRIBUSDOC_H

#include <QObject>
#include <QDebug>

class ScribusDoc;

class EpubExportScribusDoc : public QObject
{
    Q_OBJECT

public:
	EpubExportScribusDoc();
	~EpubExportScribusDoc();

    void add(ScribusDoc* doc) {this->doc << doc;}
private:
    QList<ScribusDoc*> doc;
};

QDebug operator<<(QDebug dbg, const EpubExportScribusDoc &scribusDoc);

#endif // EPUBEXPORTSCRIBUSDOC_H
