#include "ModelLoader.h"

ModelLoader::ModelLoader()
{
}
ModelLoader::ModelLoader(char* filename)
{
	this->Load(filename);
}
bool ModelLoader::LoadMTL(std::string filename){
	std::string line;
	std::ifstream objFile(filename);
	if (objFile.is_open())													// If obj file is open, continue
	{
		std::cout << "Loading Material File: " << filename << std::endl;
		std::string matName;
		while (!objFile.eof())
		{
			std::getline(objFile, line);
			if (line.c_str()[0] == 'n')//newmtl
			{
				std::string s = line;
				//std::cout << line << std::endl;
				std::vector<std::string> result;
				std::istringstream iss(s);
				for (std::string s; iss >> s;)
					result.push_back(s);
				matName = result[1];
				//std::cout << result[1] << std::endl;
			}
			if (line.c_str()[0] == 'K' &&line.c_str()[1] == 'd')
			{
				std::string s = line;
				//std::cout << line << std::endl;
				std::vector<std::string> result;
				std::istringstream iss(s);
				for (std::string s; iss >> s;)
					result.push_back(s);
				float r = ::atof(result[1].c_str());
				float g = ::atof(result[2].c_str());
				float b = ::atof(result[3].c_str());
				matlib[matName].diff.r = r;
				//std::cout << matlib[matName].r << std::endl;
				matlib[matName].diff.g = g;
				matlib[matName].diff.b = b;
				//std::cout << result[1] << std::endl;
			}
			if (line.c_str()[0] == 'K' &&line.c_str()[1] == 's')
			{
				std::string s = line;
				//std::cout << line << std::endl;
				std::vector<std::string> result;
				std::istringstream iss(s);
				for (std::string s; iss >> s;)
					result.push_back(s);
				float r = ::atof(result[1].c_str());
				float g = ::atof(result[2].c_str());
				float b = ::atof(result[3].c_str());
				matlib[matName].spec.r = r;
				//std::cout << matlib[matName].r << std::endl;
				matlib[matName].spec.g = g;
				matlib[matName].spec.b = b;
				//std::cout << result[1] << std::endl;
			}
			if (line.c_str()[0] == 'K' &&line.c_str()[1] == 'a')
			{
				std::string s = line;
				//std::cout << line << std::endl;
				std::vector<std::string> result;
				std::istringstream iss(s);
				for (std::string s; iss >> s;)
					result.push_back(s);
				float r = ::atof(result[1].c_str());
				float g = ::atof(result[2].c_str());
				float b = ::atof(result[3].c_str());
				matlib[matName].amb.r = r;
				//std::cout << matlib[matName].r << std::endl;
				matlib[matName].amb.g = g;
				matlib[matName].amb.b = b;
				//std::cout << result[1] << std::endl;
			}
			if (line.c_str()[0] == 'm' && line.c_str()[4] == 'K')
			{
				std::string s = line;
				//std::cout << line << std::endl;
				//std::vector<std::string> result;
				//std::istringstream iss(s);
				/*for (std::string s; iss >> s;)
					result.push_back(s);*/
				line = line.substr(line.find_first_of(" \t") + 1);
				/*for (std::string s; iss >> s;)
				result.push_back(s);*/
				std::string file = filename;
				std::size_t found = file.find_last_of("/");
				std::string texturePath = file.substr(0, found) + "/" + line;
				std::cout << "Loading texture: " << texturePath << std::endl;
				matlib[matName].textureID = SOIL_load_OGL_texture
					(
					texturePath.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);

				/* check for an error during the load process */
				if (0 == matlib[matName].textureID)
				{
					std::cout << "SOIL loading error: " << SOIL_last_result <<std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << "Unable to open file "<< filename << std::endl;;
		return false;
	}

	return true;
}
bool ModelLoader::Load(char *filename){
	
	std::string line;
	
	std::ifstream objFile(filename);
	if (objFile.is_open())													// If obj file is open, continue
	{
		std::cout << "Loading model: " << filename << std::endl;
		while (!objFile.eof())											// Start reading file data
		{
			std::getline(objFile, line);											// Get line from file
			if (line.c_str()[0] == 'm')										// The first character is a v: on this line is a vertex stored.
			{
				std::string file = filename;
				std::string s = line;
				//std::cout << line << std::endl;
				std::vector<std::string> result;
				std::istringstream iss(s);
				//trim line
				line = line.substr(line.find_first_of(" \t") + 1);
				//get file path of MTL file
				std::size_t found = file.find_last_of("/");
				std::string MTLPath = file.substr(0, found) + "/" + line;
				//std::cout << MTLPath;
				if (this->LoadMTL(MTLPath))
				{
					//automatically use materials
					useMats = true;
				}

			}
			if (line.c_str()[0] == 'v' && line.c_str()[1] == ' ')										// vertex stored.
			{
				line[0] = ' ';												
				vertex tmp;
				sscanf(line.c_str(), "%f %f %f ", &tmp.x, &tmp.y, &tmp.z);
				//std::cout << tmp.x <<" "<< tmp.y << " "<< tmp.z << std::endl;
				vertexBuf.push_back(tmp);

			}
			if (line.c_str()[0] == 'v' && line.c_str()[1] == 'n')										// normal.
			{
				line[0] = ' ';												
				line[1] = ' ';
				vertex tmp;
				sscanf(line.c_str(), "%f %f %f ", &tmp.x, &tmp.y, &tmp.z);
				//std::cout << tmp.x<<tmp.y<< tmp.z << std::endl;
				normBuf.push_back(tmp);

			}
			if (line.c_str()[0] == 'v' && line.c_str()[1] == 't')										// uv cord.
			{
				readTextures = true;
				line[0] = ' ';												
				line[1] = ' ';
				vertex tmp;
				sscanf(line.c_str(), "%f %f", &tmp.x, &tmp.y);
				//cout << tmp.x<<tmp.y<< tmp.z << endl;
				texBuf.push_back(tmp);

			}
			if (line.c_str()[0] == 'u')																//usemtl
			{

				chunk.push_back(new faceChunk);
				
				std::string s = line;
				std::vector<std::string> result;
				std::istringstream iss(s);
				//split the line to get the materal name
				for (std::string s; iss >> s;)
					result.push_back(s);

				chunk.back()->materialName = result[1];
				
			}
			if (line.c_str()[0] == 'f')										// face
			{
				line[0] = ' ';											
				//lenth 4 array
				int normalNumber[4] = { 0, 0, 0 };
				int vertexNumber[4] = { 0, 0, 0 };
				int textureNumber[4] = { 0, 0 , 0};
				//if there were texture points it must have a texture index
				if (readTextures)
				{
					sscanf(line.c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i",								
						&vertexNumber[0],
						&textureNumber[0],
						&normalNumber[0],

						&vertexNumber[1],
						&textureNumber[1],
						&normalNumber[1],	

						&vertexNumber[2],
						&textureNumber[2],
						&normalNumber[2]);
				}
				//else no textures, only normals
				else
				{
					sscanf(line.c_str(), "%i//%i %i//%i %i//%i",								
						&vertexNumber[0],
						&normalNumber[0],

						&vertexNumber[1],
						&normalNumber[1],	

						&vertexNumber[2],
						&normalNumber[2]);
				}

				
				//if there was a valid MTL file loaded then seperate each face into chunks
				if (useMats)
				{
					chunk.back()->vertexIndices.push_back(vertexNumber[0]);
					chunk.back()->vertexIndices.push_back(vertexNumber[1]);
					chunk.back()->vertexIndices.push_back(vertexNumber[2]);

					if (readTextures)
					{
						chunk.back()->textureIndices.push_back(textureNumber[0]);
						chunk.back()->textureIndices.push_back(textureNumber[1]);
						chunk.back()->textureIndices.push_back(textureNumber[2]);
					}

					chunk.back()->normalIndices.push_back(normalNumber[0]);
					chunk.back()->normalIndices.push_back(normalNumber[1]);
					chunk.back()->normalIndices.push_back(normalNumber[2]);
				}
				//no MTL file found no need for chunks 
				else
				{
					vertexIndices.push_back(vertexNumber[0]);
					vertexIndices.push_back(vertexNumber[1]);
					vertexIndices.push_back(vertexNumber[2]);
					if (readTextures)
					{
						textureIndices.push_back(textureNumber[0]);
						textureIndices.push_back(textureNumber[1]);
						textureIndices.push_back(textureNumber[2]);
					}
					normalIndices.push_back(normalNumber[0]);
					normalIndices.push_back(normalNumber[1]);
					normalIndices.push_back(normalNumber[2]);
				}
				
			}
		}
		objFile.close();														// Close OBJ file
		//if there were materials found, there should be chunks 
		if (useMats)
		{
			//for each chunk i.e. each faces that have different materials 
			for (unsigned int j = 0; j < chunk.size(); j++)
			{
				//for each index
				for (unsigned int i = 0; i<chunk[j]->vertexIndices.size(); i++){

					// Get the indices of its attributes
					unsigned int vertexIndex = chunk[j]->vertexIndices[i] - 1;
					unsigned int normalIndex = chunk[j]->normalIndices[i] - 1;
					//if there were textures 
					if (readTextures)
					{
						unsigned int textureIndex = chunk[j]->textureIndices[i] - 1;
						chunk[j]->tex.push_back(texBuf[textureIndex].x);
						chunk[j]->tex.push_back(texBuf[textureIndex].y);
					}
					
					// Get and set the attributes with the index
					chunk[j]->tri.push_back(vertexBuf[vertexIndex].x);
					chunk[j]->tri.push_back(vertexBuf[vertexIndex].y);
					chunk[j]->tri.push_back(vertexBuf[vertexIndex].z);

					chunk[j]->norm.push_back(normBuf[normalIndex].x);
					chunk[j]->norm.push_back(normBuf[normalIndex].y);
					chunk[j]->norm.push_back(normBuf[normalIndex].z);

				}
			}
		}
		else
		{
			//for each index
			for (unsigned int i = 0; i < vertexIndices.size(); i++){

				// Get the indices of its attributes
				unsigned int vertexIndex = vertexIndices[i] - 1;
				unsigned int normalIndex = normalIndices[i] - 1;
				unsigned int textureIndex = textureIndices[i] - 1;

				// Get andset the attributes with the index

				tri.push_back(vertexBuf[vertexIndex].x);
				tri.push_back(vertexBuf[vertexIndex].y);
				tri.push_back(vertexBuf[vertexIndex].z);

				tex.push_back(texBuf[textureIndex].x);
				tex.push_back(texBuf[textureIndex].y);

				norm.push_back(normBuf[normalIndex].x);
				norm.push_back(normBuf[normalIndex].y);
				norm.push_back(normBuf[normalIndex].z);
			}
		}

	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return false;
	}
	loaded = true;
	return true;
}
void ModelLoader::Draw()
{
	if (loaded)
	{
		glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
		glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);				// Enable texture coord arrays

		if (useMats)
		{
			for (unsigned int i = 0; i < chunk.size(); i++)
			{
				//get the material name of the current chunk and set the diffuse, specularand texture of that chunk
				float colorDiff[4] = { matlib[chunk[i]->materialName].diff.r, matlib[chunk[i]->materialName].diff.g, matlib[chunk[i]->materialName].diff.b, 1.0 };
				float colorSpec[4] = { matlib[chunk[i]->materialName].spec.r, matlib[chunk[i]->materialName].spec.g, matlib[chunk[i]->materialName].spec.b, 1.0 };
				//std::cout << matlib[chunk[i]->materialName].textureID << std::endl;

				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorDiff);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpec);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);
				glColor4fv(colorDiff);
				//std::cout << chunk[i]->materialName << std::endl;
				glBindTexture(GL_TEXTURE_2D, matlib[chunk[i]->materialName].textureID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

				// when texture area is small, bilinear filter the closest mipmap
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				// when texture area is large, bilinear filter the first mipmap
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glVertexPointer(3, GL_FLOAT, 0, &chunk[i]->tri[0]);				// Vertex Pointer to triangle array
				glNormalPointer(GL_FLOAT, 0, &chunk[i]->norm[0]);				// Normal pointer to normal array
				glTexCoordPointer(2, GL_FLOAT, 0, &chunk[i]->tex[0]);			// texture coord pointer to normal array
				glDrawArrays(GL_TRIANGLES, 0, chunk[i]->tri.size() / 3);		// Draw the triangles	
			}
		}
		else
		{
			glColor3f(0.5, 0.5, 0.5);//fallback
			glVertexPointer(3, GL_FLOAT, 0, &tri[0]);			// Vertex Pointer to triangle array
			glNormalPointer(GL_FLOAT, 0, &norm[0]);				// Normal pointer to normal array
			glDrawArrays(GL_TRIANGLES, 0, tri.size() / 3);		// Draw the triangles
		}

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);				// Disable texture coord arrays
		glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
		glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
	}
	else
	{
		std::cout << "ERROR: No model loaded" << std::endl;
	}
}