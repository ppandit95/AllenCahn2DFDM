using DelimitedFiles,Plots;pyplot()
data = ["Initial_Profile.dat" "Output-100.dat" "Output-200.dat" "Output-500.dat" "Output-1000.dat" ]
dfp = @__DIR__

for i in 1:5
    global data[i]=string(dfp,"/",data[i])
end
 D = [readdlm(data[i]) for i in 1:5]
for i in 1:5
    global data[i] =  chop(data[i],head=0,tail=3)
end
heatmap(D[1],c=:greys)
savefig(string(data[1],"png"))
heatmap(D[2],c=:greys)
savefig(string(data[2],"png"))
heatmap(D[3],c=:greys)
savefig(string(data[3],"png"))
heatmap(D[4],c=:greys)
savefig(string(data[4],"png"))
heatmap(D[5],c=:greys)
savefig(string(data[5],"png"))
