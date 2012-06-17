//
//  TMXLayer.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXLayer_h
#define LoaderTMXFiles_TMXLayer_h

#include <string>
#include <vector>
#include "TMXProperties.h"
class TMXProperties;

class TMXLayer
{
public:
	TMXLayer();
	~TMXLayer();
	std::string name;
	float opacity;
	int  visible;
	std::vector<int> data;
    TMXProperties properties;

};

#endif
