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

class TMXTileSet
{
public:
	TMXTileSet();
	~TMXTileSet();
	
	int firtGlobalID;
	std::string name;
	std::string sourceFileName;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
};

#endif
