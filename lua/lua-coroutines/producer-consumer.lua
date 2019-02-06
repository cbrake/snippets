#!/usr/bin/env luajit

function receive (prod)
	local status, value = coroutine.resume(prod)
	return value
end

function send (x)
	coroutine.yield(x)
end

function producer ()
	return coroutine.create(function ()
		while true do
			local x = io.read()
			-- produce new value
			send(x)
		end
	end)
end

function filter (prod)
	return coroutine.create(function ()
		for line = 1, math.huge do
			local x = receive(prod) -- get new value
			x = string.format("%5d %s", line, x)
			send(x)
			-- send it to consumer
		end
	end)
end

function consumer (prod)
	while true do
		local x = receive(prod)
		io.write(x, "\n")
	end
end

consumer(filter(producer()))

