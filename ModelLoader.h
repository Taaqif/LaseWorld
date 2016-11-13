//  ModelLoader.h
//  Header file for the ModelLoader class
//  This class basically loads in a TRIANGULATED OBJ file to memory then has functions to allow
//  the user to draw the OBJ file
//  
//  This class does work with textures using the SOIL.h library (needs to be statically linked)
//  More-so it does basic color drawing using the asociated MTL file (If found)
//
//  Taaqif Peck, 2016
//--------------------------------------------------------------------------------------

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "glut.h"
#include <map>
#include <SOIL.h>
/**
*
* @class ModelLoader
* @brief Loads an OBJ file to memory with textures and color
*
*/
class ModelLoader
{
public:
	/**
	* @brief Default Constructor
	*/
	ModelLoader();
	/**
	* @brief Constructor to allow a quick loading method
	* @param filename the filename to load
	*/
	ModelLoader(char* filename);
	/**
	* @method Load
	* @brief Loads a obj from a filepath
	* @param filename the path to load from
	* @return if the loading was successful or not
	*/
	bool Load(char *filename);
	/**
	* @method Draw
	* @brief draws the loaded model on screen
	*/
	void Draw();		
	/**
	* @method LoadMTL
	* @brief Loads a MTL file from a filepath
	* @param filename the path to load from
	* @return if the loading was successful or not
	*/
	bool LoadMTL(std::string filename);

private:
	///used to check if materials should be used 
	bool useMats = false;
	///used ti check if model has textures
	bool readTextures = false;
	///check if a file has been loaded first
	bool loaded = false;
	///used to store the indices of the vertex, normal and texture cordinates
	std::vector<unsigned int> vertexIndices, textureIndices, normalIndices;
	///used to store the actual vertex, normal and texture cordinates
	std::vector<GLfloat> norm, tri,tex;
	///makeshift vertex with x,y,z cordinates
	struct vertex {
		GLfloat x, y, z;
	};
	///makeshift material with a texture, diffuse, ambiant and specular rgb colors 
	struct mat{
		struct rgb{
			GLfloat r, g, b;
		};
		rgb diff;
		rgb spec;
		rgb amb;
		GLuint textureID;
	};
	///used to store a chunk of faces with a similar material name 
	struct faceChunk{
		///the material name for this chunk
		std::string materialName;
		///used to store the indices of the vertex, normal and texture cordinates for this chunk
		std::vector<unsigned int> vertexIndices, normalIndices, textureIndices;
		///used to store the actual vertex, normal and texture cordinates for this chunk
		std::vector<GLfloat> norm, tri,tex;
	};
	///buffer to store the vertex, normals and texture cordinated directly form the file
	std::vector<vertex> vertexBuf;
	std::vector<vertex> normBuf;
	std::vector<vertex> texBuf;

	///vectore of facechunks 
	std::vector<faceChunk*> chunk;
	///map of materials 
	std::map<std::string, mat> matlib;
};


