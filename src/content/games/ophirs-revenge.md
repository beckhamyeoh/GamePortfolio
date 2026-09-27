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

## Process

**Prototype (days 1–2).** The first playable build had a black square for the player
and a training dummy in place of a boss, but it already had movement, a dodge, arrows,
an ammo count and a snare. Arrows that hit the dummy dropped pickups, so the core idea,
that you have to recover your own ammo, could be tested before any art existed.

**Making every shot a decision (day 3).** I added bow charging: the longer you draw, the
faster and harder the arrow. Drawing roots the player in place, so a full-power shot
means standing still while the boss closes in. I also added death with an instant
retry, since a hard boss fight only works if trying again costs nothing.

**The fight was too easy (days 6–7).** Aiming with a mouse is easy, so I almost never
lost an arrow. I cut the starting count from 5 to 3 and the maximum from 12 to 6, and
changed pickups from walking over them to holding a key for half a second, so
recovering an arrow costs time while the boss chases you. My partner also doubled the
boss's lunge range, which made keeping your distance much harder.

**Showing the player what's happening.** Once drawing and pickups both took time,
players needed to see that time pass: a ring fills while you pick up an arrow, and a
charge bar sits under the archer. The boss health bar has a marker at 50% so you can
see phase 2 coming.

**Fair hits, readable attacks.** One lightning strike was dealing 3 damage because the
damage script had been attached more than once. I removed the duplicates and added a
short invulnerability window with a blinking sprite, so every hit counts once and you
can see it land. Distinct wind-up and charge sounds tell you which attack is coming, so
you can react without watching the boss. I cut a sound for the weak window after it
got repetitive.

**Giving the snare a purpose.** The snare originally just slowed the boss, and the fight
was easy to win without it. I turned it into a one-second stun that opens the boss's
weak point for double damage. One second is exactly one full draw, so starting your
draw before the boss reaches the trap becomes a planned combo.

**Telling the story through the fight.** An intro names the four fallen party members.
At half health the boss calls lightning down on their bodies and the music speeds up,
so the story beat and the jump in difficulty land together. Short lines appear at key
moments, and the final blow plays in slow motion.

**After the jam.** A player pointed out that the boss's lightning never connected: it
was cast from farther away than the bolts could reach. I gave the lightning its own
shorter range and taller hitboxes, and cut the maximum arrows from 6 to 4 to keep ammo
tight.

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
