# ----------------------------
#  Constants for simulation
# ----------------------------

module Constants

export W, r, u, v, Γ, dx, dt, N

Γ = 1.0       # Mobility
W = 1.0       # Curvature penalty
r = 4.0       # Quadratic Landau constant
u = -2.0      # Quartic Landau constant
v = 0.30      # Sixth order Landau constant

dx = 0.8      # Lattice spacing
dt = 0.01    # Time step size
N = 300       # Number of lattice points (N x N)

end
