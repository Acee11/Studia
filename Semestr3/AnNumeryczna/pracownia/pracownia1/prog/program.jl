###############################
#   Autor: Wojciech Balik     #
#   Nr indeksu: 280254        #
###############################
using Plotly
setprecision(256)
BF = BigFloat

δ = eps(BF)
ϵ = eps(BF)

function bisectionMethod(f, a, b, iter, δ, ϵ)
	c = 0
	for i = 1:iter
		c = (a + b) / 2
		fc = f(c)
        if(abs(b-a) < ϵ || abs(fc) < δ )
            return c
        end
		if(sign(f(a)) != sign(fc))
			b = c
		else
			a = c
		end
        
	end	
	return c
end

function secantMethod(f, a, b, iter, δ, ϵ)
	for i = 1:iter
		tmp = b
		fb = f(b)
		b = b - (fb*(b - a)) / (fb - f(a)) 
		a = tmp
        if(abs(b-a) < ϵ || abs(fb) < δ)
            return b
        end
	end
	return b
end

function secantMethodA(f, a, b, iter, δ, ϵ)
	c = a
	for i = 1:iter
		tmp = b
		fa = f(a)
		fb = f(b)
		ms = b - (fb*(b - a)) / (fb - fa) 
		if(sign(fa) != sign(fb))
			b = ms
		else
			if(ms >= b && ms <= c || ms >= c && ms <= b)
				b = ms
			else
				b = (b + c) / BF(2.0)
			end
		end
		a = tmp
        fb1 = f(b)
		if(sign(fb) != sign(fb1))
			c = a
		end
        if(abs(b-a) < ϵ || abs(fb1) < δ)
            return b
        end
	end
	return b
end

function newtonMethod(f, df, a, iter, ϵ)
	for i = 1:iter
        fa = f(a)
        if(abs(fa) < ϵ)
            return a
        end
		a = a - (fa/df(a))
	end
	return a
end


#Sposob uzywania funkcji printTests:
# f - funkcja ktorej pierwiastkow szukamy
# df - pochodna f
# fzero - pierwiastek z ktorym wyniki beda porownywane
# k - liczba iteracji
# δ, ϵ - wartosci z tresci zdania
# bis, new, sec, seca - punkty poczatkowe testowanych metod.
# new ma postac new = x0
# bis, sec, seca maja postac [x0, x1] 
function printTests(f, df, fzero, k, δ, ϵ, bis, new, sec, seca)
    @printf "%-17s %-17s %-17s %-17s %-17s\n" "Iteracja" "   MB" "   MN" "   MS" "   MSA"
    for i = 1:k
        @printf "%-17d %-17.3e %-17.3e %-17.3e %-17.3e\n" i abs(bisectionMethod(f, bis[1], bis[2], i, δ, ϵ) - fzero)  abs(newtonMethod(f, df, new, i, ϵ) - fzero) abs(secantMethod(f, sec[1], sec[2], i, δ, ϵ) - fzero) abs(secantMethodA(f, seca[1], seca[2], i, δ, ϵ) - fzero)
    end
end

