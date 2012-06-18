//
//  TMXProperties.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 16/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXProperties_h
#define LoaderTMXFiles_TMXProperties_h

#include <map>
#include <string>


class TMXProperties
{
public:
    TMXProperties();
    ~TMXProperties();
    
    std::map<std::string,std::string> properties;
        
};

#endif
