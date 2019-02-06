function printResult (a)
	for i = 1, #a do
		io.write(a[i], " ")
	end
	io.write("\n")
end

function permgen (a, n)
	n = n or #a
	if n <= 1 then
		coroutine.yield(a)
	else
		<as before>
	end
end

function permutations (a)
	local co = coroutine.create(function () permgen(a) end)
	return function () -- iterator
		local code, res = coroutine.resume(co)
		return res
	end
end

for p in permutations{"a", "b", "c"} do
	printResult(p)
end
