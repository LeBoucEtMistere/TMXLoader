//
//  TMXPolyObject.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 15/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXPolyObject_h
#define LoaderTMXFiles_TMXPolyObject_h

#include "TMXObject.h"
#include <string>
#include <vector>
#include <utility>

class TMXPolyObject : public TMXObject
{
public:
    TMXPolyObject();
    ~TMXPolyObject();

    std::vector<std::pair<int,int> > points;
    
};

#endif
