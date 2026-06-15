#include "qtopengl_qupa.h"
#include "qupa_entity.h"

#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/datatypes/color.h>

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

#include <QOpenGLContext>

// GLU a través de QT u otra vía, necesario para gluSphere
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

namespace argos {

/****************************************/
/****************************************/

CQTOpenGLObjModel CQTOpenGLQupa::m_cModel("qupa.obj");

/****************************************/
/****************************************/

CQTOpenGLQupa::CQTOpenGLQupa() {
    // Creamos la display list para una esfera de LED
    m_unLEDList = glGenLists(1);
    glNewList(m_unLEDList, GL_COMPILE);
    // Dibuja una esfera de radio x recomendao 0.00x-0.02f para los LEDs
    // la resolucion viene dada por los ultimos dos parametros (slices y stacks), 10 es un valor razonable para una esfera pequeña
    GLUquadric* pcQuadric = gluNewQuadric();
    gluSphere(pcQuadric, 0.015f, 32, 32);
    gluDeleteQuadric(pcQuadric);
    glEndList();
}

/****************************************/
/****************************************/

CQTOpenGLQupa::~CQTOpenGLQupa() {
    if(QOpenGLContext::currentContext() != NULL) {
        glDeleteLists(m_unLEDList, 1);
    }
}

/****************************************/
/****************************************/

void CQTOpenGLQupa::Draw(CQupaEntity& c_entity) {
    /* Agrega una luz de relleno desde atrás-izquierda para revelar geometría
     * en las caras opuestas a la luz principal de ARGoS (GL_LIGHT0).
     * GL_LIGHTING_BIT guarda/restaura todo el estado de luces. */
    glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);
    {
        GLfloat pfAmbient[]  = { 0.15f, 0.15f, 0.15f, 1.0f };
        GLfloat pfDiffuse[]  = { 0.30f, 0.30f, 0.30f, 1.0f };
        GLfloat pfPosition[] = { -30.0f, -30.0f, 10.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_AMBIENT,  pfAmbient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  pfDiffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, pfPosition);
        glEnable(GL_LIGHT1);
    }

    glPushMatrix();

    glScalef(0.23f, 0.23f, 0.23f);
    glTranslatef(-0.01f / 0.23f, -0.005f / 0.23f, 0.0f);

    glEnable(GL_NORMALIZE);
    m_cModel.Draw();
    glDisable(GL_NORMALIZE);

    glPopMatrix();

    DrawLEDs(c_entity);
    glPopAttrib();
}

/****************************************/
/****************************************/

void CQTOpenGLQupa::DrawLEDs(CQupaEntity& c_entity) {
    // Obtiene la entidad equipada con LEDs
    CLEDEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();
    const GLboolean bLightingWasEnabled = glIsEnabled(GL_LIGHTING);

    // Deshabilita la iluminación para que los colores de los LEDs se muestren puros
    glDisable(GL_LIGHTING);

    // Itera sobre los LEDs y los dibuja
    for (UInt32 i = 0; i < cLEDEquippedEntity.GetLEDs().size(); ++i) {
        // Guarda la matriz de transformación actual
        glPushMatrix();
        
        // Obtiene el color del LED
        const CColor& cColor = cLEDEquippedEntity.GetLED(i).GetColor();
        
        // Obtiene la posición del LED
        const CVector3& cOffset = cLEDEquippedEntity.GetLEDOffset(i);
        
        // Establece el color del LED
        glColor3ub(cColor.GetRed(), cColor.GetGreen(), cColor.GetBlue());

        // Mueve el sistema de coordenadas a la posición del LED
        glTranslatef(cOffset.GetX(), cOffset.GetY(), cOffset.GetZ());
        
        // Dibuja el LED usando la display list
        glCallList(m_unLEDList);

        // Restaura la matriz de transformación
        glPopMatrix();
    }
    
    // Restaura el estado de iluminación del llamador
    if(bLightingWasEnabled == GL_TRUE) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

class CQTOpenGLOperationDrawQupaNormal : public CQTOpenGLOperationDrawNormal {
public:
    void ApplyTo(CQTOpenGLWidget& c_visualization,
                 CQupaEntity& c_entity) {
        static CQTOpenGLQupa m_cModel;
        c_visualization.DrawRays(c_entity.GetControllableEntity());
        c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
        m_cModel.Draw(c_entity);
    }
};

class CQTOpenGLOperationDrawQupaSelected : public CQTOpenGLOperationDrawSelected {
public:
    void ApplyTo(CQTOpenGLWidget& c_visualization,
                 CQupaEntity& c_entity) {
        c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
    }
};

REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawQupaNormal, CQupaEntity);
REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawQupaSelected, CQupaEntity);

} // namespace argos
