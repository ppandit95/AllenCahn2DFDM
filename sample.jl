using DifferentialEquations
f(t,u) = -1.05 * u
u0 = 1.0
tspan = (0.0,1.0)
prob = ODEProblem(f,u0,tspan)
sol = solve(prob)
using Plots;pyplot()
plot(sol)
