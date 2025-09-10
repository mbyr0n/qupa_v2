#ifndef QTOPENGL_FOOTBOT_H
#define QTOPENGL_FOOTBOT_H

namespace argos {
   class CFootBotEntity;
}

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace argos {

   class CQTOpenGLFootBot {

   public:

      CQTOpenGLFootBot();

      virtual ~CQTOpenGLFootBot();

      virtual void Draw(CFootBotEntity& c_entity);

   private:

      /**
       * @brief Renderiza el cuerpo del robot en una display list.
       */
      void Render();

      /**
       * @brief Dibuja los LEDs de la entidad del foot-bot.
       */
      void DrawLEDs(CFootBotEntity& c_entity);

   private:

      /* Display list para el cuerpo del robot */
      GLuint m_unBodyList;
      
      /* Display list para un único LED (una esfera pequeña) */
      GLuint m_unLEDList;

   };
}

#endif