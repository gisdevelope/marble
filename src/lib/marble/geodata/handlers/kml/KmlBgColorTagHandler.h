//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2012      Mohammed Nafees <nafees.technocool@gmail.com>
//

#ifndef KMLBGCOLORTAGHANDLER_H
#define KMLBGCOLORTAGHANDLER_H

#include "GeoTagHandler.h"

namespace Marble
{
namespace kml
{

class KmlbgColorTagHandler : public GeoTagHandler
{
public:
    GeoNode * parse( GeoParser & ) const override;
};

}
}

#endif
