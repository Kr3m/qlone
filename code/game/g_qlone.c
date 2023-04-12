#include "g_local.h"

// G_RailgunRadiusDamage
// cf. https://www.quake3world.com/forum/viewtopic.php?p=703193
// ^Misantropia^: "If the trace stopped within, say, 64 units, hitting a surface, apply knockback."
// cf. G_RadiusDamage for the code inspiration

void G_RailgunRadiusDamage (vec3_t origin, gentity_t *ent) {
	int i;
	vec3_t v, dir;
	float damage, radius, distMax, dist, points;

	// use the same values as the Rocket Launcher
	damage = 100;
	radius = 120;

	// max distance to trigger the damage
	distMax = 64;

	// find the distance from the edge of the bounding box
	for ( i = 0 ; i < 3 ; i++ ) {
		if ( origin[i] < ent->r.absmin[i] ) {
			v[i] = ent->r.absmin[i] - origin[i];
		} else if ( origin[i] > ent->r.absmax[i] ) {
			v[i] = origin[i] - ent->r.absmax[i];
		} else {
			v[i] = 0;
		}
	}

	dist = VectorLength( v );

	if ( dist < distMax ) {
		points = damage * ( 1.0 - dist / radius );
		if( CanDamage (ent, origin) ) {
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage (ent, NULL, ent, dir, origin, (int)points, DAMAGE_RADIUS, MOD_RAILGUN);
		}
	}
}
