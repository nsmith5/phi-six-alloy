### Remarks and Findings

- There seems to be a numerical instability in the integration routine
that could be stemming from the higher order powers...
  - Maybe this could be stabilized by normalizing phi values to between 0 and 1
  - That approach would be helpful in the long run to make a physical connection

- There also seems to be a directional bias, in both the slab and liquid pool simulations horizonal grooves open up even though in the liquid pool there should be no difference between horizonal and vertical directions

Goals:
- Show that this is equavalent but a more simple representation than the two order parameter theory (through mass conservation?)
- Show that there is a meta-stable liquid and solid equilibrium below the eutectic point..
- Simulate a liquid pool that is cooled

Questions:
- Will a phi to the six theory create a stronger slope towards the solid to allow for sufficient solute rejection?
- Is the entalphy of fusion essentially constant for different temperatures? This would fix the barrier height from meta-stable liquid to solid.


### Shifted even Legendre Polynomial  Idea

May rewriting the free energy as a set of orthogonal polynomials would be a good idea. If we say that the polynomials orthogonal on [0,1] then we naturally have mapped our system onto a space of fractions (say number fraction or percent weight or what ever).

We need to represent span{x^2, x^4, x^6} so we can do gram-schmidt with the inner product being the simply integral of the product between 0 and 1.

$$ < f, g > = \int_0^1 f(x) g(x) dx $$

We'll call these polynomials Even Shifted Legendre polynomials:

P0(x) = 1

P2(x) = x^2 - x + 1/6

P4(x) = x^4 - 2*x^3 + (9/7)*x^2 - (2/7)*x - (1/70)

P6(x) = x^6 - 3*x^5 + (75/22)*x^4 - (20/11) x^3 + (5/11)*x^2 - (1/22)*x + (1/924)

Normalization coefficients:

n0 = 1

n2 = 6*sqrt(5)

n4 = 210

n6 = 923*sqrt(13)
