//
//  TMXPolyLine.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 18/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXPolyLine_h
#define LoaderTMXFiles_TMXPolyLine_h


#include "TMXObject.h"
#include <vector>
#include <utility>

class TMXPolyLine : public TMXObject
{
public:
    TMXPolyLine();
    ~TMXPolyLine();
    
    std::vector<std::pair<int,int> > points;
    
};

#endif
