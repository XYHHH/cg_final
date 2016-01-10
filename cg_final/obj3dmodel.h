#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct vertex{
	double x;
	double y;
	double z;
};
struct face{
	unsigned int v1, v2, v3;
};

class obj3dmodel
{
	vector<vertex> vetexes;
	vector<face> faces;
public:
	void parse(const char* filename);
	void draw();
	obj3dmodel(){}
	~obj3dmodel(){}
};

void obj3dmodel::parse(const char *filename)
{
	string s;
	ifstream fin(filename);
	cout << "parsing" << endl;
	if (!fin){
		cout << "not found" << endl;
		return;
	}
	while (fin >> s)
	{
		if (s == "v")
		{
			vertex v;
			fin >> v.x >> v.y >> v.z;
			vetexes.push_back(v);
		}
		else if (s == "f")
		{
			face f;
			char tmp[2];
			int vn;
			fin >> f.v1 >> tmp[0] >> tmp[1] >> vn;
			fin >> f.v2 >> tmp[0] >> tmp[1] >> vn;
			fin >> f.v3 >> tmp[0] >> tmp[1] >> vn;
			faces.push_back(f);
		}
	}
	cout << "ok" << endl;
	for (int i = 0; i < faces.size() && i<10; i++){
		face tmp = faces[i];
		cout << tmp.v1 << " " << tmp.v2 << " " << tmp.v3 << endl;
	}
}

void obj3dmodel::draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	for (int i = 0; i<faces.size(); i++)
	{
		vertex v1 = vetexes[faces[i].v1 - 1];
		vertex v2 = vetexes[faces[i].v2 - 1];
		vertex v3 = vetexes[faces[i].v3 - 1];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glPopMatrix();
	glEnd();
}