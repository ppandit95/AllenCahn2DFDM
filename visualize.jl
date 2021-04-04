using DelimitedFiles

data = readdlm("/home/pushkar/Task_assignment_pics/AllenCahn2DFDM/Output-100.000000.dat")
using Plots;pyplot()
heatmap(data,c=:greys)
