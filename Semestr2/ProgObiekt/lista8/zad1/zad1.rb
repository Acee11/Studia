class Fixnum
	def prime?
		if self % 2 == 0
			return false
		end
		i = 3
		while i*i <= self
			if self % i == 0
				return false
			end
			i += 2
		end
		return true
	end

	def ack(y)
		if self == 0
			return y + 1
		end
		if y == 0
			return (self-1).ack(1)
		end
		return (self-1).ack(self.ack(y-1))
	end

	def doskonala?
		suma = 0
		for i in 1..(self/2)
			if self % i == 0
				suma += i
			end
		end
		if suma == self
			return true
		end
		return false	
	end

	def slownie
		if self == 0
			return "zero"
		end
		i = self
		minus = ""
		if i < 0
			minus = "minus "
			i = -i
		end
		res = ""
		while i != 0
			case i % 10
			when 0
				res = "zero " + res
			when 1
				res = "jeden " + res
			when 2
				res = "dwa " + res
			when 3
				res = "trzy " + res
			when 4
				res = "cztery " + res
			when 5
				res = "piec " + res
			when 6
				res = "szesc " + res
			when 7
				res = "siedem " + res
			when 8
				res = "osiem " + res
			when 9
				res = "dziewiec " + res
			end
			i /= 10
		end
		return minus + res
	end


end

puts "prime? test"

for i in 2..20
	puts i.prime?
end

puts
puts "ack test"

puts 1.ack(1)
puts 2.ack(1)
puts 1.ack(2)
puts 2.ack(2)


puts
puts "doskonala test"

for i in 1..30
	puts i
	puts i.doskonala?
end

puts
puts "slownie test"

puts 123.slownie
puts -321.slownie
puts 0.slownie
puts 1.slownie
puts 1337.slownie
