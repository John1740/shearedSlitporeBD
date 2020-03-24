#ifndef FORCE_H
#define FORCE_H

#include "../struct/cartesian_coordinate.h"
#include "../interfaces/box_geometry.h"

template<class PARTICLE_T>
class FORCE
{
public:
   virtual CARTESIAN_COORDINATE forceOnParticle ( PARTICLE_T& particle ) = 0;
};

template<class PARTICLE_T>
class CONSERVATIVE_FORCE: public FORCE<PARTICLE_T>
{
public:
   virtual double energyOnParticle ( PARTICLE_T& particle ) = 0;
};

template<class PARTICLE_T>
class TWO_BODY_FORCE
{
public:
   virtual CARTESIAN_COORDINATE forceOnParticleFromParticle ( PARTICLE_T& particle1, PARTICLE_T& particle2, BOX_GEOMETRY& simBox ) = 0;
};

template<class PARTICLE_T>
class TWO_BODY_CONSERVATIVE_FORCE: public TWO_BODY_FORCE<PARTICLE_T>
{
public:
   virtual double energyOnParticleFromParticle ( PARTICLE_T& particle1, PARTICLE_T& particle2, BOX_GEOMETRY& simBox ) = 0;
};

#endif // FORCE_H
