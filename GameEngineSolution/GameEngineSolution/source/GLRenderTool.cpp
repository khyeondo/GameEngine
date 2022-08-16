
#include "../header/GLRenderTool.h"
#include "../header/WindowManager.h"
#include "../header/Transform.h"
#include "../header/Camera.h"
#include "../header/Texture.h"
#include "../header/Mesh.h"

#include "../header/glaux.h"
#include "../header/stb_image.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstring>

bool GLRenderTool::Init(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int nPixelFormat;

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cDepthBits = 32;
    pfd.cColorBits = 32;

    nPixelFormat = ChoosePixelFormat(hDC, &pfd);
    if (!nPixelFormat) return false;

    if (!SetPixelFormat(hDC, nPixelFormat, &pfd)) return false;

    DescribePixelFormat(hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    
   	HGLRC hrc;
    hrc = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hrc);
    
    glClearColor(0.4, 0.8, 0.8, 1);

    glViewport(0, 0, 
        WindowMgr::Instance()->GetWidth(), 
        WindowMgr::Instance()->GetHeight());

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);    

    return true;
}

void GLRenderTool::ProjectionPerspective()
{
    if (m_pCamera != nullptr)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(
            m_pCamera->GetFov(),
            (float)WindowMgr::Instance()->GetWidth() / 
            (float)WindowMgr::Instance()->GetHeight(),
            m_pCamera->GetNear(),
            m_pCamera->GetFar());
    }
}

void GLRenderTool::ProjectionOrtho()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -(float)WindowMgr::Instance()->GetWidth()/2.f, 
        (float)WindowMgr::Instance()->GetWidth() / 2.f,
        -(float)WindowMgr::Instance()->GetHeight() / 2.f,
        (float)WindowMgr::Instance()->GetHeight() / 2.f,
        -1.0, 
        1000.0
    );
}

void GLRenderTool::LocalToWorld(const Transform& transform)
{
    Vec3f pos = transform.GetPosition();
    Vec3f rotation = transform.GetRotation();
    Vec3f scale = transform.GetScale();

    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);	
	glScalef(scale.x, scale.y, scale.z);
    
}

void GLRenderTool::WorldToView()
{
    if (m_pCamera != nullptr)
    {
        Vec3f pos = m_pCamera->GetPosition();

        GLfloat _pos[] = { pos.x,pos.y,pos.z,1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, _pos);

		glRotatef(-m_pCamera->GetRotation().x, 1.0, 0.0, 0.0);
		glRotatef(-m_pCamera->GetRotation().y, 0.0, 1.0, 0.0);
        gluLookAt(
            pos.x, pos.y, pos.z + 1.f,
            pos.x, pos.y, pos.z,
            0.f, 1.f, 0.f);
    }    
}

void GLRenderTool::PushMatrix()
{
    glPushMatrix();
}

void GLRenderTool::PopMatrix()
{
    glPopMatrix();    
}

void GLRenderTool::StartRender()
{    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ProjectionPerspective();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLRenderTool::StartRenderUI()
{
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    ProjectionOrtho();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void GLRenderTool::EndRender()
{    
    glFlush();
    SwapBuffers(WindowMgr::Instance()->GetHDC());
}

void GLRenderTool::RenderMesh(const Mesh* pMesh, const Texture* pTexture) {    

    Vec3f* vertex = pMesh->vertex;
    Vec2f* uv = pMesh->uv;
    int* vertexIdx = pMesh->vertexTriIdx;
    int* uvIdx = pMesh->uvTriIdx;
    //Vec3i* idx = pMesh->vertexIdx;
    //glBegin(GL_QUADS);

    if (pTexture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, *((unsigned int*)(pTexture->m_pTexture)));
    }

    glBegin(GL_TRIANGLES);

    if (uv != nullptr)
    {
        for (size_t i = 0; i < pMesh->triIdxNum; i++)
        {
            //glColor3f(0.f, 0.f, 1.f);
            glTexCoord2f(uv[vertexIdx[i * 3]].x, uv[vertexIdx[i * 3]].y);
            glVertex3f(vertex[vertexIdx[i * 3]].x, vertex[vertexIdx[i * 3]].y, vertex[vertexIdx[i * 3]].z);
            //glColor3f(0.f, 1.f, 0.f);
            glTexCoord2f(uv[vertexIdx[i * 3 + 1]].x, uv[vertexIdx[i * 3 + 1]].y);
            glVertex3f(vertex[vertexIdx[i * 3 + 1]].x, vertex[vertexIdx[i * 3 + 1]].y, vertex[vertexIdx[i * 3 + 1]].z);
            //glColor3f(1.f, 0.f, 0.f);
            glTexCoord2f(uv[vertexIdx[i * 3 + 2]].x, uv[vertexIdx[i * 3 + 2]].y);
            glVertex3f(vertex[vertexIdx[i * 3 + 2]].x, vertex[vertexIdx[i * 3 + 2]].y, vertex[vertexIdx[i * 3 + 2]].z);
        }
    }
    else 
    {
        for (size_t i = 0; i < pMesh->triIdxNum; i++)
        {
            //glColor3f(0.f, 0.f, 1.f);            
            glVertex3f(vertex[vertexIdx[i * 3]].x, vertex[vertexIdx[i * 3]].y, vertex[vertexIdx[i * 3]].z);
            //glColor3f(0.f, 1.f, 0.f);            
            glVertex3f(vertex[vertexIdx[i * 3 + 1]].x, vertex[vertexIdx[i * 3 + 1]].y, vertex[vertexIdx[i * 3 + 1]].z);
            //glColor3f(1.f, 0.f, 0.f);            
            glVertex3f(vertex[vertexIdx[i * 3 + 2]].x, vertex[vertexIdx[i * 3 + 2]].y, vertex[vertexIdx[i * 3 + 2]].z);
        }
    }
    glEnd();



    if (pTexture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture->m_pTexture);
    }
    vertexIdx = pMesh->vertexQuadIdx;
    uvIdx = pMesh->uvQuadIdx;
    glBegin(GL_QUADS);
    if (uv != nullptr)
    {
        for (size_t i = 0; i < pMesh->quadIdxNum; i++)
        {
            glTexCoord2f(uv[uvIdx[i * 4]].x, uv[uvIdx[i * 4]].y);
            glVertex3f(vertex[vertexIdx[i * 4]].x, vertex[vertexIdx[i * 4]].y, vertex[vertexIdx[i * 4]].z);
            glTexCoord2f(uv[uvIdx[i * 4 + 1]].x, uv[uvIdx[i * 4 + 1]].y);
            glVertex3f(vertex[vertexIdx[i * 4 + 1]].x, vertex[vertexIdx[i * 4 + 1]].y, vertex[vertexIdx[i * 4 + 1]].z);
            glTexCoord2f(uv[uvIdx[i * 4 + 2]].x, uv[uvIdx[i * 4 + 2]].y);
            glVertex3f(vertex[vertexIdx[i * 4 + 2]].x, vertex[vertexIdx[i * 4 + 2]].y, vertex[vertexIdx[i * 4 + 2]].z);
            glTexCoord2f(uv[uvIdx[i * 4 + 3]].x, uv[uvIdx[i * 4 + 3]].y);
            glVertex3f(vertex[vertexIdx[i * 4 + 3]].x, vertex[vertexIdx[i * 4 + 3]].y, vertex[vertexIdx[i * 4 + 3]].z);
        }
    }
    else
    {
        for (size_t i = 0; i < pMesh->quadIdxNum; i++)
        {
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f(vertex[vertexIdx[i * 4]].x, vertex[vertexIdx[i * 4]].y, vertex[vertexIdx[i * 4]].z);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f(vertex[vertexIdx[i * 4 + 1]].x, vertex[vertexIdx[i * 4 + 1]].y, vertex[vertexIdx[i * 4 + 1]].z);
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(vertex[vertexIdx[i * 4 + 2]].x, vertex[vertexIdx[i * 4 + 2]].y, vertex[vertexIdx[i * 4 + 2]].z);
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f(vertex[vertexIdx[i * 4 + 3]].x, vertex[vertexIdx[i * 4 + 3]].y, vertex[vertexIdx[i * 4 + 3]].z);
        }
   }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

void GLRenderTool::RenderSkyBox(Texture *pTexture[6])
{
    glCullFace(GL_FRONT);

    if (m_pCamera != nullptr)
    {
        Vec3f pos = m_pCamera->GetPosition();
        float size = m_pCamera->GetFar() / 1.75f;

        if (pTexture[0] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture[0]->m_pTexture);

        glBegin(GL_POLYGON);        
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-size + pos.x, size + pos.y, -size + pos.z);  //À­¸é
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-size + pos.x, size + pos.y, size + pos.z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(size + pos.x, size + pos.y, size + pos.z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(size + pos.x, size + pos.y, -size + pos.z);
        glEnd();

        if(pTexture[1] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture[1]->m_pTexture);
        glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size + pos.x, -size + pos.y, -size + pos.z);  //¾Æ·§¸é
		glTexCoord2f(1.0f, 0.0f); glVertex3f(size + pos.x, -size + pos.y, -size + pos.z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(size + pos.x, -size + pos.y, size + pos.z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-size + pos.x, -size + pos.y, size + pos.z);
        glEnd();

        if (pTexture[2] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture[2]->m_pTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-size + pos.x, -size + pos.y, -size + pos.z);  //ÁÂÃø¸é
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-size + pos.x, -size + pos.y, size + pos.z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-size + pos.x, size + pos.y, size + pos.z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-size + pos.x, size + pos.y, -size + pos.z);
        glEnd();

        if (pTexture[3] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *((unsigned int*)pTexture[3]->m_pTexture));
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-size+pos.x, -size+pos.y, size+pos.z);  //¾Õ¸é
        glTexCoord2f(1.0f, 0.0f); glVertex3f(size+pos.x, -size+pos.y, size+pos.z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(size+pos.x, size+pos.y, size+pos.z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-size+pos.x, size+pos.y, size+pos.z);
        glEnd();

        if (pTexture[4] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture[4]->m_pTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(size + pos.x, -size + pos.y, -size + pos.z);  //¿ìÃø¸é
        glTexCoord2f(1.0f, 1.0f); glVertex3f(size + pos.x, size + pos.y, -size + pos.z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(size + pos.x, size + pos.y, size + pos.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(size + pos.x, -size + pos.y, size + pos.z);
        glEnd();

        if (pTexture[5] != nullptr)
            glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture[5]->m_pTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-size+pos.x, -size+pos.y, -size+pos.z);  //µÞ¸é
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-size+pos.x, size+pos.y, -size+pos.z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(size+pos.x, size+pos.y, -size+pos.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(size+pos.x, -size+pos.y, -size+pos.z);
        glEnd();
    }
        
    glBindTexture(GL_TEXTURE_2D, 0);
    glCullFace(GL_BACK);
}

void GLRenderTool::DrawTexture(const Texture* pTexture, const Vec2f& pos, unsigned int width, unsigned int height ,const Vec2f& pivot, int anchor)
{
    Vec2f anchorPos;    
    if (anchor & Anchor::LEFT)
        anchorPos.x -= WindowMgr::Instance()->GetWidth() / 2.f;
    else if (anchor & Anchor::CENTER)
        anchorPos.x = 0.f;
    else if (anchor & Anchor::RIGHT)
        anchorPos.x += WindowMgr::Instance()->GetWidth() / 2.f;

    if (anchor & Anchor::BOTTOM)
        anchorPos.y -= WindowMgr::Instance()->GetHeight() / 2.f;
    else if (anchor & Anchor::MIDDLE)
        anchorPos.y = 0.f;
    else if(anchor & Anchor::TOP)
        anchorPos.y += WindowMgr::Instance()->GetHeight() / 2.f;    

    if (pTexture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, *(unsigned int*)pTexture->m_pTexture);
    }

    glBegin(GL_POLYGON);
    //left bottom
    glTexCoord2f(0.0, 0.0);
    glVertex3f(
        pos.x - width * pivot.x + anchorPos.x,
        pos.y - height * pivot.y + anchorPos.y,
        0.0);
    //right bottom
    glTexCoord2f(1.0, 0.0);
    glVertex3f(
        pos.x + width * (1.f - pivot.x) + anchorPos.x,
        pos.y - height * pivot.y + anchorPos.y,
        0.0);
    //right top
    glTexCoord2f(1.0, 1.0);
    glVertex3f(
        pos.x + width * (1.f - pivot.x) + anchorPos.x,
        pos.y + height * (1.f - pivot.y) + anchorPos.y,
        0.0);
    //left top
    glTexCoord2f(0.0, 1.0);
    glVertex3f(
        pos.x - width * pivot.x + anchorPos.x,
        pos.y + height * (1.f - pivot.y) + anchorPos.y,
        0.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLRenderTool::Reshape(int w, int h)
{
    glViewport(0, 0, w, h);    
}

bool GLRenderTool::LoadTexture(const std::wstring& path, Texture* pOutTexture)
{    
    std::string path_a;
    path_a.assign(path.begin(), path.end());

    int width, height, nrChannels;
    unsigned char* data = nullptr;

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path_a.c_str(), &width, &height, &nrChannels, 0);

    if (data == nullptr)
        return false;

    unsigned int* texture = new unsigned int();

    glGenTextures(1, texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //if(path.back() == L'g') //.png
    if(wcsstr(path.c_str(), L".png"))
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    pOutTexture->m_pTexture = texture;
    pOutTexture->width = width;
    pOutTexture->height = height;

    stbi_image_free(data);

    return true;
}

void GLRenderTool::SetCamera(Camera* pCamera)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    RenderTool::SetCamera(pCamera);
    gluPerspective(
        pCamera->GetFov(),
        (float)WindowMgr::Instance()->GetWidth() /
        (float)WindowMgr::Instance()->GetHeight(),
        pCamera->GetNear(), pCamera->GetFar());
}