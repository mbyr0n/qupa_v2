function init()
  if robot.colored_blob_omnidirectional_camera then
    robot.colored_blob_omnidirectional_camera.enable()   -- << CLAVE
  end
  if robot.leds then
    local n = tonumber(robot.id:match("(%d+)$")) or 0
    local colors={{255,0,0},{0,255,0},{0,0,255},{255,255,0},{0,255,255},{255,0,255}}
    local c=colors[(n%#colors)+1]
    robot.leds.set_all_colors(c[1],c[2],c[3])
  end
end

function destroy()
  if robot.colored_blob_omnidirectional_camera then
    robot.colored_blob_omnidirectional_camera.disable()
  end
end
