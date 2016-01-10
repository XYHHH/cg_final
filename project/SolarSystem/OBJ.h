#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED
#include <map>
#include <GL/glut.h>  //引用相关包
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
using namespace std;
//#define FILE_NAME "monkey.obj"
#define Num_Faces 4
#define Function_Draw GL_TRIANGLE_FAN

#define BITMAP_ID 0x4D42 // the universal bitmap ID
double chaji_degree(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double ans = sqrt(pow(y1*z2-z1*y2,2)+pow(z1*x2-x1*z2,2)+pow(x1*y2-y1*x2,2))/
            sqrt((x1*x1+y1*y1+z1*z1)*(x2*x2+y2*y2+z2*z2));
    cout<<"chaji_degree: "<<ans<<endl;
    return ans;
}
int LoadBitMap(const char *file)
{
    unsigned int ID, i;
    int width, height;
    byte *image;
    byte t;
    FILE *fp;
    BITMAPFILEHEADER FileHeader;
    BITMAPINFOHEADER InfoHeader;
    fp = fopen(file, "rb");
    if (fp == NULL)
    {
        perror("LoadBitMap");
        return -1;
    }
    fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    if (FileHeader.bfType != 0x4D42)  //确保文件是一个位图文件，效验文件类型
    {
        printf("Error: This file is not a bmp file!");
        fclose(fp);
        return -1;
    }
    fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    width = InfoHeader.biWidth;
    height = InfoHeader.biHeight;
    if (InfoHeader.biSizeImage == 0)
    {
        InfoHeader.biSizeImage = width * height * 3;
    }

    fseek(fp, FileHeader.bfOffBits, SEEK_SET);
    image = (byte *)malloc(sizeof(byte) * InfoHeader.biSizeImage);
    if (image == NULL)
    {
        free(image);
        printf("Error: No enough space!");
        return -1;
    }
    fread(image, 1, InfoHeader.biSizeImage, fp);
    for (i = 0; i < InfoHeader.biSizeImage; i += 3)
    {
        t = image[i];
        image[i] = image[i + 2];
        image[i + 2] = t;
    }
    fclose(fp);
    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
    //cout<<ID<<endl;
    return ID;
}
class MTL
{
public:
    GLfloat * Kd = NULL;
    GLfloat * Ka = NULL;
    GLfloat * Ks = NULL;
    GLfloat * Ke = NULL;
    GLfloat * Ns = NULL;
    GLfloat * Ni = NULL;
    GLfloat d, illum;
    unsigned int map_Ks, map_Kd, map_Bump, refl;
    string tmpp;
    MTL()
    {

    }
    int print_info()
    {
        cout << "MTL info: " << endl;
        if (Kd)
            for (int i = 0; i < 3; i++)
                cout << Kd[i] << " ";
        cout << endl;
        if (Ka)
            for (int i = 0; i < 3; i++)
                cout << Ka[i] << " ";
        cout << endl;
        if (Ks)
            for (int i = 0; i < 3; i++)
                cout << Ks[i] << " ";
        cout << endl;
        if (Ke)
            for (int i = 0; i < 3; i++)
                cout << Ke[i] << " ";
        cout << endl;
        cout << Ns[0] << endl;
        cout << Ni[0] << endl;
        cout << d << endl;
        cout << illum << endl;
        cout << "------------" << endl;
    }
    int hash_cal(string s)
    {
        int ans = 0;
        for (int i = 0; i < s.length(); i++)
            ans = (ans * 150 + s[i]) % 999983;
        return ans;
    }

    int get_info(string s) // r1 表示这个material到头啦
    {
        istringstream tmp(s);
        string ss;
        //cout<<hash_cal("map_Bump")<<endl;
        tmp >> ss;
        switch (hash_cal(ss))
        {
        case ('N'*150+'s'):
            Ns = new GLfloat[1];
            tmp >> Ns[0];
            Ns[0] = Ns[0] * 1.0 / 1000.0 * 128;
            break;
        case ('K'*150+'a'):
            Ka = new GLfloat[3];
            for (int i = 0; i < 3; i++) tmp >> Ka[i];
            break;
        case ('K'*150+'d'):
            Kd = new GLfloat[3];
            for (int i = 0; i < 3; i++) tmp >> Kd[i];
            break;
        case ('K'*150+'s'):
            Ks = new GLfloat[3];
            for (int i = 0; i < 3; i++) tmp >> Ks[i];
            break;
        case ('N'*150+'i'):
            Ni = new GLfloat[1];
            tmp >> Ni[0];
            break;
        case ('d'):
            tmp >> d;
            break;
        case (107567):
            tmp >> illum;
            break;
        //map 材质需要搞！
        case (454705)://map_Kd
            tmp >> tmpp;
            map_Kd = LoadBitMap(tmpp.c_str());
            cout << "map_Kd: " << map_Kd << endl;
            //texture_map_Kd.insert(make_pair(map_Kd,bmp));
            break;
        case (59879)://map_Bump
            tmp >> tmpp;
            break;
        case (454720): //map_Ks
            tmp >> tmpp;
            break;
        case (44487)://refl
            //something need doing
            return 1;
        default:
            cout << "useless:  ->" << ss << endl;
            break;

        }
        return 0;
    }
private:


};
class OBJ
{
public:
    OBJ(string s, double x, double y, double z)
    {
        double sum = sqrt(x * x + y * y + z * z);
        des_x = x / sum;
        des_y = y / sum;
        des_z = z / sum;
        FILE_NAME = s;
        getLineNum(FILE_NAME);
        readfile(FILE_NAME);
    }
    OBJ()
    {

    }
    void render(double x, double y, double z, double sx, double sy, double sz) //在坐标 xyz 处 自转 degree角度
    {
        double sum = sqrt(sx * sx + sy * sy + sz * sz);
        sx /= sum;
        sy /= sum;
        sz /= sum;
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();

        glTranslatef(x, y, z);
        double degree = asin(chaji_degree(des_x,des_y,des_z,sx,sy,sz)),
               pivot_x =  des_y * sz - des_z * sy,
               pivot_y = des_z * sx - des_x * sz,
               pivot_z = des_x * sy - des_y * sx;
        cout<<"translate: "<<degree<<" "<<pivot_x<<" "<<pivot_y<<" "<<pivot_z<<endl;
        glRotatef(degree/3.1415928*180,pivot_x,pivot_y,pivot_z);
        glScaled(Scale, Scale, Scale);

        for (int i = 0; i < f_num; i++)

        {
            if (current_material != MArr[i])
            {
                setMaterial(MArr[i]);
                current_material = MArr[i];
            }
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            //glColor3f(1, 1, 1);
            glBegin(Function_Draw);
            // cout<<i<<" face: fn :";
            for (int j = 0; 1 ; j++)
            {
                if (fvArr[i][j] == NULL) break;
                //cout <<fvArr[i][j]-1<<" !j! ";
                glTexCoord2f(vtArr[ftArr[i][j] - 1][0], vtArr[ftArr[i][j] - 1][1]);

                glNormal3f(vnArr[fnArr[i][j] - 1][0], vnArr[fnArr[i][j] - 1][1], vnArr[fnArr[i][j] - 1][2]);

                glVertex3f(vArr[fvArr[i][j] - 1][0], vArr[fvArr[i][j] - 1][1], vArr[fvArr[i][j] - 1][2]);

            }
            // cout<<endl;
//            glTexCoord2f(0.0f, 0.0f);
//            glVertex3f(0,1.0,0);
//            glTexCoord2f(1.0f, 0.0f);
//            glVertex3f(0, 0,1);
//            glTexCoord2f(1.0f, 1.0f);
//            glVertex3f(0, 0,0);



            glEnd();

        }

        glFlush();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    void setScale(double s)
    {
        Scale = s;
    }
private:
    string FILE_NAME;
    string current_material;
    int v_num = 0; //记录点的数量
    int vn_num = 0; //记录法线的数量
    int f_num = 0; //记录面的数量
    int vt_num = 0; //贴图坐标数
    int m_num = 0;
    GLfloat **vArr; //存放点的二维数组
    GLfloat **vnArr;//存放法线的二维数组
    GLfloat **vtArr;//存贴图坐标二维数组
    int **fvArr; //存放面顶点的二维数组
    int **fnArr; //存放面法线的二维数组
    int **ftArr; //存
    string *MArr;
    double Scale = 1, des_x, des_y, des_z;

//    QImage tex,buffer;

    map<string, MTL> MTL_map;
    string s1;
    GLfloat f2, f3, f4;
    void LoadMaterial(string s)//读某个mtl文件，存一万个newmtl
    {
        cout << "start loading " << s << endl;
        string MaterialName = "";
        string slice, head;
        ifstream infile(s.c_str());
        while (getline(infile, slice))
        {
            istringstream sli(slice);
            sli >> head;
            if (head == "newmtl")
            {
                sli >> MaterialName;
                cout << MaterialName << endl;
                MTL tmp;//= new MTL();
                while (getline(infile, slice))
                {
                    if (tmp.get_info(slice) == 1) break;
                }
                tmp.print_info();
                MTL_map.insert(make_pair(MaterialName, tmp));
            }
        }
        cout << "loading finished!" << endl;


    }
    void setMaterial(string s)
    {
        MTL tmp = MTL_map[s];
        //  tmp.print_info();
        if (tmp.Ka) glMaterialfv(GL_FRONT, GL_AMBIENT, tmp.Ka);
        if (tmp.Kd) glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp.Kd);
        if (tmp.Ks) glMaterialfv(GL_FRONT, GL_SPECULAR, tmp.Ks);
        if (tmp.Ns) glMaterialfv(GL_FRONT, GL_SHININESS, tmp.Ns);
        if (tmp.Ke) glMaterialfv(GL_FRONT, GL_EMISSION, tmp.Ke);
        glBindTexture(GL_TEXTURE_2D, tmp.map_Kd);
        //cout<<tmp.map_Kd<<endl;
//        bmp = GetBmp(tmp.map_Kd.c_str());
//        Ka[0] = 0;
//        Ka[1] = 0;
//        Ka[2] = 0;
//        //cout << Ka[1] << endl;
//        Kd[0] = 1;
//        Kd[1] = 1;
//        Kd[2] = 1;
//        //*Kd = (1, 1, 1);
//        Ks[0] = 1;
//        Ks[1] = 2;
//        Ks[2] = 1;
//        *Ks = (1, 2, 1);
//       // cout << Ks[1] << endl;
//        Ns[0] = 76.470588;

    }
    void getLineNum(string s)
    {
        ifstream infile(s.c_str());
        string tmp;
        while (getline(infile, tmp))
        {
            if (tmp[0] == 'v')
                if (tmp[1] == 'n') vn_num++;
                else if (tmp[1] == 't') vt_num++;
                else v_num++;
            else if (tmp[0] == 'f') f_num++;
            else if (tmp[0] == 'm') m_num++;

        }

        cout << v_num << " " << f_num << " " << vn_num << endl;


        //LoadMaterial("gun.mtl");

    }
    int readfile(string addrstr) //将文件内容读到数组中去

    {

        int i;

        vArr = new GLfloat*[v_num];

        for (i = 0; i < v_num; i++)
            vArr[i] = new GLfloat[3];

        vnArr = new GLfloat*[vn_num];

        for (i = 0; i < vn_num; i++)
            vnArr[i] = new GLfloat[3];

        vtArr = new GLfloat*[vt_num];

        for (i = 0; i < vt_num; i++)
            vtArr[i] = new GLfloat[3];

        fvArr = new int*[f_num];

        fnArr = new int*[f_num];

        ftArr = new int*[f_num];

        MArr = new string [f_num];

        for (i = 0; i < f_num; i++)

        {
            ftArr[i] = new int[3];
            fvArr[i] = new int[3];
            fnArr[i] = new int[3];

        }

        ifstream infile(addrstr.c_str());

        string sline;//每一行

        int ii = 0, jj = 0, kk = 0, zz = 0;

        while (getline(infile, sline))

        {
            if (sline[0] == 'v')

            {
                if (sline[1] == 'n') //vn

                {
                    istringstream sin(sline);

                    sin >> s1 >> f2 >> f3 >> f4;

                    vnArr[ii][0] = f2;

                    vnArr[ii][1] = f3;

                    vnArr[ii][2] = f4;

                    ii++;

                }

                else if (sline[1] == 't')
                {
                    istringstream sin(sline);
                    sin >> s1 >> f2 >> f3 >> f4;
                    vtArr[zz][0] = f2;
                    vtArr[zz][1] = f3;
                    vtArr[zz][2] = f4;
                    zz++;

                }
                else

                {

                    istringstream sin(sline);

                    sin >> s1 >> f2 >> f3 >> f4;

                    vArr[jj][0] = f2;

                    vArr[jj][1] = f3;

                    vArr[jj][2] = f4;

                    jj++;

                }

            }
            else if (sline[0] == 'f') //读取面

            {
                MArr[kk] = current_material;
                istringstream in(sline);

                GLfloat a;

                in >> s1; //去掉前缀f

                int i, k;

                s1 = "";

                in >> s1;

                for (i = 0; s1 != ""; i++)

                {

                    //in >> s1;
                    //if (s1=="") continue;
                    // cout << s1 << endl; //取得顶点索引和法线索引

                    a = 0;

                    for (k = 0; s1[k] != '/'; k++)

                        a = a * 10 + (s1[k] - 48);

                    fvArr[kk][i] = a;

                    a = 0;

                    for (k = k + 1; s1[k] != '/'; k++)

                        a = a * 10 + (s1[k] - 48);

                    ftArr[kk][i] = a;

                    a = 0;


                    for (k = k + 1; s1[k]; k++)
                        a = a * 10 + (s1[k] - 48);;

                    fnArr[kk][i] = a;

                    s1 = "";

                    in >> s1;

                }
                fvArr[kk][i] = NULL;
                kk++;

            }
            else if (sline[0] == 'm')
            {
                //去读材质包啦！
                istringstream in(sline);
                string tmp;
                in >> tmp;
                in >> tmp;
                LoadMaterial(tmp);
            }
            else if (sline[0] == 'u') //设定材质
            {
                istringstream in(sline);
                string tmp;
                in >> tmp;
                in >> tmp;
                current_material = tmp;
            }
        }
        infile.close();
        current_material = "";
        return 0;

    }
    void output_file()
    {
        cout << "num of vertice: " << v_num << endl;
        for (int i = 0; i < v_num; i++)
            cout << vArr[i][0] << " " << vArr[i][1] << " " << vArr[i][2] << endl;
        cout << "num of faces: " << f_num << endl;
        for (int i = 0; i < f_num; i++)
            cout << fvArr[i][0] << " " << fvArr[i][1] << " " << fvArr[i][2] << endl;
        cout << "num of vn: " << vn_num << endl;
        for (int i = 0; i < vn_num; i++)
            cout << vnArr[i][0] << " " << vnArr[i][1] << " " << vnArr[i][2] << endl;
    }

};

#endif // OBJ_H_INCLUDED
