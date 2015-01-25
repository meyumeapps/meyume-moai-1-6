MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

MOAIUntzSystem.initialize ()

sound = MOAIUntzSound.new ()
sound:load ( 'piece-drop.wav' )
sound:setVolume ( 1 )
sound:setLooping (false)

--[[sound2 = MOAIUntzSound.new ()
sound2:load ( 'mono16.wav' )
sound2:setVolume ( 1 )
sound2:setLooping (false)]]--

    sound:play();
    --sound2:play();

MOAIInputMgr.device.mouseLeft:setCallback(function(down)
    if  down then
		print("sound is playing " .. tostring(sound:isPlaying()))
		--print("sound2 is playing " .. tostring(sound2:isPlaying()))
    end	
end
)
