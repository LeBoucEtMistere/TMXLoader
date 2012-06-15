//
//  TMXLoader.h
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LoaderTMXFiles_TMXLoader_h
#define LoaderTMXFiles_TMXLoader_h

#include <string>
#include "TMXMap.h"
#include "tinyxml.h"


class InternalLoader 
{
public:
	InternalLoader(std::string filename = "");	
	void LoadFromFile(std::string filename);
	TMXMap* m_map;
	
private:
	void readMap(TiXmlNode* node);
	TMXTileSet* readTileSet(TiXmlNode* node);
	const char* readImage(TiXmlNode* node);
	TMXLayer* readLayer(TiXmlNode* node);
	void readData(TiXmlNode* node, std::vector<int>& data);
	void readXML(TiXmlNode* node,std::vector<int>& data);
	void readCSV(TiXmlNode* node,std::vector<int>& data);
	void decodeblock( unsigned char* in, unsigned char* out );
	void readBase64(TiXmlNode* node,const char* compression,std::vector<int>& data);
};

#endif
