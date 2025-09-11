-- camera_blobs_qupa.lua (robusto)
local BASE_SPEED, TURN_GAIN, THRESHOLD = 8.0, 6.0, 0.15

local HAS = {}
local CAM
local CAM_OK = false

local function atan2(y, x)
  if math.atan2 then return math.atan2(y, x) end
  if x == 0 then return (y >= 0 and math.pi/2 or -math.pi/2) end
  local a = math.atan(y/x)
  if x < 0 then a = a + math.pi end
  return a
end

function init()
  HAS.wheels = robot.wheels and type(robot.wheels.set_velocity)=="function"
  HAS.leds   = robot.leds   and type(robot.leds.set_all_colors)=="function"

  CAM = robot.colored_blob_omnidirectional_camera or robot.omnidirectional_camera
  if CAM and type(CAM.enable)=="function" then
    CAM.enable()
    CAM_OK = true
  else
    log("WARN: omni-cam sin enable(); sigo sin cámara (no rompo).")
  end

  if HAS.leds then
    local n = tonumber(robot.id:match("(%d+)$")) or 0
    local colors={{255,0,0},{0,255,0},{0,0,255},{255,255,0},{0,255,255},{255,0,255}}
    local c=colors[(n%#colors)+1]
    robot.leds.set_all_colors(c[1],c[2],c[3])
  end
end

function step()
  -- Avoid con proximidad
  local prox = robot.qupa_proximity or robot.proximity
  local vx, vy = 0, 0
  if prox then
    for _, r in ipairs(prox) do
      vx = vx + r.value * math.cos(r.angle)
      vy = vy + r.value * math.sin(r.angle)
    end
  end
  local mag = math.sqrt(vx*vx + vy*vy)
  local ang = atan2(vy, vx)

  local vL, vR = BASE_SPEED, BASE_SPEED
  if mag > THRESHOLD then
    local turn = TURN_GAIN * (ang > 0 and -1 or 1)
    vL = BASE_SPEED + turn
    vR = BASE_SPEED - turn
    if HAS.leds then robot.leds.set_all_colors(255,0,0) end
  else
    if HAS.leds then robot.leds.set_all_colors(0,255,0) end
  end
  if HAS.wheels then
    local function clamp(x,a,b) if x<a then return a elseif x>b then return b else return x end end
    robot.wheels.set_velocity(clamp(vL,-15,15), clamp(vR,-15,15))
  end

  -- Lectura de cámara (sin reventar)
  if CAM then
    local blobsN = 0
    if type(CAM.get_reading)=="function" then
      local r = CAM.get_reading()
      if r and r.blobs then blobsN = #r.blobs end
    elseif type(CAM.blobs)=="table" then
      blobsN = #CAM.blobs
    end
    log(string.format("[id=%s] blobs=%d", robot.id, blobsN))
  end
end

function reset()
  if HAS.leds   then robot.leds.set_all_colors(0,0,0) end
  if HAS.wheels then robot.wheels.set_velocity(0,0) end
  if CAM_OK and type(CAM.disable)=="function" then CAM.disable() end
end

function destroy()
  if CAM_OK and type(CAM.disable)=="function" then CAM.disable() end
end
