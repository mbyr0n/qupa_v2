/**
 * @file <argos3/plugins/robots/qupa/simulator/qupa_turret_encoder_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef QUPA_TURRET_ENCODER_DEFAULT_SENSOR_H
#define QUPA_TURRET_ENCODER_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CQupaTurretEncoderDefaultSensor;
}

#include "../control_interface/ci_qupa_turret_encoder_sensor.h"
#include "qupa_turret_encoder_default_sensor.h"
#include "qupa_turret_entity.h"
#include <argos3/core/simulator/sensor.h>

namespace argos {

   class CQupaTurretEncoderDefaultSensor : public CCI_QupaTurretEncoderSensor,
                                              public CSimulatedSensor {

   public:

      CQupaTurretEncoderDefaultSensor();

      virtual ~CQupaTurretEncoderDefaultSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Update();

      virtual void Reset();

      virtual void Enable();

      virtual void Disable();

   private:

      CQupaTurretEntity* m_pcTurretEntity;

   };

}

#endif
