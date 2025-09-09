#include "qtopengl_footbot.h"
#include "footbot_entity.h"
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_widget.h>

// --> INCLUYE LOS HEADERS DE TU MODELO .OBJ
// Asegúrate de que los nombres coincidan con tus archivos generados
#include "qupaMTL.h"
#include "qupaOBJ.h"

namespace argos {

   /****************************************/
   /****************************************/

   CQTOpenGLFootBot::CQTOpenGLFootBot() {
      // Compila el modelo 3D en una display list para un renderizado eficiente
      m_unBodyList = glGenLists(1);
      glNewList(m_unBodyList, GL_COMPILE);
      Render();
      glEndList();
   }

   /****************************************/
   /****************************************/

   CQTOpenGLFootBot::~CQTOpenGLFootBot() {
      // Libera la memoria de la display list
      glDeleteLists(m_unBodyList, 1);
   }

   /****************************************/
   /****************************************/

   // Esta es la función que dibuja tu robot en cada fotograma de la simulación
   void CQTOpenGLFootBot::Draw(CFootBotEntity& c_entity) {

      // =================================================================
      // --> INICIO DE LA MODIFICACIÓN: AJUSTE DE POSICIÓN VISUAL <--
      // =================================================================
      // Modifica estos valores para desplazar el DIBUJO de tu robot.
      // Las unidades están en metros.
      // Un valor positivo en fOffsetZ hará que el robot se dibuje más arriba.
      // Un valor positivo en fOffsetX lo moverá hacia su "derecha" local.
      // Un valor positivo en fOffsetY lo moverá hacia su "frente" local.
      
      const GLfloat fOffsetX = 0.0f;  // Desplazamiento en X (izquierda/derecha)
      const GLfloat fOffsetY = 0.0f;  // Desplazamiento en Y (adelante/atrás)
      const GLfloat fOffsetZ = 0.3f;  // Desplazamiento en Z (arriba/abajo) -> ¡PRUEBA A CAMBIAR ESTE VALOR!

      // Guardamos la matriz de transformación actual de OpenGL.
      // Esto es importante para no afectar el dibujo de otros objetos en la simulación.
      glPushMatrix();

      // Aplicamos nuestra traslación personalizada.
      // Esto mueve el sistema de coordenadas ANTES de que se dibuje tu modelo.
      glTranslatef(fOffsetX, fOffsetY, fOffsetZ);

      // Ahora llamamos a la lista que dibuja tu modelo .obj.
      // Se dibujará en la nueva posición, desplazada.
      glCallList(m_unBodyList);

      // Restauramos la matriz de transformación original que guardamos antes.
      // Esto deshace nuestro desplazamiento para que el resto de la simulación se dibuje correctamente.
      glPopMatrix();
      
      // =================================================================
      // --> FIN DE LA MODIFICACIÓN <--
      // =================================================================
   }

   /****************************************/
   /****************************************/

   // Esta función carga los datos de tu .obj y los prepara para ser dibujados
   void CQTOpenGLFootBot::Render() {
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);

      // Asegúrate de que estos nombres de variables coincidan con tus archivos .h
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

      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
   }

   /****************************************/
   /****************************************/

   /*
    * Clases "pegamento" que registran nuestro dibujador personalizado en Argos3
    * para la entidad CFootBotEntity. No es necesario modificar esto.
    */

   class CQTOpenGLOperationDrawFootBotNormal : public CQTOpenGLOperationDrawNormal {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CFootBotEntity& c_entity) {
         static CQTOpenGLFootBot m_cModel;
         /* Esta línea le dice a la visualización que aplique la transformación
            del cuerpo físico del robot (posición y rotación) */
         c_visualization.DrawEntity(c_entity.GetEmbodiedEntity());
         /* Y esta línea llama a nuestra función Draw() personalizada para dibujar el modelo */
         m_cModel.Draw(c_entity);
         /* (Opcional) Dibuja los rayos de los sensores si los tuviera */
         c_visualization.DrawRays(c_entity.GetControllableEntity());
      }
   };

   class CQTOpenGLOperationDrawFootBotSelected : public CQTOpenGLOperationDrawSelected {
   public:
      void ApplyTo(CQTOpenGLWidget& c_visualization,
                   CFootBotEntity& c_entity) {
         c_visualization.DrawBoundingBox(c_entity.GetEmbodiedEntity());
      }
   };

   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawNormal, CQTOpenGLOperationDrawFootBotNormal, CFootBotEntity);
   REGISTER_QTOPENGL_ENTITY_OPERATION(CQTOpenGLOperationDrawSelected, CQTOpenGLOperationDrawFootBotSelected, CFootBotEntity);
}