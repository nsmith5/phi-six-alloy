# ---------------------------------
#  Methods required for simulation
# ---------------------------------

module Methods

using Constants

export integrate!

function ring(index::Int64, limit::Int64)
  # Period modulus for indexing
  return (limit+index%limit)%limit + 1
end

function random_flux(σ::Float64)
  x_flux = σ*randn(N,N)
  y_flux = σ*randn(N,N)
  ξ = zeros(N,N)

  for i in 1:N
    for j in 1:N
    ξ[i,j] -= x_flux[i,j] + y_flux[i,j]
    ξ[ ring(i+1, N), j] += x_flux[i,j]/2.0
    ξ[ ring(i-1, N), j] += x_flux[i,j]/2.0
    ξ[i, ring(j+1, N)] += y_flux[i,j]/2.0
    ξ[i, ring(j-1, N)] += y_flux[i,j]/2.0
    end
  end

  return ξ
end

function ∇²(ϕ::Array{Float64, 2})
  temp = zeros(N,N)
  for i in 2:(N-1)
    for j in 2:(N-1)
      temp[i,j] = (ϕ[i+1,j] - 4.0*ϕ[i,j] + ϕ[i-1,j] + ϕ[i,j+1] + ϕ[i,j-1])/dx^2
    end
  end

  for i in 1:N
    temp[i,N] = (ϕ[ring(i+1,N), N] - 4.0*ϕ[i, N] + ϕ[ring(i-1,N), N] + ϕ[ring(i,N),1] + ϕ[ring(i,N), N-1])/dx^2
    temp[i,1] = (ϕ[ring(i+1,N), 1] - 4.0*ϕ[i, 1] + ϕ[ring(i-1,N), 1] + ϕ[ring(i,N),2] + ϕ[ring(i,N),N])/dx^2
  end
  for j in 1:N
    temp[N,j] =(ϕ[N,ring(j+1,N)] - 4.0*ϕ[N,j] + ϕ[N, ring(j-1,N)] + ϕ[1, ring(j,N)] + ϕ[N-1, ring(j,N)])/dx^2
    temp[1,j] =(ϕ[1,ring(j+1,N)] - 4.0*ϕ[1,j] + ϕ[1, ring(j-1,N)] + ϕ[2, ring(j,N)] + ϕ[N, ring(j,N)])/dx^2
  end

  return temp
end

function integrate!(ϕ::Array{Float64, 2})
  # ----------------------
  #   Euler time march
  # the field by one time
  # step.
  # ----------------------
  N = size(ϕ)[1]            # Size of the field
  σ = 0.1
  ξ = random_flux(σ)  # Generate noise

  # ∂ϕ = ∇²(ϕ)
  #
  # for i in 1:N
  #   for j in 1:N
  #     ∂ϕ[i,j] *= -W
  #     ∂ϕ[i,j] += r*ϕ[i,j] + u*ϕ[i,j]^3 + v*ϕ[i,j]^5
  #     ∂ϕ[i,j] *= Γ
  #   end
  # end
  #
  # ∂ϕ = ∇²(∂ϕ)
  #
  # for i in 1:N
  #   for j in 1:N
  #     ∂ϕ[i,j] += ξ[i,j]
  #     ∂ϕ[i,j] *= dt
  #     ϕ[i,j] += ∂ϕ[i,j]
  #   end
  # end
  ϕ +=  dt*(Γ*∇²(-W*∇²(ϕ) + r*ϕ + u*ϕ.^3 + v*ϕ.^5) + ξ)         # Update the field phi

  return ϕ
end


end
