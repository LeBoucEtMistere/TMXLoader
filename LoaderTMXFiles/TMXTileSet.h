//
//  TMXTileSet.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXTileSet_h
#define LoaderTMXFiles_TMXTileSet_h


#include <string>
#include <map>
#include "TMXProperties.h"
#include "TMXImage.h"
class TMXProperties;

class TMXTileSet
{
public:
	TMXTileSet();
	~TMXTileSet();
	
	int firtGlobalID;
	std::string name;
    std::string source;
	TMXImage* image;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
    std::map<int,TMXProperties*> properties;
};

#endif
