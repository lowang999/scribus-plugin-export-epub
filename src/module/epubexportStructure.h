/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef EPUBEXPORTSTRUCTURE_H
#define EPUBEXPORTSTRUCTURE_H

#include <QObject>
#include <QDebug>

#include "scribusapi.h" // for SCRIBUS_API

#include "module/scribusAPIDocument.h"

/*
struct EpubExportStructureMetadata
{
    QString title;
     // Publications with multiple co-authors should provide multiple creator elements,
     // each containing one author. The order of creator elements is presumed
     // to define the order in which the creators' names should be presented by the Reading System.
     //
     // This specification recommends that the content of the creator elements hold the text
     // for a single name as it would be presented to the Reader.
     //
     // This specification adds to the creator element two optional attributes: role and file-as.
     // The set of values for role are identical to those defined in Section 2.2.6
     // for the contributor element. The file-as attribute should be used
     // to specify a normalized form of the contents, suitable for machine processing.
    QString author;
    QString subject; // multiple instances are allowed
    QString date;
	// <URN> ::= "urn:" <NID> ":" <NSS>
	// <dc:identifier id="bookid">urn:uuid:ba151a94-2581-dbd1-144a-3ae968f738c7</dc:identifier>
	// <dc:identifier id="BookId" opf:scheme="ISBN">123456789X</dc:identifier>
    // TODO: add scheme to settings (http://en.wikipedia.org/wiki/Uniform_resource_name)
    QString id;
    QString language;
    // it seems that keywords are treated as subjects in epub...
    // sould we separate the keywords by ","? (ale/20120912)
    QString keywords;
    QString description; // labelled as description in scribus
    QString publisher;
    QString contributor; // A party whose contribution to the publication is secondary to those named in creator elements. 
    QString type;
    QString format; // should be one of: event, image, interactive resource, moving image, physical object, service, software, sound, still image, text
    QString source; // Information regarding a prior resource from which the publication was derived;
    QString relation;
    QString coverage; // space and time covered by the work
    QString rights; // A statement about rights, or a reference to one. In this specification, the copyright notice and any further rights description should appear directly.
    EpubExportStructureMetadata()
    {
        title = "";
        author = "";
        subject = "";
        date = "";
        id = "";
        language = "";
        keywords = "";
        description = "";
        publisher = "";
        contributor = "";
        type = "";
        format = "";
        source = "";
        relation = "";
        coverage = "";
        rights = "";
    }
};
*/

struct EpubExportStructureManifestItem
{
    QString id;
    QString href;
    QString mediatype;
    int section; // TODO: not filled yet: fill this instead of xhtmlFile
    QString title; // TODO: not filled yet: fill this instead of xhtmlFile
    QString filename; // TODO: not filled yet: fill this instead of xhtmlFile
    EpubExportStructureManifestItem()
    {
        id = "";
        filename = "";
        mediatype = "";
        title = "";
        section = 0;
        href = "";
    }
};


class EpubExportStructure : public QObject
{
    Q_OBJECT

public:
	EpubExportStructure();
	~EpubExportStructure();

	void readMetadata(ScribusAPIDocumentMetadata  metadata);
	ScribusAPIDocumentMetadata getMetadata() {return metadata;}

	void setFilename(QString filename) {this->filename = filename;}
	void addToManifest(EpubExportStructureManifestItem item) {this->manifest.append(item);}
	void addToManifest(QString id, QString path, QString mediatype);
	void addToToc(QString id, QString path, QString title);
	void addToToc(EpubExportStructureManifestItem item) {this->toc.append(item);}
    QString getOPF();
    QString getNCX();
    QString getContainer();
	void setCover(QByteArray cover) {this->cover = cover;}
    bool hasCover() {return !this->cover.isEmpty();}
    QByteArray getCover();
private:
    ScribusAPIDocumentMetadata metadata;
    QString filename;
    QVector<EpubExportStructureManifestItem> manifest;
    QVector<EpubExportStructureManifestItem> toc;
    QByteArray cover; // byte representation of the cover image
};

QDebug operator<<(QDebug dbg, const EpubExportStructure &structure);
// QDebug operator<<(QDebug dbg, const EpubExportStructureMetadata &metadata);
QDebug operator<<(QDebug dbg, const EpubExportStructureManifestItem &item);

#endif // EPUBEXPORTSTRUCTURE_H
