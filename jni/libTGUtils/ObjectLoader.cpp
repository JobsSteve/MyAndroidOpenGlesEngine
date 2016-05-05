#include "ObjectLoader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <jni.h>
#include <android/log.h>

#include "Mesh.h"
#include "Vector3F.h"

#define LOG_TAG "ObjectLoader.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

Mesh* GetModelFromOBJ(std::string filePath)
{
	int verticeSize = 0;
	int textureSize = 0;
	int normalSize = 0;
	int facesSize = 0;
	int maxAmountOfVerticesPerFace = 0;

	std::string line;
	bool normalIncluded = false;

	std::ifstream obj(filePath.c_str());
	if (obj.is_open())
	{
		while (obj.good())
		{
			getline(obj, line);
			//LOGI("Reading--%s", line.c_str());
			switch (line[0])
			{
			case 'v':
				if (line[1] == 'n')
				{
					normalSize++;
				}
				else if (line[1] == ' ')
				{
					verticeSize++;
				}
				else if (line[1] == 't')
				{
					textureSize++;
				}
				break;
			case 'f':
				facesSize++;

				std::istringstream f(line.substr(2));
				std::string s;

				int verticesInFace = 0;

				while (getline(f, s, ' ')) {
					verticesInFace++;
				}

				maxAmountOfVerticesPerFace = (maxAmountOfVerticesPerFace < verticesInFace) ? verticesInFace : maxAmountOfVerticesPerFace;
				break;
			}
		}

		obj.clear();
		obj.seekg(0, std::ios::beg);

		Vector3F *vertices = (Vector3F *)malloc(verticeSize * sizeof(Vector3F));	//TODO: Free at destructor of mesh
		Vector3F *texture = (Vector3F *)malloc(textureSize * sizeof(Vector3F));	//TODO: Free at destructor of mesh
		Vector3F *normals = (Vector3F *)malloc(normalSize * sizeof(Vector3F));	//TODO: Free at destructor of mesh
		Vector3F *faces = (Vector3F *)malloc(facesSize * sizeof(Vector3F) * maxAmountOfVerticesPerFace);

		int vertexIndex = 0;
		int textureIndex = 0;
		int normalsIndex = 0;
		int facesIndex = 0;

		while (obj.good())
		{
			getline(obj, line);

			switch (line[0])
			{
			case 'v':
				if (line[1] == 'n')
				{
					normalIncluded = true;

					std::istringstream f(line.substr(3));
					std::string s;
					float x = 0.0;
					float y = 0.0;
					float z = 0.0;

					int index = 0;
					while (getline(f, s, ' ')) {
						switch (index)
						{
						case 0:
							x = (float)::atof(s.c_str());
							break;
						case 1:
							y = (float)::atof(s.c_str());
							break;
						case 2:
							z = (float)::atof(s.c_str());
							break;
						}
						index++;
					}

					normals[normalsIndex] = Vector3F( x, y, z );
					normalsIndex++;
				}
				else if (line[1] == ' ')
				{
					std::istringstream f(line.substr(2));
					std::string s;
					float x = 0.0;
					float y = 0.0;
					float z = 0.0;

					int index = 0;
					while (getline(f, s, ' ')) {
						switch (index)
						{
						case 0:
							x = (float)::atof(s.c_str());
							break;
						case 1:
							y = (float)::atof(s.c_str());
							break;
						case 2:
							z = (float)::atof(s.c_str());
							break;
						}
						index++;
					}

					vertices[vertexIndex] = { x, y, z };
					vertexIndex++;
				}
				else if (line[1] == 't')
				{
					std::istringstream f(line.substr(3));
					std::string s;
					float u = 0.0;
					float v = 0.0;

					int index = 0;
					while (getline(f, s, ' ')) {
						switch (index)
						{
						case 0:
							u = (float)::atof(s.c_str());
							break;
						case 1:
							v = (float)::atof(s.c_str());
							break;
						}
						index++;
					}

					texture[textureIndex] = { u, 1 - v, 0 };
					textureIndex++;
				}
				break;
			case 'f':
				std::istringstream f(line.substr(2));
				std::string s;

				if (normalIncluded)
				{
					while (getline(f, s, ' ')) {
						std::istringstream f1(s);
						std::string s1;
						int index = 0;

						float x = 0.0;
						float y = 0.0;
						float z = 0.0;

						while (getline(f1, s1, '/')) {

							switch (index)
							{
							case 0:
								x = (float)::atof(s1.c_str());
								break;
							case 1:
								y = (float)::atof(s1.c_str());
								break;
							case 2:
								z = (float)::atof(s1.c_str());
								break;
							}
							index++;
						}
						s1.erase(std::remove(s1.begin(), s1.end(), ' '), s1.end());

						if (!(s1 == ""))
						{
							faces[facesIndex] = { x, y, z };
							facesIndex++;
						}
					}
				}
				else
				{
					while (getline(f, s, ' ')) {
						std::istringstream f1(s);
						std::string s1;
						int index = 0;

						float x = 0.0;
						float y = 0.0;

						while (getline(f1, s1, '/')) {

							switch (index)
							{
							case 0:
								x = (float)::atof(s1.c_str());
								break;
							case 1:
								y = (float)::atof(s1.c_str());
								break;
							}
							index++;
						}
						s1.erase(std::remove(s1.begin(), s1.end(), ' '), s1.end());

						if (!(s1 == ""))
						{
							faces[facesIndex] = { x, y, 0 };
							facesIndex++;
						}
					}
				}
				break;
			}
		}

		obj.close();

		return new Mesh(vertices, normals, texture, faces, verticeSize, normalSize, textureSize, facesSize, maxAmountOfVerticesPerFace);
	}
	else
	{
		std::cout << "Unable to open file " << filePath << std::endl << std::endl;
		exit(11);
		return new Mesh();
	}
}
