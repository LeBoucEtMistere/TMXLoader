//
//  TMXMap.cpp
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TMXMap.h"

struct Delete 
{ 
	template <class T> void operator ()(T*& p) const 
	{ 
		delete p;
		p = NULL;
	} 
};

TMXMap::TMXMap()
: width(0)
, height(0)
, orientation()
, tileWidth(0)
, tileHeight(0)
, tilesets()
, layers()
,properties()
{}

TMXMap::~TMXMap()
{
	std::for_each(layers.begin()     , layers.end()     , Delete());
	std::for_each(tilesets.begin()   , tilesets.end()   , Delete());
    std::for_each(objectGroups.begin()   , objectGroups.end()   , Delete());
}