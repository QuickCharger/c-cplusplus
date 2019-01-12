myStr = "this is from lua"

myTable = {name="qwer", id=1234}
myTable2 = {111, 222, 333}
myTable3 = {{name="qwer", id=1234},{name="asdf", id=2345},{name="zxcv", id=3456}}

function add(x,y)
	print(x, "+", y, "=", x+y)
	return x+y;
end 
