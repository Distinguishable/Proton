#include "OBJLoader.h"

namespace proton {
	namespace base {
		namespace renderer {
			bool is_near(float v1, float v2) {
				return fabs(v1 - v2) < 0.01f;
			}

			bool getSimilarVertexIndex(
				glm::vec3 & in_vertex,
				glm::vec2 & in_uv,
				glm::vec3 & in_normal,
				std::vector<glm::vec3> & out_vertices,
				std::vector<glm::vec2> & out_uvs,
				std::vector<glm::vec3> & out_normals,
				unsigned short & result
			) {
				for (unsigned int i = 0; i < out_vertices.size(); i++) {
					if (
						is_near(in_vertex.x, out_vertices[i].x) &&
						is_near(in_vertex.y, out_vertices[i].y) &&
						is_near(in_vertex.z, out_vertices[i].z) &&
						is_near(in_uv.x, out_uvs[i].x) &&
						is_near(in_uv.y, out_uvs[i].y) &&
						is_near(in_normal.x, out_normals[i].x) &&
						is_near(in_normal.y, out_normals[i].y) &&
						is_near(in_normal.z, out_normals[i].z)
						) {
						result = i;
						return true;
					}
				}
				return false;
			}

			void indexVBO_slow(
				std::vector<glm::vec3> & in_vertices,
				std::vector<glm::vec2> & in_uvs,
				std::vector<glm::vec3> & in_normals,

				std::vector<unsigned short> & out_indices,
				std::vector<glm::vec3> & out_vertices,
				std::vector<glm::vec2> & out_uvs,
				std::vector<glm::vec3> & out_normals
			) {
				for (unsigned int i = 0; i < in_vertices.size(); i++) {
					unsigned short index;
					bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

					if (found) { 
						out_indices.push_back(index);
					}
					else { 
						out_vertices.push_back(in_vertices[i]);
						out_uvs.push_back(in_uvs[i]);
						out_normals.push_back(in_normals[i]);
						out_indices.push_back((unsigned short)out_vertices.size() - 1);
					}
				}
			}

			struct PackedVertex {
				glm::vec3 position;
				glm::vec2 uv;
				glm::vec3 normal;
				bool operator<(const PackedVertex that) const {
					return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
				};
			};

			bool getSimilarVertexIndex_fast(
				PackedVertex & packed,
				std::map<PackedVertex, unsigned short> & VertexToOutIndex,
				unsigned short & result
			) {
				std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
				if (it == VertexToOutIndex.end()) {
					return false;
				}
				else {
					result = it->second;
					return true;
				}
			}

			void indexVBO(
				std::vector<glm::vec3> & in_vertices,
				std::vector<glm::vec2> & in_uvs,
				std::vector<glm::vec3> & in_normals,

				std::vector<unsigned short> & out_indices,
				std::vector<glm::vec3> & out_vertices,
				std::vector<glm::vec2> & out_uvs,
				std::vector<glm::vec3> & out_normals
			) {
				std::map<PackedVertex, unsigned short> VertexToOutIndex;

				for (unsigned int i = 0; i < in_vertices.size(); i++) {

					PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };

					unsigned short index;
					bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

					if (found) { 
						out_indices.push_back(index);
					}
					else { 
						out_vertices.push_back(in_vertices[i]);
						out_uvs.push_back(in_uvs[i]);
						out_normals.push_back(in_normals[i]);
						unsigned short newindex = (unsigned short)out_vertices.size() - 1;
						out_indices.push_back(newindex);
						VertexToOutIndex[packed] = newindex;
					}
				}
			}







			void indexVBO_TBN(
				std::vector<glm::vec3> & in_vertices,
				std::vector<glm::vec2> & in_uvs,
				std::vector<glm::vec3> & in_normals,
				std::vector<glm::vec3> & in_tangents,
				std::vector<glm::vec3> & in_bitangents,

				std::vector<unsigned short> & out_indices,
				std::vector<glm::vec3> & out_vertices,
				std::vector<glm::vec2> & out_uvs,
				std::vector<glm::vec3> & out_normals,
				std::vector<glm::vec3> & out_tangents,
				std::vector<glm::vec3> & out_bitangents
			) {
				for (unsigned int i = 0; i < in_vertices.size(); i++) {

					unsigned short index;
					bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

					if (found) {
						out_indices.push_back(index);

						out_tangents[index] += in_tangents[i];
						out_bitangents[index] += in_bitangents[i];
					}
					else { 
						out_vertices.push_back(in_vertices[i]);
						out_uvs.push_back(in_uvs[i]);
						out_normals.push_back(in_normals[i]);
						out_tangents.push_back(in_tangents[i]);
						out_bitangents.push_back(in_bitangents[i]);
						out_indices.push_back((unsigned short)out_vertices.size() - 1);
					}
				}

			}
			Model OBJLoader::LoadOBJ(const char* filePath, glm::vec3 position, shader::Shader& shader) {
				std::vector < glm::vec3 > temp_vertices;
				std::vector < glm::vec2 > temp_uvs;
				std::vector < glm::vec3 > temp_normals;
				std::vector < unsigned short> temp_indices;

				std::vector < glm::vec3 > out_vertices;
				std::vector < glm::vec2 > out_uvs;
				std::vector < glm::vec3 > out_normals;
				std::vector < unsigned short> out_indices;

				std::vector < glm::vec3 > final_vertices;
				std::vector < glm::vec2 > final_uvs;
				std::vector < glm::vec3 > final_normals;
				std::vector < unsigned short> final_indices;

				std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
				FILE * file = fopen(filePath, "r");
				if (file == NULL) {
					printf("Impossible to open the file!\n");
					getchar();
				}

				while (1) {

					char lineHeader[128];

					int res = fscanf(file, "%s", lineHeader);
					if (res == EOF)
						break; 
					if (strcmp(lineHeader, "v") == 0) {
						glm::vec3 vertex;
						fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
						temp_vertices.push_back(vertex);
					}
					else if (strcmp(lineHeader, "vt") == 0) {
						glm::vec2 uv;
						fscanf(file, "%f %f\n", &uv.x, &uv.y);
						uv.y = -uv.y;
						temp_uvs.push_back(uv);
					}
					else if (strcmp(lineHeader, "vn") == 0) {
						glm::vec3 normal;
						fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
						temp_normals.push_back(normal);
					}
					else if (strcmp(lineHeader, "f") == 0) {
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
						int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
						if (matches != 9) {
							printf("File can't be read\n");
						}
						vertexIndices.push_back(vertexIndex[0]);
						vertexIndices.push_back(vertexIndex[1]);
						vertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
						normalIndices.push_back(normalIndex[0]);
						normalIndices.push_back(normalIndex[1]);
						normalIndices.push_back(normalIndex[2]);
					}
					else {
						char stupidBuffer[1000];
						fgets(stupidBuffer, 1000, file);
					}

				}

				for (unsigned int i = 0; i < vertexIndices.size(); i++) {

					unsigned int vertexIndex = vertexIndices[i];
					unsigned int uvIndex = uvIndices[i];
					unsigned int normalIndex = normalIndices[i];

					glm::vec3 vertex = temp_vertices[vertexIndex - 1];
					glm::vec2 uv = temp_uvs[uvIndex - 1];
					glm::vec3 normal = temp_normals[normalIndex - 1];

					out_vertices.push_back(vertex);
					out_uvs.push_back(uv);
					out_normals.push_back(normal);

				}

				indexVBO(out_vertices, out_uvs, out_normals, final_indices, final_vertices, final_uvs, final_normals);

				return Model(final_vertices, final_uvs, final_normals, final_indices, position, shader);
			}
		}
	}
}