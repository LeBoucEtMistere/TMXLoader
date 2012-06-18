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
#include <utility>
#include <algorithm>
#include "TMXMap.h"
#include "tinyxml.h"

void error(std::string message);

class TMXLoader 
{
public:
	TMXLoader();	
	bool LoadFromFile(std::string filename);
    TMXMap getTMXMap();
	
	
private:
    
    TMXMap* m_map;
	void readMap(TiXmlNode* node);
    TMXProperties* readProperties(TiXmlNode* node);
	TMXTileSet* readTileSet(TiXmlNode* node);
    void readTileInTileset(TiXmlNode* node, std::map<int,TMXProperties*> map);
	const char* readImage(TiXmlNode* node);
	TMXLayer* readLayer(TiXmlNode* node);
	void readData(TiXmlNode* node, std::vector<int>& data);
	void readXML(TiXmlNode* node,std::vector<int>& data);
	void readCSV(TiXmlNode* node,std::vector<int>& data);
	void decodeblock( unsigned char* in, unsigned char* out );
	void readBase64(TiXmlNode* node,const char* compression,std::vector<int>& data);
    TMXObjectGroup* readObjectGroup(TiXmlNode* node);
    void readObject (TiXmlNode* node, std::vector<TMXObject*> &objects);
    void readPolyObject (TiXmlNode* node, std::vector<TMXPolyObject*> &polyObjects);
};

#endif
