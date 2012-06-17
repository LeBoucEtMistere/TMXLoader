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
		delete p;
		p = NULL;
	} 
};

TMXObjectGroup::TMXObjectGroup() :  name(""), width(0), height(0), properties()
{}

TMXObjectGroup::~TMXObjectGroup()
{
    std::for_each(objects.begin()     , objects.end()     , Delete());
	std::for_each(polyObjects.begin()   , polyObjects.end()   , Delete());
}