class Jawna
	def initialize(str)
		@str = str
	end
	def zaszyfruj(klucz)
		s = ""
		for i in 0...(@str.length)
			s += (@str[i].ord + klucz).chr
		end
		return Zaszyfrowana.new(s)
	end 

	def to_s
		return @str
	end
end

class Zaszyfrowana
	def initialize(str)
		@str = str
	end
	def odszyfruj(klucz)
		s = ""
		for i in 0...(@str.length)
			s += (@str[i].ord - klucz).chr
		end
		return Jawna.new(s)
	end

	def to_s
		return @str
	end
end

str1 = Jawna.new("Ala ma kota")
str2 = Zaszyfrowana.new("bcd")
puts str1.zaszyfruj(3)