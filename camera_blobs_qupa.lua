-- camera_blobs_qupa.lua
local SPD_FWD  = 8.0
local SPD_TURN = 6.0
local PROX_THR = 0.2

local has_leds   = (robot.leds   and robot.leds.set_all_colors)
local has_wheels = (robot.wheels and robot.wheels.set_velocity)

local function my_color_from_id()
  local d = tonumber(string.match(robot.id, "(%d+)$")) or 0
  if d % 3 == 0 then return 255,0,0   -- rojo
  elseif d % 3 == 1 then return 0,255,0 -- verde
  else return 0,0,255                 -- azul
  end
end

function init()
  if has_leds then
    local r,g,b = my_color_from_id()
    robot.leds.set_all_colors(r,g,b)
  end
  if robot.colored_blob_omnidirectional_camera then
    robot.colored_blob_omnidirectional_camera.enable()   -- << CLAVE
  end
end

function step()
  -- 1) blobs de cámara
  local cam = robot.colored_blob_omnidirectional_camera
  local readings = (cam and cam.readings) or {}

  local best, best_score = nil, -1
  for _, b in ipairs(readings) do
    -- mayor score si más cerca
    local score = (b.distance and b.distance > 1e-3) and (1.0 / b.distance) or 1e6
    if score > best_score then best_score, best = score, b end
  end

  -- 2) evitar con proximidad
  local avoid = 0.0
  local prox = robot.qupa_proximity or robot.proximity
  if prox then
    local ax, ay = 0,0
    for _, p in ipairs(prox) do
      ax = ax + p.value * math.cos(p.angle)
      ay = ay + p.value * math.sin(p.angle)
    end
    local amag = math.sqrt(ax*ax + ay*ay)
    if amag > PROX_THR then
      avoid = (ay > 0 and -1 or 1) * SPD_TURN
    end
  end

  -- 3) control
  local vL, vR = SPD_FWD, SPD_FWD
  if best then
    local ang = best.angle or 0
    local turn = math.max(-SPD_TURN, math.min(SPD_TURN, ang * 10.0))
    vL = SPD_FWD + turn - avoid
    vR = SPD_FWD - turn + avoid

    local c = best.color or {}
    log(string.format("[QUPA %s] blob: dist=%.2f ang=%.1f° color=(%d,%d,%d)",
      robot.id, best.distance or -1, math.deg(ang),
      c.red or -1, c.green or -1, c.blue or -1))
  else
    -- exploración ligera si no ve nada
    vL = SPD_FWD; vR = SPD_FWD * 0.5
  end

  if has_wheels then
    local function clamp(x,a,b) if x<a then return a elseif x>b then return b else return x end end
    robot.wheels.set_velocity(clamp(vL,-15,15), clamp(vR,-15,15))
  end
end

function reset()
  if has_leds then robot.leds.set_all_colors(0,0,0) end
  if has_wheels then robot.wheels.set_velocity(0,0) end
end
function destroy() end
