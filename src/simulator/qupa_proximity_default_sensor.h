/**
 * @file <argos3/plugins/robots/qupa/simulator/qupa_proximity_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef QUPA_PROXIMITY_DEFAULT_SENSOR_H
#define QUPA_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CQupaProximityDefaultSensor;
}

#include "../control_interface/ci_qupa_proximity_sensor.h"
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CQupaProximityDefaultSensor : public CCI_QupaProximitySensor,
                                          public CSimulatedSensor {

   public:

      CQupaProximityDefaultSensor();

      virtual ~CQupaProximityDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

      virtual void Enable();

      virtual void Disable();



   private:

      CProximityDefaultSensor* m_pcProximityImpl;

   };

}

#endif
