//
//  main.cpp
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "TMXLoader.h"

int main (int argc, const char * argv[])
{

    TMXLoader loader; //create a loader
    loader.LoadFromFile("mapiso.tmx"); //load a .tmx from a file
    TMXMap map = loader.getTMXMap(); //get a TMXMap object from the loader
    return 0;
}

