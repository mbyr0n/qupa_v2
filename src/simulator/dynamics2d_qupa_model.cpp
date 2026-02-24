/**
 * @file <argos3/plugins/robots/qupa/simulator/dynamics2d_qupa_model.cpp>
 *
 * @author Jose Santos
 * @author Gabriel Mauricio Madroñero Pachajoa
 */

#include "dynamics2d_qupa_model.h"
#include "qupa_turret_entity.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {

   /* Constantes de control (Innecesarias ahora, pero se dejan para no romper el header) */
   static const Real PD_P_CONSTANT = 0.4;
   static const Real PD_D_CONSTANT = 0.2;

   /* EL CULPABLE: El radio debe ser 0.15f para que el disco físico 
      coincida con el visual de 15cm de radio */
   static const Real QUPA_RADIUS                   = 0.15f; 
   static const Real QUPA_INTERWHEEL_DISTANCE      = 0.14f;
   static const Real QUPA_HEIGHT                   = 0.146899733f;

   /* FUERZA: 30f es suficiente para mover 5kg con fricción */
   static const Real QUPA_MAX_FORCE                = 30.f;
   static const Real QUPA_MAX_TORQUE               = 150.f;

   enum QUPA_WHEELS {
      QUPA_LEFT_WHEEL = 0,
      QUPA_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DQupaModel::CDynamics2DQupaModel(CDynamics2DEngine& c_engine,
                                                    CQupaEntity& c_entity) :
      CDynamics2DMultiBodyObjectModel(c_engine, c_entity),
      m_cQupaEntity(c_entity),
      m_cWheeledEntity(m_cQupaEntity.GetWheeledEntity()),
      m_cGripperEntity(c_entity.GetGripperEquippedEntity()),
      m_cDiffSteering(c_engine,
                      QUPA_MAX_FORCE,
                      QUPA_MAX_TORQUE,
                      QUPA_INTERWHEEL_DISTANCE,
                      c_entity.GetConfigurationNode()),
      m_pcGripper(nullptr),
      m_pcGrippable(nullptr),
      m_fMass(5.0f), // Masa robusta
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()),
      m_unLastTurretMode(m_cQupaEntity.GetTurretEntity().GetMode()) {

      /* Solo registramos el ancla de origen. 
         Comentamos las demás para evitar que el motor de física las use como colisionadores */
      RegisterAnchorMethod<CDynamics2DQupaModel>(
         GetEmbodiedEntity().GetOriginAnchor(),
         &CDynamics2DQupaModel::UpdateOriginAnchor);

      /* CREACIÓN DEL CUERPO ÚNICO */
      m_ptActualBaseBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(m_fMass,
                                  cpMomentForCircle(m_fMass,
                                                    0.0f,
                                                    QUPA_RADIUS, // USAR EL RADIO REAL, NO EL DOBLE
                                                    cpvzero)));
      
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      m_ptActualBaseBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(m_ptActualBaseBody, cZAngle.GetValue());

      /* FORMA FÍSICA (Shape) */
      m_ptBaseShape =
         cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                         cpCircleShapeNew(m_ptActualBaseBody,
                                          QUPA_RADIUS,
                                          cpvzero));
      
      m_ptBaseShape->e = 0.0; // Sin rebote
      m_ptBaseShape->u = 0.5; // Fricción moderada (para que resbalen un poco al tocarse)

      m_pcGrippable = new CDynamics2DGrippable(GetEmbodiedEntity(), m_ptBaseShape);
      m_cDiffSteering.AttachTo(m_ptActualBaseBody);

      /* AGREGAR CUERPO PRINCIPAL */
      AddBody(m_ptActualBaseBody, cpvzero, 0, QUPA_HEIGHT);

      /* =====================================================================
         LIMPIEZA RADICAL: COMENTAMOS EL CUERPO DEL GRIPPER Y CONSTRAINTS
         Aquí es donde vivía el "fantasma" que empujaba en el video.
         ===================================================================== */
      /*
      m_ptActualGripperBody = ...
      m_ptBaseGripperLinearMotion = ...
      m_ptBaseGripperAngularMotion = ...
      */
   }

   CDynamics2DQupaModel::~CDynamics2DQupaModel() {
      delete m_pcGripper;
      delete m_pcGrippable;
      m_cDiffSteering.Detach();
   }

   void CDynamics2DQupaModel::MoveTo(const CVector3& c_position, const CQuaternion& c_orientation) {
      m_pcGrippable->ReleaseAll();
      CDynamics2DMultiBodyObjectModel::MoveTo(c_position, c_orientation);
   }

   void CDynamics2DQupaModel::Reset() {
      m_cDiffSteering.Reset();
      m_pcGrippable->ReleaseAll();
      CDynamics2DMultiBodyObjectModel::Reset();
   }

   void CDynamics2DQupaModel::CalculateBoundingBox() {
      /* La caja de colisión ahora depende ÚNICAMENTE del disco de 15cm */
      GetBoundingBox().MinCorner.SetX(m_ptBaseShape->bb.l);
      GetBoundingBox().MinCorner.SetY(m_ptBaseShape->bb.b);
      GetBoundingBox().MinCorner.SetZ(GetDynamics2DEngine().GetElevation());
      GetBoundingBox().MaxCorner.SetX(m_ptBaseShape->bb.r);
      GetBoundingBox().MaxCorner.SetY(m_ptBaseShape->bb.t);
      GetBoundingBox().MaxCorner.SetZ(GetDynamics2DEngine().GetElevation() + QUPA_HEIGHT);
   }

   void CDynamics2DQupaModel::UpdateFromEntityStatus() {
      if((m_fCurrentWheelVelocity[QUPA_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[QUPA_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[QUPA_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[QUPA_RIGHT_WHEEL]);
      }
      else {
         m_cDiffSteering.Reset();
      }
      /* Lógica de torreta eliminada para estabilidad física total */
   }

   /* Métodos vacíos para cumplir con la interfaz sin generar peso físico */
   void CDynamics2DQupaModel::TurretPassiveToActive() {}
   void CDynamics2DQupaModel::TurretActiveToPassive() {}
   void CDynamics2DQupaModel::UpdateTurretAnchor(SAnchor& s_anchor) {}
   void CDynamics2DQupaModel::UpdatePerspectiveCameraAnchor(SAnchor& s_anchor) {}

   void CDynamics2DQupaModel::UpdateOriginAnchor(SAnchor& s_anchor) {
      s_anchor.Position.SetX(m_ptActualBaseBody->p.x);
      s_anchor.Position.SetY(m_ptActualBaseBody->p.y);
      s_anchor.Orientation.FromAngleAxis(CRadians(m_ptActualBaseBody->a), CVector3::Z);
   }

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CQupaEntity, CDynamics2DQupaModel);
}