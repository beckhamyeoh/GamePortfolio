---
title: "Space SHMUP"
tagline: "Vertical shoot-'em-up with power-ups, enemy variety, and a boss fight."
year: 2024
tech: ["Unity", "C#"]
playable: true
buildPath: "play/space-shmup"
order: 10
---

A vertical shoot-'em-up built in Unity. Pilot a ship through waves of enemies,
collect stacking power-ups, and take on a multi-phase boss encounter.

## Highlights

- Power-up pickup system with stacking effects
- Multiple enemy patterns with pooled spawning
- Boss fight with phased behavior

## Code highlight

A data-driven weapon system where the spread shot fans three projectiles using
quaternion rotations. Adding a new weapon is just filling in a
`WeaponDefinition` in the inspector.

```csharp
case eWeaponType.spread:
    MakeProjectile().vel = vel;                                   // center
    var pL = MakeProjectile();                                    // +10 degrees
    pL.transform.rotation = Quaternion.AngleAxis(10, Vector3.back);
    pL.vel = pL.transform.rotation * vel;
    var pR = MakeProjectile();                                    // -10 degrees
    pR.transform.rotation = Quaternion.AngleAxis(-10, Vector3.back);
    pR.vel = pR.transform.rotation * vel;
    break;
```
