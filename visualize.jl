using DelimitedFiles,Plots;pyplot()
data = ["Initial_Profile.dat" "Output-10.dat" "Output-20.dat" "Output-50.dat" "Output-100.dat"]
dfp = @__DIR__
for i in 1:5
    global data[i]=string(dfp,"/",data[i])
end
 D = [readdlm(data[i]) for i in 1:5]
for i in 1:5
    heatmap(D[i],c=:greys)
end
