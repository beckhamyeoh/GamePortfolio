---
title: "Mission Demolition"
tagline: "Angry-Birds-style physics game: launch projectiles to topple structures."
thumbnail: "screenshots/mission-demolition.png"
year: 2024
tech: ["Unity", "C#", "Physics"]
playable: true
buildPath: "play/mission-demolition"
order: 40
---

A physics-based projectile game inspired by Angry Birds. Players pull back to
launch a projectile and try to topple the goal structure across multiple
levels.

## Code highlight

The drag is clamped to the slingshot's collider radius, then the launch
velocity is the inverse of the drag vector. Pull back further, fire harder,
just like the real thing.

```csharp
// clamp the drag to the slingshot's radius so you can't over-pull
if (mouseDelta.magnitude > maxMagnitude) mouseDelta = mouseDelta.normalized * maxMagnitude;
// on release, launch opposite the drag, scaled by a velocity multiplier
projRB.isKinematic = false;
projRB.velocity = -mouseDelta * velocityMult;
```
