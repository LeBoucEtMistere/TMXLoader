//
//  TMXObjectGroup.cpp
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 15/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TMXObjectGroup.h"

struct Delete 
{ 
	template <class T> void operator ()(T*& p) const 
	{ 
		if (p != NULL) {
            delete p;
            p = NULL;
        }
        
	} 
};

TMXObjectGroup::TMXObjectGroup() :  name(""), color(""), width(0), height(0), opacity(0), visible(true), properties(), objects(), polyObjects(), polyLines()
{}

TMXObjectGroup::~TMXObjectGroup()
{
    std::for_each(objects.begin()     , objects.end()     , Delete());
	std::for_each(polyObjects.begin()   , polyObjects.end()   , Delete());
    std::for_each(polyLines.begin(), polyLines.end(), Delete());
}