//
//  TMXLoader.cpp
//  LoaderTMXFiles
//
//  Created by DEPASSE Arthur on 14/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TMXLoader.h"

#define _LOG_
#include <iostream>
#ifdef _LOG_
#define PRINT(...) printf(__VA_ARGS__)
#else
#define PRINT(...)
#endif

#include <string>
#include <sstream>
#include <iostream>

template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
    std::istringstream iss(s);
    return !(iss >> f >> t).fail();
}

struct PrintPolyPoints 
{ 
	void operator ()(std::vector<std::pair<int,int> >::iterator& p) const 
	{ 
        PRINT("%d,%d ",p->first, p->second);		
	} 
};


void error(std::string message)
{
	std::cerr<< "Error:" << message << std::endl;
}


TMXLoader::TMXLoader()
: m_map(NULL)
{}

bool TMXLoader::LoadFromFile(std::string filename)
{
	TiXmlDocument doc(filename.c_str());
	if(!doc.LoadFile())
	{
		error("TMX::Loader couldn't open file :" + filename);
		return false;
	}
	
	// create handle for reading XML node
	TiXmlHandle hdl(&doc);
	readMap(hdl.FirstChildElement("map").ToNode());
	PRINT("Reading complete!\n");
    
    return true;
}

TMXMap TMXLoader::getTMXMap()
{
    return *m_map;
}

void TMXLoader::readMap(TiXmlNode* node)
{
	PRINT("Reading Map\n");
	
	m_map = new TMXMap;
	
	TiXmlElement* pElement = node->ToElement();
	
	if(std::string(pElement->Attribute("version")) != "1.0")
		error("Support only version 1.0 of tmx files.");
	else PRINT("TMX Version 1.0\n");
	
	if(std::string(pElement->Attribute("orientation")) != "orthogonal")
		error("Support only orthogonal orientation for now.");
	else   PRINT("Orientation orthogonal\n");
	
	pElement->QueryIntAttribute("width",&(m_map->width));
	PRINT("Witdh %d\n",m_map->width);
	pElement->QueryIntAttribute("height",&(m_map->height));
	PRINT("Height %d\n",m_map->height);
	pElement->QueryIntAttribute("tilewidth",&(m_map->tileWidth));
	PRINT("TileWidth %d\n",m_map->tileWidth);
	pElement->QueryIntAttribute("tileheight",&(m_map->tileHeight));
	PRINT("TileHeight %d\n",m_map->tileHeight);
	
	// et enfin on regarde toutes les balises enfant
	for(TiXmlNode* pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		if( pChild->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			if( std::string(pChild->Value()) == "tileset")
			{
				m_map->tilesets.push_back(readTileSet(pChild)); 
			}
			else if( std::string(pChild->Value()) == "layer")
			{
				m_map->layers.push_back(readLayer(pChild));
			}
            else if (std::string(pChild->Value()) == "objectgroup")
            {
                m_map->objectGroups.push_back(readObjectGroup(pChild));
            }
		}
	}
}

TMXTileSet* TMXLoader::readTileSet(TiXmlNode* node)
{
	PRINT("Reading Tileset\n");
	
	TMXTileSet* tileset = new TMXTileSet;
	TiXmlElement* pElement = node->ToElement(); //on le converti en element
	
	tileset->name = pElement->Attribute("name");
	PRINT("name %s\n",tileset->name.c_str());
	pElement->QueryIntAttribute("firstgid",&(tileset->firtGlobalID));
	PRINT("firstgid %d\n",tileset->firtGlobalID);
	pElement->QueryIntAttribute("tilewidth",&(tileset->tileWidth));
	PRINT("tileWidth %d\n",tileset->tileWidth);
	pElement->QueryIntAttribute("tileheight",&(tileset->tileHeight));
	PRINT("tileHeight %d\n",tileset->tileHeight);
	pElement->QueryIntAttribute("spacing",&(tileset->spacing));
	PRINT("spacing %d\n",tileset->spacing);
	pElement->QueryIntAttribute("margin",&(tileset->margin));
	PRINT("margin %d\n",tileset->margin);
	
	for(TiXmlNode* pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		if ( pChild->Type() == TiXmlNode::TINYXML_ELEMENT )
		{
			if( std::string(pChild->Value()) == "image")
			{
				tileset->sourceFileName = readImage(pChild);
				PRINT("source %s\n",tileset->sourceFileName.c_str());
			}
		}
	}
	return tileset;
}

const char* TMXLoader::readImage(TiXmlNode* node)
{
	PRINT("Reading Image\n");
	TiXmlElement* pElement = node->ToElement(); //on le converti en element
	return  pElement->Attribute("source");
}

TMXLayer* TMXLoader::readLayer(TiXmlNode* node)
{
	PRINT("Reading Layer\n");
	TMXLayer* layer = new TMXLayer;
	layer->data.reserve(m_map->width*m_map->height);
	TiXmlElement* pElement = node->ToElement(); //on le converti en element
	
	layer->name = pElement->Attribute("name");
	PRINT("name %s\n",layer->name.c_str());
	pElement->QueryFloatAttribute("opacity",&(layer->opacity));
	PRINT("opacity %f\n",layer->opacity);
	pElement->QueryIntAttribute("visible",&(layer->visible));
	PRINT("visible %d\n",layer->visible);
	
	// et enfin on regarde toutes les blises enfant
	for(TiXmlNode* pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		
		if ( pChild->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			if( std::string(pChild->Value()) == "data")
			{
				readData(pChild,layer->data); 
			}
		}
	}
	return layer;
}

void TMXLoader::readData(TiXmlNode* node, std::vector<int>& data)
{
	PRINT("Reading Data:");
	TiXmlElement* pElement = node->ToElement(); //on le converti en element
	
	const char* encodage = pElement->Attribute("encoding");
	const char* compression = pElement->Attribute("compression");
	
	if( encodage == NULL) // les donnees sont stockees en XML
	{
		readXML(node,data);
	}
	else if( std::string(encodage) == "csv")
	{
		readCSV(node,data);
	}
	else if( std::string(encodage) == "base64")
	{
		readBase64(node,compression,data);
	}
	else
	{
		error("Doesn't handle this encoding");
	}
}

void TMXLoader::readXML(TiXmlNode* node,std::vector<int>& data)
{
	PRINT("XML format\n");
	// il n'y a pas d'attribut donc on passe directement ici.
	for(TiXmlNode* pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		if ( pChild->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			if( std::string(pChild->Value()) == "tile")
			{
				int i = 0;
				pChild->ToElement()->QueryIntAttribute("gid",&i);
				data.push_back(i);
				PRINT("%d,",i);
			}
		}
	}
	PRINT(" end data\n%d tiles read\n",(int)data.size());
}

void TMXLoader::readCSV(TiXmlNode* node,std::vector<int>& data)
{
	PRINT("CSV format\n");
	
	const char* csv = node->ToElement()->GetText();
	int number = 0;
	int pos = 0;
	
	//une chaine de caractere se termine toujours par 0
	while(csv[pos]!=0)
	{
		if(csv[pos] == ',')
		{
			data.push_back(number);
			PRINT("%d,",number);
			number = 0;
		}
		else if( (csv[pos] -'0' < 10) && (csv[pos] -'0' >= 0) ) 
		{
			number =  number*10+csv[pos]-'0';
		}
		pos++;
	}
	data.push_back(number);
	PRINT("%d",number);
	PRINT(" end data\n%d tiles read",(int)data.size());
}

void TMXLoader::decodeblock( unsigned char* in, unsigned char* out ) //in must contain 4 char, out must contain 3 char
{
	const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
	int len = 0;
	int v = 0;
	for (int i = 0;i<4 ; i++) 
	{
		v = in[i];
		v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
		if( v ) 
		{
			v = (unsigned char) ((v == '$') ? 0 : v - 61);
		}
		if( in[i]!=0 ) 
		{
			len++;
			if( v ) 
			{
				in[ i ] = (unsigned char) (v - 1);
			}
		}
		else 
		{
			in[i] = 0;
		}
	}
	if( len ) 
	{
		out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
		out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
		out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
	}
}

void TMXLoader::readBase64(TiXmlNode* node,const char* compression,std::vector<int>& data)
{
	PRINT("Base format, compression %s\n", compression);
	if(compression!=NULL)
	{
		error("Compression not handle");
	}
	else 
	{
		unsigned char* input_text = (unsigned char*)node->ToElement()->GetText();
		int size = strlen((const char*)input_text);
		PRINT("string base 64 size %d => %d tiles\n",size,size/4);
		unsigned char* output_text = (unsigned char*)malloc(size/4*3*sizeof(unsigned char));
		for(int i=0;i<size/4;i++)
			decodeblock(&input_text[4*i] , &output_text[3*i]);
		for (int i = 0; i<size/4*3; i+=4) 
		{
			int gid = output_text[i] |
			output_text[i + 1] << 8 |
			output_text[i + 2] << 16 |
			output_text[i + 3] << 24;
			data.push_back(gid);
			PRINT("%d,",gid);
		}
		PRINT(" end data\n%d tiles read",(int)data.size());
		free(output_text);
	}
}

TMXObjectGroup* TMXLoader::readObjectGroup(TiXmlNode *node)
{
    PRINT("Reading ObjectGroup\n");
	TMXObjectGroup* objGroup = new TMXObjectGroup;
	objGroup->objects.reserve(m_map->width*m_map->height);
    objGroup->polyObjects.reserve(m_map->width*m_map->height);
	TiXmlElement* pElement = node->ToElement(); //on le converti en element
	
	objGroup->name = pElement->Attribute("name");
	PRINT("name %s\n",objGroup->name.c_str());
	pElement->QueryIntAttribute("width",&(objGroup->width));
	PRINT("width %d\n",objGroup->width);
	pElement->QueryIntAttribute("height",&(objGroup->height));
	PRINT("height %d\n",objGroup->height);
	
	// et enfin on regarde toutes les balises enfant
	for(TiXmlNode* pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		
		if ( pChild->Type() == TiXmlNode::TINYXML_ELEMENT)
		{
			if( std::string(pChild->Value()) == "object")
			{ 
                if (!pChild->FirstChild("polygon")) 
                {
                    readObject(pChild, objGroup->objects);
                }
                else
                {
                    readPolyObject(pChild, objGroup->polyObjects);
                }
			}
		}
	}
	return objGroup;
}

void TMXLoader::readObject (TiXmlNode* node, std::vector<TMXObject*> &objects)
{
    TMXObject* obj = new TMXObject;
    TiXmlElement* pElement = node->ToElement();
    
    obj->name = pElement->Attribute("name");
    obj->type = pElement->Attribute("type");
    pElement->QueryIntAttribute("x",&(obj->posX));
    pElement->QueryIntAttribute("y",&(obj->posY));
    pElement->QueryIntAttribute("width",&(obj->width));
    pElement->QueryIntAttribute("height",&(obj->height));
    
    objects.push_back(obj);
    
    PRINT("Object added\n");
    PRINT("name : %s \n",obj->name.c_str());
    PRINT("type : %s \n",obj->type.c_str());
    PRINT("coordonnées : %d; %d\n", obj->posX, obj->posY);
    PRINT("width %d\n",obj->width);
    PRINT("height %d\n",obj->height);
    
	


}
void TMXLoader::readPolyObject (TiXmlNode* node, std::vector<TMXPolyObject*> &polyObjects)
{
    TMXPolyObject* obj = new TMXPolyObject;
    TiXmlElement* pElement = node->ToElement();
    
    obj->name = pElement->Attribute("name");
    obj->type = pElement->Attribute("type");
    pElement->QueryIntAttribute("x",&(obj->posX));
    pElement->QueryIntAttribute("y",&(obj->posY));
    
    
    TiXmlNode* pChild = node->FirstChild();
    pElement = pChild->ToElement();
    
    std::string points = pElement->Attribute("points");
    const char* pointschar = points.c_str();
    int p1 = 0;
    int p2 = 0;
    std::string s1("");
    std::string s2("");
    
    for (const char* ptr = pointschar; *ptr != '\0'; ++ptr) 
    {
        while (*ptr != ',') 
        {
            s1 += *ptr;
            ++ptr;
        }
        ++ptr;
        while (*ptr != ' ' && *ptr != '\0') 
        {
            s2 += *ptr;
            ++ptr;
        }
        
        
        if(from_string<int>(p1, s1, std::dec) && from_string<int>(p2, s2, std::dec)) //convert the strings to int in 
                                                                                     //order to make a pair of int
        {
            std::pair<int, int> pair (p1,p2);
            obj->points.push_back(pair);
            s1.clear();
            s2.clear();
            p1=0;
            p2=0;
        }
        else
        {
            error(std::string("Can't read the polygons points data in the object \""+obj->name+"\""));
        }
        
    }
    
    
    
    polyObjects.push_back(obj);
    
    PRINT("Object added\n");
    PRINT("name : %s \n",obj->name.c_str());
    PRINT("type : %s \n",obj->type.c_str());
    PRINT("coordonnées : %d; %d\n", obj->posX, obj->posY);
    PRINT("poly points : ");
    for (std::vector<std::pair<int,int> >::iterator it = obj->points.begin(); it!=obj->points.end(); it++) 
    {
        PRINT("%d,%d ",it->first, it->second);
    }
    PRINT("\n");
    //std::for_each(obj->points.begin(), obj->points.end(),PrintPolyPoints());
    


}

