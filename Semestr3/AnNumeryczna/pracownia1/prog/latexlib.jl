function generateResMatrix(f, df, fzero, k, δ, ϵ, bis, new, sec, seca)
    MB = Array{BigFloat}(k) 
    MN = Array{BigFloat}(k)
    MS = Array{BigFloat}(k)
    MSA = Array{BigFloat}(k)
    for i = 1:k
        MB[i] = abs(bisectionMethod(f, bis[1], bis[2], i, δ, ϵ) - fzero)
        MN[i] = abs(newtonMethod(f, df, new, i, ϵ) - fzero)
        MS[i] = abs(secantMethod(f, sec[1], sec[2], i, δ, ϵ) - fzero)
        MSA[i] = abs(secantMethodA(f, seca[1], seca[2], i, δ, ϵ) - fzero)
    end
    return [MB, MN, MS, MSA]
end

function latexTable(resMatrix)
    res = "Iteracja & MB & MN & MS & MSA \\\\ \\hline \\hline\n"
    MB = resMatrix[1]
    MN = resMatrix[2]
    MS = resMatrix[3]
    MSA = resMatrix[4]
    for i = 1:length(MB)
        sMB = @sprintf " & %.3e" MB[i]
        sMN = @sprintf " & %.3e" MN[i]
        sMS = @sprintf " & %.3e" MS[i]
        sMSA = @sprintf " & %.3e \\\\ \\hline\n" MSA[i]
        res = string(res, @sprintf "%d" i)
        res = string(res, sMB, sMN)
        res = string(res, sMS, sMSA)
    end
    return res
end