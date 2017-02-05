class Proc
	def value(x)
		self.call(x)
	end

	def zerowe(a, b, e)
		res = []
		epsilon = 0.000001
		while(a <= b)
			if(value(a).abs < epsilon)
				res.push(a.round(5))
			end
			a += e
		end
		if res.empty?
			return nil
		end
		return res
	end

	def pole(a, b, step = 0.0001)
		area = 0.0
		s = a + step
		while(s < b)
			area += (value(a)+value(s)) * 0.5 * step
			a += step
			s += step
		end
		return area
	end

	def poch(x, h = 0.001)
		return (value(x + h) - value(x)) / h
	end

	def wykres(filename, a, b, size = 300, scale = 1.0, e = 0.1)
		sizestr = size.to_s
		sizestrminus = (-size).to_s
		file = File.new(filename, "w+")
		file.write("%!PS-Adobe-2.0 EPSF-2.0\n")
		file.write("%%BoundingBox: " + sizestrminus + " " + sizestrminus + " " + sizestr + " " + sizestr + "\n")
		file.write("newpath\n")
		file.write(
					  sizestrminus + " 0 moveto\n" +
					  sizestr + " 0 lineto\n" +
					  "0 " + sizestr + " moveto\n" +
					  "0 " + sizestrminus + " lineto\n"				
				  )

		file.write((a * scale).to_s + " " + (value(a) * scale).to_s + " moveto\n")
		i = a
		while(i < b)
			i += e
			file.write((i * scale).to_s + " " + (value(i) * scale).to_s + " lineto\n")
		end
		file.write("stroke\nshowpage")
	end

end


f = proc { |x| -5 * x * x * x + 2 * x * x + 6 * Math.sin(x)*x + 1 }
f1 = proc{ |x| x*x}
f2 = proc {|x| Math.atan(x)}
f3 = proc {|x| Math.sin(x)}
#puts f1.pole(0.0, 1.0)
#puts f1.poch(1.0)
#f2.wykres("wykres.ps",-10.0,10.0, 300, 100.0)
f2.wykres("wykres.ps", -10.0, 10.0, 300, 20.0)
