/**
 * @file <argos3/plugins/robots/qupa/simulator/qupa_turret_encoder_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "qupa_turret_encoder_default_sensor.h"
#include <argos3/core/simulator/entity/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CQupaTurretEncoderDefaultSensor::CQupaTurretEncoderDefaultSensor() :
      m_pcTurretEntity(nullptr) {}

   /****************************************/
   /****************************************/

   void CQupaTurretEncoderDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      m_pcTurretEntity = &(c_entity.GetComponent<CQupaTurretEntity>("turret"));

      /* sensor is enabled by default */
      Enable();
   }

   /****************************************/
   /****************************************/

   void CQupaTurretEncoderDefaultSensor::Update() {
      /* sensor is disabled--nothing to do */
      if (IsDisabled()) {
        return;
      }
      m_cRotation = m_pcTurretEntity->GetRotation();
   }

   /****************************************/
   /****************************************/

   void CQupaTurretEncoderDefaultSensor::Enable() {
     m_pcTurretEntity->Enable();
     CCI_Sensor::Enable();
   }

   /****************************************/
   /****************************************/

   void CQupaTurretEncoderDefaultSensor::Disable() {
     m_pcTurretEntity->Disable();
     CCI_Sensor::Disable();
   }

   /****************************************/
   /****************************************/

   void CQupaTurretEncoderDefaultSensor::Reset() {
      m_cRotation = CRadians::ZERO;
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CQupaTurretEncoderDefaultSensor,
                   "qupa_turret_encoder", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The qupa turret encoder sensor.",
                   "This sensor accesses the qupa turret encoder. For a complete\n"
                   "description of its usage, refer to the ci_qupa_turret_encoder_sensor\n"
                   "file.\n\n"

                   "This sensor is enabled by default.\n\n"

                   "REQUIRED XML CONFIGURATION\n\n"

                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <qupa_turret_encoder implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "None for the time being.\n",
                   "Usable"
      );

}
