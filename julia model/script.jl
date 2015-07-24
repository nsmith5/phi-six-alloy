# ----------------------------------------
#       Main Simulation Script
# ----------------------------------------

module script

using Constants, Methods

using PyPlot

ϕ = zeros(N, N)

for x in 1:N
  for y in 1:N/2
    ϕ[x,y] = 1.5
  end
end

c = imshow(ϕ)
plt.colorbar()

for x in 1:100
  ϕ = integrate!(ϕ)
  c[:set_data](ϕ)
  draw()
  println(x)
end

writedlm("out.dat", ϕ)

end
