/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
*/
/*
int v_num = 0; //��¼������� 
int vn_num = 0;//��¼���ߵ�����
int f_num = 0; //��¼������� 
GLfloat **vArr; //��ŵ�Ķ�ά����
GLfloat **vnArr;//��ŷ��ߵĶ�ά���� 
int **fvArr; //����涥��Ķ�ά����
int **fnArr; //����淨�ߵĶ�ά����


int readfile(string addrstr) //���ļ����ݶ���������ȥ 
{
	vArr = new GLfloat*[v_num];
	for (int i = 0; i < v_num; i++)
	{
		vArr[i] = new GLfloat[3];
	}

	vnArr = new GLfloat*[vn_num];
	for (int i = 0; i<vn_num; i++)
	{
		vnArr[i] = new GLfloat[3];
	}

	fvArr = new int*[f_num];
	fnArr = new int*[f_num];
	for (int i = 0; i<f_num; i++)
	{
		fvArr[i] = new int[3];
		fnArr[i] = new int[3];
	}
	ifstream infile(addrstr.c_str());
	string sline;//ÿһ��
	int ii = 0, jj = 0, kk = 0;
	while (getline(infile, sline))
	{
		if (sline[0] == 'v')
		{
			if (sline[1] == 'n')//vn 
			{
				istringstream sin(sline);
				sin >> s1 >> f2 >> f3 >> f4;
				vnArr[ii][0] = f2;
				vnArr[ii][1] = f3;
				vnArr[ii][2] = f4;     ii++;
			}
			else//v 
			{
				istringstream sin(sline);
				sin >> s1 >> f2 >> f3 >> f4;
				vArr[jj][0] = f2;
				vArr[jj][1] = f3;
				vArr[jj][2] = f4;     jj++;

			}
		}
		if (sline[0] == 'f') //��ȡ��
		{
			istringstream in(sline);
			GLfloat a;
			in >> s1;//ȥ��ǰ׺f  
			int i, k;
			for (i = 0; i<3; i++)
			{
				in >> s1;     cout << s1 << endl;     //ȡ�ö��������ͷ�������    
				a = 0;     for (k = 0; s1[k] != '/'; k++)
				{
					a = a * 10 + (s1[k] - 48);
				}
				fvArr[kk][i] = a;      a = 0;
				for (k = k + 2; s1[k]; k++)
				{
					a = a * 10 + (s1[k] - 48);;
				}     fnArr[kk][i] = a;

			}   kk++;
		}
	} return 0;

}
*/
