---
title: "Ophir's Revenge"
tagline: "A ranger with three arrows against the Storm Head. 5th of 18 in Boss Fight Jam."
thumbnail: "screenshots/ophirs-revenge.png"
tech: ["Unity", "C#"]
playable: true
buildPath: "play/ophirs-revenge"
repo: "https://github.com/beckhamyeoh/boss-jam"
order: 5
---

Your party is dead and your quiver is nearly empty, so every arrow you fire is one
you have to walk back out and pick up while the boss hunts you.

A single boss fight built in a week for Boss Fight Jam, working with one partner.
It placed **5th of 18 overall**, **3rd in Game Design** and **4th in Fun**. Also on
[itch.io](https://attempt1.itch.io/ophirs-revenge).

## Highlights

- **Ammo as the core tension.** You hold at most four arrows. Arrows that hit the
  boss drop where they land, and missed arrows are gone for good.
- **Risk in the draw.** Drawing the bow roots you in place, so a full-power shot
  means standing still while the boss closes in.
- **Snare combo.** A snare stops the boss and opens its weak point for one second,
  which is exactly one full draw if you start early.
- **Two phases.** At half health the boss calls down lightning that destroys your
  fallen party, and the music pitches up as it enters its second phase.

## My contributions

Player controller, bow and ammo systems, the snare, HUD and boss health bar, game
flow and end screens, audio, and the phase 2 lightning that burns away the party.
My partner built the boss: its animations, attack state machine and lightning
hitboxes, plus the camera shake, screen bounds and the fallen party. We split the
arena between us.

## Code highlight

Draw time drives both arrow speed and damage from a single 0&ndash;1 charge value, so
one input controls the risk/reward of every shot.

```csharp
void Fire()
{
    if (arrowPrefab == null || currentArrows <= 0) return;

    Vector3 mouseWorld = cam.ScreenToWorldPoint(Input.mousePosition);
    mouseWorld.z = 0f;
    Vector2 dir = ((Vector2)(mouseWorld - transform.position)).normalized;
    if (dir.sqrMagnitude < 0.0001f) return;

    currentArrows--;

    // longer draw -> faster arrow and more damage
    float charge = DrawCharge;
    float speed = Mathf.Lerp(minArrowSpeed, maxArrowSpeed, charge);
    float damage = Mathf.Lerp(minDamage, maxDamage, charge);

    float angle = Mathf.Atan2(dir.y, dir.x) * Mathf.Rad2Deg;
    Vector3 spawnPos = transform.position + (Vector3)dir * 0.5f;
    GameObject arrow = Instantiate(arrowPrefab, spawnPos, Quaternion.Euler(0, 0, angle));
    arrow.GetComponent<Arrow>().Launch(dir * speed, damage);
    Sfx.Play("shoot", 0.5f);
    OnFired?.Invoke();
}
```
