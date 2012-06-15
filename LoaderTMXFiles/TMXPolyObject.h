//
//  TMXPolyObject.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 15/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXPolyObject_h
#define LoaderTMXFiles_TMXPolyObject_h

#include <string>
#include <vector>
#include <utility>

class TMXPolyObject
{
public:
    TMXPolyObject();
    ~TMXPolyObject();
    
    std::string name;
    std::string type;
    int posX;
    int posY;
    std::vector<std::pair<int,int> > points;
    
};

#endif
