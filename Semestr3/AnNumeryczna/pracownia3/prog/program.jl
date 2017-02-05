###################################
#                                 #
#      Autor: Wojciech Balik      #
#                                 #   
###################################


A = Array{Float64}(4,4)
@enum LU LOWER UPPER

function getRandMatrix(n, nmatr=1, T = Float64, a = T(20), b = T(-10))
    res = []
    for k = 1:nmatr
        M = zeros(T,n,n)
        for i = 1:n
            for j = 1:i
                M[i,j] = rand()*a + b
            end
        end
        push!(res, M)
    end
    return res
end


function pei(n, ϵ, T = Float64)
    M = ones(T,n,n)
    for i = 1:n
        M[i,i] = ϵ
    end
    return M
end

function hilbert(n, T = Float64)
    M = Array{T}(n,n)
    for i = 1:n, j = 1:n
        for j = 1:n
            M[i,j] = 1/(i+j-1)
        end
    end
    return M
end

function cholesky(A::Array, T = Float64)
    n,m = size(A)
    assert(n == m)
    L = Array{T}(n,n)

    for i = 1:n
        w = A[i,i]
        for j = 1:(i-1)
            s = 0
            for k = 1:(j-1)
                s += L[i,k] * L[j,k]
            end
            L[i,j] = (A[i,j] - s)/L[j,j]
            w -= L[i,j]*L[i,j]
        end
        if w < 0
            return -1
        end
        L[i,i] = sqrt(w)
    end
    
    return L
end

function chol_solve(A, b) #solves Ax = b (returns x)
    L = cholesky(A)
    y = diag_solve(L, b, LOWER)
    return diag_solve(transpose(L), y, UPPER)
end

function diag_solve(A, b, LU::LU)
    n = length(b)
    x = Array{typeof(b[1])}(n) 

    if(LU == LOWER)
        for i = 1:n
            s = 0
            for j = 1:(i-1)
                s += A[i,j]*x[j]
            end
            x[i] = (b[i] - s)/A[i,i]
        end
    else
        for i = n:-1:1
            s = 0
            for j = (i+1):n
                s += A[i,j]*x[j]
            end
            x[i] = (b[i] - s)/A[i,i]
        end  
    end
    return x
end
