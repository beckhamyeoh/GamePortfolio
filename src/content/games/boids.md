---
title: "Boids"
tagline: "Flocking simulation using separation, alignment, and cohesion."
year: 2024
tech: ["Unity", "C#", "AI"]
playable: true
buildPath: "play/boids"
order: 70
---

A flocking simulation that implements the classic boids algorithm —
separation, alignment, and cohesion — to produce emergent group behavior in
real time.

## Code highlight

Three simple steering rules (avoid neighbors, match their velocity, move toward
their center) sum into one vector that produces emergent flocking. No single
boid knows about the flock as a whole.

```csharp
// collision avoidance: steer away from neighbors that are too close
if (tooNearPos != Vector3.zero) sumVel += (pos - tooNearPos).normalized * bSet.nearAvoid;
// velocity matching: align heading with nearby boids
if (velAlign != Vector3.zero) sumVel += velAlign.normalized * bSet.velMatching;
// flock centering: drift toward the local center of mass
if (velCenter != Vector3.zero) sumVel += (velCenter - pos).normalized * bSet.flockCentering;
// ease toward the combined steering vector instead of snapping to it
vel = Vector3.Lerp(vel.normalized, sumVel.normalized, bSet.velocityEasing) * bSet.velocity;
```
