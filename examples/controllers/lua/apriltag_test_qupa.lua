function init()
   log("apriltag_test_qupa initialized")
end

function step()
   if robot.tag then
      log(string.format(
         "tag id=%d position=(%.3f,%.3f,%.3f) angle=%.3f",
         robot.tag.id,
         robot.tag.position.x,
         robot.tag.position.y,
         robot.tag.position.z,
         robot.tag.angle
      ))
   end
end

function reset()
end

function destroy()
end
