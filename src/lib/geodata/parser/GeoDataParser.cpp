/*
    Copyright (C) 2007, 2008 Nikolas Zimmermann <zimmermann@kde.org>

    This file is part of the KDE project

    This library is free software you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    aint with this library see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/


// Own
#include "GeoDataParser.h"

// Qt
#include <QtCore/QDebug>

// Geodata
#include "GeoDataDocument.h"
#include "GeoDocument.h"
#include "GeoTagHandler.h"


// TODO: GeoRSS support
// #include "GeoRSSElementDictionary.h"

// GPX support
#include "GPXElementDictionary.h"

// KML support
#include "KmlElementDictionary.h"

namespace Marble
{

using namespace GeoDataElementDictionary;

GeoDataParser::GeoDataParser(GeoDataSourceType source)
    : GeoParser(source)
{
}

GeoDataParser::~GeoDataParser()
{
}

bool GeoDataParser::isValidDocumentElement() const
{
    switch ((GeoDataSourceType) m_source) {
    // TODO: case GeoData_GeoRSS:
    case GeoData_GPX:
        return isValidElement(gpxTag_gpx);
    case GeoData_KML:
        return isValidElement(kml::kmlTag_kml);
    default:
        Q_ASSERT(false);
        return false;
    }
}

void GeoDataParser::raiseDocumentElementError()
{
    switch ((GeoDataSourceType) m_source) {
    // TODO: case GeoData_GeoRSS:
    case GeoData_GPX:
        raiseError(QObject::tr("The file is not a valid GPX 1.0 / 1.1 file"));
        break;                
    case GeoData_KML:
        raiseError(QObject::tr("The file is not a valid KML 2.0 / 2.1 / 2.2 file"));
        break;
    default:
        GeoParser::raiseDocumentElementError();
        break;
    }
}

bool GeoDataParser::isValidElement(const QString& tagName) const
{
    if (!GeoParser::isValidElement(tagName))
        return false;

    switch ((GeoDataSourceType) m_source) {
    // TODO: case GeoData_GeoRSS:
    case GeoData_GPX:
        return (namespaceUri() == gpxTag_nameSpace10 || namespaceUri() == gpxTag_nameSpace11);
    case GeoData_KML:
        return (namespaceUri() == kml::kmlTag_nameSpace20 || 
                namespaceUri() == kml::kmlTag_nameSpace21 || 
                namespaceUri() == kml::kmlTag_nameSpace22);
    default:
        break;
    }

    // Should never be reached.
    Q_ASSERT(false);
    return false;
}

GeoDocument* GeoDataParser::createDocument() const
{
    return new GeoDataDocument;
}

// Global helper function for the tag handlers
GeoDataDocument* geoDataDoc(GeoParser& parser)
{
    GeoDocument* document = parser.activeDocument();
    Q_ASSERT(document->isGeoDataDocument());
    return static_cast<GeoDataDocument*>(document);
}

}
