//
//  TMXImage.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 19/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXImage_h
#define LoaderTMXFiles_TMXImage_h


#include <string>

class TMXImage
{
public :
    TMXImage();
    ~TMXImage();
    
    std::string source;
    std::string trans;
    int width;
    int height;
    
};

#endif
