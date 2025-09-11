#include "qtopengl_qupa.h"
#include "qupa_entity.h"

#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/datatypes/color.h>

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

// GLU a través de QT u otra vía, necesario para gluSphere
#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif

#include "qupaMTL.h"
#include "qupaOBJ.h"

namespace argos {

/****************************************/
/****************************************/

CQTOpenGLQupa::CQTOpenGLQupa() {
    // Creamos la display list para el cuerpo del robot
    m_unBodyList = glGenLists(1);
    glNewList(m_unBodyList, GL_COMPILE);
    Render();
    glEndList();

    // Creamos la display list para una esfera de LED
    m_unLEDList = glGenLists(1);
    glNewList(m_unLEDList, GL_COMPILE);
    // Dibuja una esfera de radio 0.01
    GLUquadric* pcQuadric = gluNewQuadric();
    gluSphere(pcQuadric, 0.02, 10, 10);
    gluDeleteQuadric(pcQuadric);
    glEndList();
}

/****************************************/
/****************************************/

CQTOpenGLQupa::~CQTOpenGLQupa() {
    glDeleteLists(m_unBodyList, 1);
    glDeleteLists(m_unLEDList, 1);
}

/****************************************/
/****************************************/

void CQTOpenGLQupa::Draw(CQupaEntity& c_entity) {
    // Dibuja el cuerpo del robot
    glCallList(m_unBodyList);
    // Dibuja los LEDs
    DrawLEDs(c_entity);
}

/****************************************/
/****************************************/

void CQTOpenGLQupa::DrawLEDs(CQupaEntity& c_entity) {
    // Obtiene la entidad equipada con LEDs
    CLEDEquippedEntity& cLEDEquippedEntity = c_entity.GetLEDEquippedEntity();

    // Deshabilita la iluminación para que los colores de los LEDs se muestren puros
    glDisable(GL_LIGHTING);

    // Itera sobre los LEDs y los dibuja
    for (UInt32 i = 0; i < cLEDEquippedEntity.GetLEDs().size(); ++i) {
        // Guarda la matriz de transformación actual
        glPushMatrix();
        
        // Obtiene el color del LED (esto estaba bien)
        const CColor& cColor = cLEDEquippedEntity.GetLED(i).GetColor();
        
        // Obtiene la posición del LED (ESTA ES LA LÍNEA CORREGIDA)
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
    
    // Vuelve a habilitar la iluminación
    glEnable(GL_LIGHTING);
}

/****************************************/
/****************************************/

void CQTOpenGLQupa::Render() {

    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.3f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);


    glVertexPointer(3, GL_FLOAT, 0, &qupaOBJVerts[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &qupaOBJTexCoords[0]);
    glNormalPointer(GL_FLOAT, 0, qupaOBJNormals);

    for (int i = 0; i < qupaMTLNumMaterials; i++) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qupaMTLAmbient[i]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qupaMTLDiffuse[i]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qupaMTLSpecular[i]);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, qupaMTLExponent[i]);
        glDrawArrays(GL_TRIANGLES, qupaMTLFirst[i], qupaMTLCount[i]);
    }
    // -----------------------------------------------------------

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // <<< CAMBIO AÑADIDO: Restaura la matriz de transformación a su estado original.
    glPopMatrix();
}

/****************************************/
/****************************************/

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