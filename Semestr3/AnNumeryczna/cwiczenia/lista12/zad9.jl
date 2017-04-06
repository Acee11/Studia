l = 5.0
g = 9.80665
θ = [pi/3.0, 0.0]
b = 10.0
h = 0.1
t = zero(Float64)

f(t, θ::Vector{Float64}) = [θ[2], -g/l * sin(θ[1])]

function RK(t, θ::Vector{Float64}, h, f::Function)
    K1 = f(t, θ)
    K2 = f(t+h/2  , θ+h*K1/2)
    K3 = f(t+h/2  , θ+h*K2/2)
    K4 = f(t+h    , θ+h*K3  )
    return θ + h/6*(K1+2*(K2+K3)+K4)
end

while(t <= b)
    @printf "%.1f   |   %.3f\n"  t θ[1]
    θ = RK(t, θ, h, f)
    t = t + h
end
