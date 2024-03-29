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
#include "TMXPolyLine.h"
#include "TMXProperties.h"
class TMXProperties;

class TMXObjectGroup
{
public:
	TMXObjectGroup();
	~TMXObjectGroup();
	std::string name;
    std::string color;
    int width;
    int height;
    float opacity;
    bool visible;
    std::vector<TMXObject*> objects;
    std::vector<TMXPolyObject*> polyObjects;
    std::vector<TMXPolyLine*> polyLines;
    TMXProperties* properties;

  
};

#endif
