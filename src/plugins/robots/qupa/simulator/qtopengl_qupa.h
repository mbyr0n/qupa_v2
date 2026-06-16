#ifndef QTOPENGL_QUPA_H
#define QTOPENGL_QUPA_H

namespace argos {
   class CQupaEntity;
}
#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_obj_model.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace argos {

   class CQTOpenGLQupa {

   public:

      CQTOpenGLQupa();

      virtual ~CQTOpenGLQupa();

      virtual void Draw(CQupaEntity& c_entity);

   private:
      /**
       * @brief Dibuja los LEDs de la entidad del qupa.
       */
      void DrawLEDs(CQupaEntity& c_entity);

      /**
       * @brief Dibuja los tags (AprilTag) de la entidad.
       */
      void DrawTag(CQupaEntity& c_entity);

      /* Display list para un único LED (una esfera pequeña) */
      GLuint m_unLEDList;

      /** Textura 2D para el tag checkerboard */
      GLuint m_unTagTexture;

     };
}

#endif
