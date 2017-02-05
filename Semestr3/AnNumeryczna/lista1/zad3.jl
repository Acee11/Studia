w0(x, t) = x^3 - t(6.0)*(x^2) + t(3)*x - t(0.149)

w1(x, t) = ((x - t(6))*x + t(3))*x - t(0.149) 


for t in [float16, float32, float64]
	x = t(4.71)

	x0 = w0(x, t)
	@printf "w0(x) = %f\n" x0
	@printf "%s\n" typeof(x0)

	x1 = w1(x, t)
	@printf "w1(x) = %f\n" x1
	@printf "%s\n" typeof(x1)
end



#=
	w0(x) = -14.578125
	Float16
	w1(x) = -14.632813
	Float16

	w0(x) = -14.636500
	Float32
	w1(x) = -14.636490
	Float32

	w0(x) = -14.636489
	Float64
	w1(x) = -14.636489
	Float64
=#