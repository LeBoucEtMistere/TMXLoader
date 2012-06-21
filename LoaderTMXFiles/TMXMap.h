//
//  TMXMap.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXMap_h
#define LoaderTMXFiles_TMXMap_h

#include "TMXProperties.h"
class TMXProperties;

#include <vector>
#include <algorithm>
#include <string>
#include "TMXTileSet.h"
#include "TMXLayer.h"
#include "TMXObjectGroup.h"




class TMXMap
{
public:
	TMXMap();
	~TMXMap();
	
	int width;
	int height;
    std::string orientation;
	int tileWidth;
	int tileHeight;
	std::vector<TMXTileSet*> tilesets;
	std::vector<TMXLayer*>   layers;
    std::vector<TMXObjectGroup*> objectGroups;
    TMXProperties* properties;
};

#endif
