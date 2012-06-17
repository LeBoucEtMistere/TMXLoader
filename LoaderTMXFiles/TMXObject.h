//
//  TMXObject.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 15/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXObject_h
#define LoaderTMXFiles_TMXObject_h

#include "TMXProperties.h"
class TMXProperties;
#include <string>

class TMXObject
{
public:
    TMXObject();
    ~TMXObject();
    
    std::string name;
    std::string type;
    int posX;
    int posY;
    int width;
    int height;
    TMXProperties properties;

};

#endif
