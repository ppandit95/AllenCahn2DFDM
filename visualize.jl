using DelimitedFiles

data = readdlm("/home/pushkar/Task_assignment_pics/AllenCahn2DFDM/Initial_Profile.dat")
using Plots;pyplot()
heatmap(data,c=:greys)
