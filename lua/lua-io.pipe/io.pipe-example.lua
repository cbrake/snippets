
util = require 'util'

local M = {}

function M.setup(serialNumber)
	M.serialNumber = serialNumber
	M.enabled = false
	M.lastCheck = 0
	M.co = coroutine.create(M.disableRemoteAccess)
	M.pipe = nil
end

function M.isRunning()
	local ret = os.execute('ps | grep sshkite | grep defunct | grep -v grep')
	if (ret == 0) then
		io.close(M.pipe)
		return false
	end
	local ret, exit, status = os.execute('ps | grep sshkite | grep -v grep')
	return ret == 0 
end

function M.enableRemoteAccess()
	if (M.isRunning()) then
		os.execute('killall sshkite')
		coDelay(5)
	end

	::RESTART::

	M.pipe = io.popen('sshkite ' .. M.serialNumber .. '.bec.pagekite.me gesbcrs485')
	if (not M.pipe) then
		print('Warning, sshkite did not start properly')
		coDelay(10)
		goto RESTART
	end

	while true do
		--print(p.read())
		if (not M.isRunning()) then
			print('Warning, sshkite stopped, restarting')
			goto RESTART
		end
		coDelay(60)
	end
end

function M.disableRemoteAccess()
	while (M.isRunning()) do
		os.execute('killall sshkite')
		coDelay(5)
	end
end

function M.update(enabled)
	if (enabled ~= M.enabled) then
		print('Remote access: ', enabled)
		M.enabled = enabled
		if enabled then
			M.co = coroutine.create(M.enableRemoteAccess)
		else
			M.co = coroutine.create(M.disableRemoteAccess)
		end
	end

	if (coroutine.status(M.co) ~= 'dead') then
		local ret, v = coroutine.resume(M.co)
		if (not ret) then
			print('RemoteAccess coroutine stopped', v)
		end
	end
end

return M

