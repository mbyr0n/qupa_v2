#ifndef QTOPENGL_FOOTBOT_H
#define QTOPENGL_FOOTBOT_H

namespace argos {
   class CFootBotEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLFootBot {

   public:
      CQTOpenGLFootBot();
      virtual ~CQTOpenGLFootBot();
      virtual void Draw(CFootBotEntity& c_entity);

   private:
      void Render();

   private:
      /* Display list para el cuerpo del robot */
      GLuint m_unBodyList;
   };
}

#endif