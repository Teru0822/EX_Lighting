#include "func.h"
#include "GL/freeglut.h"
#include <stdio.h>
#include "stb_image.h"


GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // テクスチャパラメータの設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // テクスチャ画像をバインドする
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // 手動でミップマップを生成する
        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}
bool collisionCheck(Position currentPosition, Position targetPosition,Position objPosition ,float rusius)
{
    //プレイヤー座標→焦点ベクトル方向に線分を伸ばし、かかったかどうかを判断。
    /*
        必要なもの
        ・現在地
        ・焦点

        ・オブジェクトの座標
        ・オブジェクトの大きさ（半径）


        線分がオブジェクトの領域(球体)に入った時trueを返す
    */
    //10等分
    for (int i = 0; i < 10; i++)
    {   
        double CPX = currentPosition.x + (targetPosition.x - currentPosition.x) * i / 10.0;
        double CPY = currentPosition.y + (targetPosition.y - currentPosition.y) * i / 10.0;
        double CPZ = currentPosition.z + (targetPosition.z - currentPosition.z) * i / 10.0;
        if (CPX > objPosition.x - rusius && CPX < objPosition.x + rusius && CPY > objPosition.y - rusius && CPY < objPosition.y + rusius && CPZ > objPosition.z - rusius && CPZ < objPosition.z + rusius)
        {
            return true;
        }
    }
    return false;
}

struct rangeCoordinate
{
    float minX;
    float minY;
    float minZ;
    float MaxX;
    float MaxY;
    float MaxZ;
};


namespace test
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;
}
namespace test2
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;
}
namespace test3
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;

}
namespace rengaTile
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;
}
namespace ground
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;

}
namespace back
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;

}
namespace top
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;

}
namespace weapon
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;

}

namespace ball
{
    GLfloat vertex[ARRAY_MAX];//頂点座標を格納
    GLfloat flat[ARRAY_MAX];//頂点座標を格納
    GLfloat sortedVertex[ARRAY_MAX];
    GLfloat sortedFlat[ARRAY_MAX];
    int index[ARRAY_MAX];
    int vertexDataSize = 0;
    int flatDataSize = 0;
    int indexSize = 0;
}

void makeTest(float r, float g, float b)
{
    //vertexの入れ替えを行う
    for (int i = 0; i < test::indexSize * 3; i++)
    {
        test::sortedVertex[i * 3] = test::vertex[3 * test::index[i]];
        test::sortedVertex[i * 3 + 1] = test::vertex[3 * test::index[i] + 1];
        test::sortedVertex[i * 3 + 2] = test::vertex[3 * test::index[i] + 2];

    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, test::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, test::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < test::indexSize; i++) 
    {
        glBegin(GL_TRIANGLES);
        glNormal3f(test::flat[i * 3], test::flat[i * 3 + 1], test::flat[i * 3 + 2]);
        glVertex3f(test::sortedVertex[i * 9], test::sortedVertex[i * 9 + 1], test::sortedVertex[i * 9 + 2]);
        glVertex3f(test::sortedVertex[i * 9 + 3], test::sortedVertex[i * 9 + 4], test::sortedVertex[i * 9 + 5]);
        glVertex3f(test::sortedVertex[i * 9 + 6], test::sortedVertex[i * 9 + 7], test::sortedVertex[i * 9 + 8]);
        glEnd();
    }
}
void make2Test(float r, float g, float b)//3頂点
{
    //vertexの入れ替えを行う
    for (int i = 0; i < test2::indexSize * 3; i++)
    {
        test2::sortedVertex[i * 3] = test2::vertex[3 * test2::index[i]];
        test2::sortedVertex[i * 3 + 1] = test2::vertex[3 * test2::index[i] + 1];
        test2::sortedVertex[i * 3 + 2] = test2::vertex[3 * test2::index[i] + 2];

    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, test2::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, test2::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < test2::indexSize; i++)
    {
        glBegin(GL_TRIANGLES);
        glNormal3f(test2::flat[i * 3], test2::flat[i * 3 + 1], test2::flat[i * 3 + 2]);
        glVertex3f(test2::sortedVertex[i * 9], test2::sortedVertex[i * 9 + 1], test2::sortedVertex[i * 9 + 2]);
        glVertex3f(test2::sortedVertex[i * 9 + 3], test2::sortedVertex[i * 9 + 4], test2::sortedVertex[i * 9 + 5]);
        glVertex3f(test2::sortedVertex[i * 9 + 6], test2::sortedVertex[i * 9 + 7], test2::sortedVertex[i * 9 + 8]);
        glEnd();
    }
}

void make3Test(float r, float g, float b, GLuint textureID)//4頂点テクスチャあり
{
    //vertexの入れ替えを行う
    for (int i = 0; i < test3::indexSize * 4 ; i++)
    {
        test3::sortedVertex[i * 3] = test3::vertex[3 * test3::index[i]];
        test3::sortedVertex[(i * 3) + 1] = test3::vertex[(3 * test3::index[i]) + 1];
        test3::sortedVertex[(i * 3) + 2] = test3::vertex[(3 * test3::index[i]) + 2];

    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, test3::sortedVertex);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glNormalPointer(GL_FLOAT, 0, test3::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < test3::indexSize; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(test3::flat[i * 3], test3::flat[i * 3 + 1], test3::flat[i * 3 + 2]);
        glTexCoord2d(0.0, 1.0);
        glVertex3f(test3::sortedVertex[i * 12], test3::sortedVertex[i * 12 + 1], test3::sortedVertex[i * 12 + 2]);
        glTexCoord2d(1.0, 1.0);
        glVertex3f(test3::sortedVertex[i * 12 + 3], test3::sortedVertex[i * 12 + 4], test3::sortedVertex[i * 12 + 5]);
        glTexCoord2d(1.0, 0.0);
        glVertex3f(test3::sortedVertex[i * 12 + 6], test3::sortedVertex[i * 12 + 7], test3::sortedVertex[i * 12 + 8]);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(test3::sortedVertex[i * 12 + 9], test3::sortedVertex[i * 12 + 10], test3::sortedVertex[i * 12 + 11]);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}
void make3Test(float r, float g, float b)//4頂点テクスチャなし
{
    //vertexの入れ替えを行う
    for (int i = 0; i < test3::indexSize * 4; i++)
    {
        test3::sortedVertex[i * 3] = test3::vertex[3 * test3::index[i]];
        test3::sortedVertex[(i * 3) + 1] = test3::vertex[(3 * test3::index[i]) + 1];
        test3::sortedVertex[(i * 3) + 2] = test3::vertex[(3 * test3::index[i]) + 2];
    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, test3::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, test3::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < test3::indexSize; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(test3::flat[i * 3], test3::flat[i * 3 + 1], test3::flat[i * 3 + 2]);
        glVertex3f(test3::sortedVertex[i * 12], test3::sortedVertex[i * 12 + 1], test3::sortedVertex[i * 12 + 2]);
        glVertex3f(test3::sortedVertex[i * 12 + 3], test3::sortedVertex[i * 12 + 4], test3::sortedVertex[i * 12 + 5]);
        glVertex3f(test3::sortedVertex[i * 12 + 6], test3::sortedVertex[i * 12 + 7], test3::sortedVertex[i * 12 + 8]);
        glVertex3f(test3::sortedVertex[i * 12 + 9], test3::sortedVertex[i * 12 + 10], test3::sortedVertex[i * 12 + 11]);
        glEnd();
    }
}

void makeGround(float r, float g, float b, GLuint textureID)//4頂点テクスチャあり
{
    //vertexの入れ替えを行う
    for (int i = 0; i < ground::indexSize * 4; i++)
    {
        ground::sortedVertex[i * 3] = ground::vertex[3 * ground::index[i]];
        ground::sortedVertex[(i * 3) + 1] = ground::vertex[(3 * ground::index[i]) + 1];
        ground::sortedVertex[(i * 3) + 2] = ground::vertex[(3 * ground::index[i]) + 2];

    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, ground::sortedVertex);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glNormalPointer(GL_FLOAT, 0, ground::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < ground::indexSize; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(ground::flat[i * 3], ground::flat[i * 3 + 1], ground::flat[i * 3 + 2]);
        glTexCoord2d(0.0, 1.0);
        glVertex3f(ground::sortedVertex[i * 12], ground::sortedVertex[i * 12 + 1], ground::sortedVertex[i * 12 + 2]);
        glTexCoord2d(1.0, 1.0);
        glVertex3f(ground::sortedVertex[i * 12 + 3], ground::sortedVertex[i * 12 + 4], ground::sortedVertex[i * 12 + 5]);
        glTexCoord2d(1.0, 0.0);
        glVertex3f(ground::sortedVertex[i * 12 + 6], ground::sortedVertex[i * 12 + 7], ground::sortedVertex[i * 12 + 8]);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(ground::sortedVertex[i * 12 + 9], ground::sortedVertex[i * 12 + 10], ground::sortedVertex[i * 12 + 11]);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}
void makeRengaTile(float r, float g, float b, GLuint textureID)//4頂点テクスチャあり
{
    //vertexの入れ替えを行う
    for (int i = 0; i < rengaTile::indexSize * 4; i++)
    {
        rengaTile::sortedVertex[i * 3] = rengaTile::vertex[3 * rengaTile::index[i]];
        rengaTile::sortedVertex[(i * 3) + 1] = rengaTile::vertex[(3 * rengaTile::index[i]) + 1];
        rengaTile::sortedVertex[(i * 3) + 2] = rengaTile::vertex[(3 * rengaTile::index[i]) + 2];

    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, rengaTile::sortedVertex);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glNormalPointer(GL_FLOAT, 0, rengaTile::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < rengaTile::indexSize; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(rengaTile::flat[i * 3], rengaTile::flat[i * 3 + 1], rengaTile::flat[i * 3 + 2]);
        glTexCoord2d(0.0, 1.0);
        glVertex3f(rengaTile::sortedVertex[i * 12], rengaTile::sortedVertex[i * 12 + 1], rengaTile::sortedVertex[i * 12 + 2]);
        glTexCoord2d(1.0, 1.0);
        glVertex3f(rengaTile::sortedVertex[i * 12 + 3], rengaTile::sortedVertex[i * 12 + 4], rengaTile::sortedVertex[i * 12 + 5]);
        glTexCoord2d(1.0, 0.0);
        glVertex3f(rengaTile::sortedVertex[i * 12 + 6], rengaTile::sortedVertex[i * 12 + 7], rengaTile::sortedVertex[i * 12 + 8]);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(rengaTile::sortedVertex[i * 12 + 9], rengaTile::sortedVertex[i * 12 + 10], rengaTile::sortedVertex[i * 12 + 11]);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

}
void makeBack(float r, float g, float b)//4頂点テクスチャなし
{
    //vertexの入れ替えを行う
    for (int i = 0; i < back::indexSize * 3; i++)
    {
        back::sortedVertex[i * 3] = back::vertex[3 * back::index[i]];//x
        back::sortedVertex[(i * 3) + 1] = back::vertex[(3 * back::index[i]) + 1];//y
        back::sortedVertex[(i * 3) + 2] = back::vertex[(3 * back::index[i]) + 2];//z
    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, back::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, back::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < back::indexSize; i++)
    {
        glBegin(GL_TRIANGLES);
        glNormal3f(back::flat[i * 3] * -1.0, back::flat[i * 3 + 1]* -1.0, back::flat[i * 3 + 2] * -1.0);
        glVertex3f(back::sortedVertex[i * 9], back::sortedVertex[i * 9 + 1], back::sortedVertex[i * 9 + 2]);
        glVertex3f(back::sortedVertex[i * 9 + 3], back::sortedVertex[i * 9 + 4], back::sortedVertex[i * 9 + 5]);
        glVertex3f(back::sortedVertex[i * 9 + 6], back::sortedVertex[i * 9 + 7], back::sortedVertex[i * 9 + 8]);
        glEnd();
    }
}
void makeWeapon(float r, float g, float b)//4頂点テクスチャなし
{
    //vertexの入れ替えを行う
    for (int i = 0; i < weapon::indexSize * 4; i++)
    {
        weapon::sortedVertex[i * 3] = weapon::vertex[3 * weapon::index[i]];
        weapon::sortedVertex[(i * 3) + 1] = weapon::vertex[(3 * weapon::index[i]) + 1];
        weapon::sortedVertex[(i * 3) + 2] = weapon::vertex[(3 * weapon::index[i]) + 2];
    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, weapon::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, weapon::flat);
    glColor3f(r, g, b);

    for (int i = 0; i < weapon::indexSize; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(weapon::flat[i * 3] , weapon::flat[i * 3 + 1], weapon::flat[i * 3 + 2]);
        glVertex3f(weapon::sortedVertex[i * 12], weapon::sortedVertex[i * 12 + 1], weapon::sortedVertex[i * 12 + 2]);
        glVertex3f(weapon::sortedVertex[i * 12 + 3], weapon::sortedVertex[i * 12 + 4], weapon::sortedVertex[i * 12 + 5]);
        glVertex3f(weapon::sortedVertex[i * 12 + 6], weapon::sortedVertex[i * 12 + 7], weapon::sortedVertex[i * 12 + 8]);
        glVertex3f(weapon::sortedVertex[i * 12 + 9], weapon::sortedVertex[i * 12 + 10], weapon::sortedVertex[i * 12 + 11]);
        glEnd();
    }
}
void makeBall(float r, float g, float b,float rusius)
{
    //vertexの入れ替えを行う
    for (int i = 0; i < ball::indexSize * 3; i++)
    {
        ball::sortedVertex[i * 3] = ball::vertex[3 * ball::index[i]];
        ball::sortedVertex[i * 3 + 1] = ball::vertex[3 * ball::index[i] + 1];
        ball::sortedVertex[i * 3 + 2] = ball::vertex[3 * ball::index[i] + 2];
    }
    glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, ball::sortedVertex);
    glNormalPointer(GL_FLOAT, 0, ball::flat);
    glColor3f(r, g, b);
    rangeCoordinate ballRange;
    for (int i = 0; i < ball::indexSize; i++)
    {
        glBegin(GL_TRIANGLES);
        glNormal3f(ball::flat[i * 3], ball::flat[i * 3 + 1], ball::flat[i * 3 + 2]);
        glVertex3f(ball::sortedVertex[i * 9], ball::sortedVertex[i * 9 + 1], ball::sortedVertex[i * 9 + 2]);
        glVertex3f(ball::sortedVertex[i * 9 + 3], ball::sortedVertex[i * 9 + 4], ball::sortedVertex[i * 9 + 5]);
        glVertex3f(ball::sortedVertex[i * 9 + 6], ball::sortedVertex[i * 9 + 7], ball::sortedVertex[i * 9 + 8]);
        glEnd();
      
    }
    //このボールレンジの中央値をオブジェクトの中心地とする
}



void readPoints()
{
    FILE* vData, * fData, * iData, * v2Data, * f2Data, * i2Data, * v4Data, * i4Data, * f4Data, * vRengaTile, * fRengaTile, * iRengaTile, * vGround, * fGround, * iGround,
        * vBack, * fBack, * iBack, * vWeapon, * fWeapon, * iWeapon, * vBall, * fBall, * iBall;
    fopen_s(&vData, "vData.txt", "r");
    fopen_s(&fData, "fData.txt", "r");
    fopen_s(&iData, "iData.txt", "r");
    fopen_s(&v2Data, "v2Data.txt", "r");
    fopen_s(&f2Data, "f2Data.txt", "r");
    fopen_s(&i2Data, "i2Data.txt", "r");
    fopen_s(&v4Data, "v4Data.txt", "r");
    fopen_s(&f4Data, "f4Data.txt", "r");
    fopen_s(&i4Data, "i4Data.txt", "r");
    fopen_s(&vRengaTile, "vRengaTile.txt", "r");
    fopen_s(&fRengaTile, "fRengaTile.txt", "r");
    fopen_s(&iRengaTile, "iRengaTile.txt", "r");
    fopen_s(&vGround, "vGround.txt", "r");
    fopen_s(&fGround, "fGround.txt", "r");
    fopen_s(&iGround, "iGround.txt", "r");
    fopen_s(&vBack, "vBack.txt", "r");
    fopen_s(&fBack, "fBack.txt", "r");
    fopen_s(&iBack, "iBack.txt", "r");
    fopen_s(&vWeapon, "vWeapon.txt", "r");
    fopen_s(&fWeapon, "fWeapon.txt", "r");
    fopen_s(&iWeapon, "iWeapon.txt", "r");
    fopen_s(&vBall, "vBall.txt", "r");
    fopen_s(&fBall, "fBall.txt", "r");
    fopen_s(&iBall, "iBall.txt", "r");

    if ((vData == NULL) || (fData == NULL) || (iData == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vData, "%f, %f, %f", &test::vertex[test::vertexDataSize * 3], &test::vertex[test::vertexDataSize * 3 + 1], &test::vertex[test::vertexDataSize * 3 + 2]) != EOF)
            test::vertexDataSize++;
        while (fscanf_s(fData, "%f, %f, %f", &test::flat[test::flatDataSize * 3], &test::flat[test::flatDataSize * 3 + 1], &test::flat[test::flatDataSize * 3 + 2]) != EOF)
            test::flatDataSize++;
        while (fscanf_s(iData, "%d, %d, %d", &test::index[test::indexSize * 3], &test::index[test::indexSize * 3 + 1], &test::index[test::indexSize * 3 + 2]) != EOF)
            test::indexSize++;//面の数

    }
    if ((v2Data == NULL) || (f2Data == NULL) || (i2Data == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(v2Data, "%f, %f, %f", &test2::vertex[test2::vertexDataSize * 3], &test2::vertex[test2::vertexDataSize * 3 + 1], &test2::vertex[test2::vertexDataSize * 3 + 2]) != EOF)
            test2::vertexDataSize++;
        while (fscanf_s(f2Data, "%f, %f, %f", &test2::flat[test2::flatDataSize * 3], &test2::flat[test2::flatDataSize * 3 + 1], &test2::flat[test2::flatDataSize * 3 + 2]) != EOF)
            test2::flatDataSize++;
        while (fscanf_s(i2Data, "%d, %d, %d", &test2::index[test2::indexSize * 3], &test2::index[test2::indexSize * 3 + 1], &test2::index[test2::indexSize * 3 + 2]) != EOF)
            test2::indexSize++;//面の数

    }
    if ((v4Data == NULL) || (f4Data == NULL) || (i4Data == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(v4Data, "%f, %f, %f", &test3::vertex[test3::vertexDataSize * 3], &test3::vertex[test3::vertexDataSize * 3 + 1], &test3::vertex[test3::vertexDataSize * 3 + 2]) != EOF)
            test3::vertexDataSize++;
        while (fscanf_s(f4Data, "%f, %f, %f", &test3::flat[test3::flatDataSize * 3], &test3::flat[test3::flatDataSize * 3 + 1], &test3::flat[test3::flatDataSize * 3 + 2]) != EOF)
            test3::flatDataSize++;
        while (fscanf_s(i4Data, "%d, %d, %d, %d", &test3::index[test3::indexSize * 4], &test3::index[test3::indexSize * 4 + 1], &test3::index[test3::indexSize * 4 + 2] , &test3::index[test3::indexSize * 4 + 3]) != EOF)
            test3::indexSize++;//面の数

    }
    if ((vRengaTile == NULL) || (fRengaTile == NULL) || (iRengaTile == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vRengaTile, "%f, %f, %f", &rengaTile::vertex[rengaTile::vertexDataSize * 3], &rengaTile::vertex[rengaTile::vertexDataSize * 3 + 1], &rengaTile::vertex[rengaTile::vertexDataSize * 3 + 2]) != EOF)
            rengaTile::vertexDataSize++;
        while (fscanf_s(fRengaTile, "%f, %f, %f", &rengaTile::flat[rengaTile::flatDataSize * 3], &rengaTile::flat[rengaTile::flatDataSize * 3 + 1], &rengaTile::flat[rengaTile::flatDataSize * 3 + 2]) != EOF)
            rengaTile::flatDataSize++;
        while (fscanf_s(iRengaTile, "%d, %d, %d, %d", &rengaTile::index[rengaTile::indexSize * 4], &rengaTile::index[rengaTile::indexSize * 4 + 1], &rengaTile::index[rengaTile::indexSize * 4 + 2], &rengaTile::index[rengaTile::indexSize * 4 + 3]) != EOF)
            rengaTile::indexSize++;//面の数

    }
    if ((vGround == NULL) || (fGround == NULL) || (iGround == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vGround, "%f, %f, %f", &ground::vertex[ground::vertexDataSize * 3], &ground::vertex[ground::vertexDataSize * 3 + 1], &ground::vertex[ground::vertexDataSize * 3 + 2]) != EOF)
            ground::vertexDataSize++;
        while (fscanf_s(fGround, "%f, %f, %f", &ground::flat[ground::flatDataSize * 3], &ground::flat[ground::flatDataSize * 3 + 1], &ground::flat[ground::flatDataSize * 3 + 2]) != EOF)
            ground::flatDataSize++;
        while (fscanf_s(iGround, "%d, %d, %d, %d", &ground::index[ground::indexSize * 4], &ground::index[ground::indexSize * 4 + 1], &ground::index[ground::indexSize * 4 + 2], &ground::index[ground::indexSize * 4 + 3]) != EOF)
            ground::indexSize++;//面の数

    }
    if ((vBack == NULL) || (fBack == NULL) || (iBack == NULL))
    {
        printf("file error!!\n");
        return;

    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vBack, "%f, %f, %f", &back::vertex[back::vertexDataSize * 3], &back::vertex[back::vertexDataSize * 3 + 1], &back::vertex[back::vertexDataSize * 3 + 2]) != EOF)
            back::vertexDataSize++;
        while (fscanf_s(fBack, "%f, %f, %f", &back::flat[back::flatDataSize * 3], &back::flat[back::flatDataSize * 3 + 1], &back::flat[back::flatDataSize * 3 + 2]) != EOF)
            back::flatDataSize++;
        while (fscanf_s(iBack, "%d, %d, %d", &back::index[back::indexSize * 3], &back::index[back::indexSize * 3 + 1], &back::index[back::indexSize * 3 + 2]) != EOF)
            back::indexSize++;//面の数

    }
    if ((vWeapon == NULL) || (fWeapon == NULL) || (iWeapon == NULL))
    {
        printf("file error!!\n");
        return;
    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vWeapon, "%f, %f, %f", &weapon::vertex[weapon::vertexDataSize * 3], &weapon::vertex[weapon::vertexDataSize * 3 + 1], &weapon::vertex[weapon::vertexDataSize * 3 + 2]) != EOF)
            weapon::vertexDataSize++;
        while (fscanf_s(fWeapon, "%f, %f, %f", &weapon::flat[weapon::flatDataSize * 3], &weapon::flat[weapon::flatDataSize * 3 + 1], &weapon::flat[weapon::flatDataSize * 3 + 2]) != EOF)
            weapon::flatDataSize++;
        while (fscanf_s(iWeapon, "%d, %d, %d, %d", &weapon::index[weapon::indexSize * 4], &weapon::index[weapon::indexSize * 4 + 1], &weapon::index[weapon::indexSize * 4 + 2], &weapon::index[weapon::indexSize * 4 + 3]) != EOF)
            weapon::indexSize++;//面の数
    }
    if ((vBall == NULL) || (fBall == NULL) || (iBall == NULL))
    {
        printf("file error!!\n");
        return;
    }
    else
    {
        printf("success!!\n");

        while (fscanf_s(vBall, "%f, %f, %f", &ball::vertex[ball::vertexDataSize * 3], &ball::vertex[ball::vertexDataSize * 3 + 1], &ball::vertex[ball::vertexDataSize * 3 + 2]) != EOF)
            ball::vertexDataSize++;
        while (fscanf_s(fBall, "%f, %f, %f", &ball::flat[ball::flatDataSize * 3], &ball::flat[ball::flatDataSize * 3 + 1], &ball::flat[ball::flatDataSize * 3 + 2]) != EOF)
            ball::flatDataSize++;
        while (fscanf_s(iBall, "%d, %d, %d", &ball::index[ball::indexSize * 3], &ball::index[ball::indexSize * 3 + 1], &ball::index[ball::indexSize * 3 + 2]) != EOF)
            ball::indexSize++;//面の数
    }
}

