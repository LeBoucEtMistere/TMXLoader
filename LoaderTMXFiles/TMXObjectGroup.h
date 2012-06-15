//
//  TMXObjectGroup.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 15/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXObjectGroup_h
#define LoaderTMXFiles_TMXObjectGroup_h

#include <string>
#include <vector>
#include <algorithm>
#include "TMXObject.h"
#include "TMXPolyObject.h"

class TMXObjectGroup
{
public:
	TMXObjectGroup();
	~TMXObjectGroup();
	std::string name;
    int width;
    int height;
    std::vector<TMXObject*> objects;
    std::vector<TMXPolyObject*> polyObjects;
  
};

#endif
