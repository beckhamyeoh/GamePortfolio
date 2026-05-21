---
title: "Prospector"
tagline: "Solitaire-style card game with scoring, animations, and a polished UI."
year: 2024
tech: ["Unity", "C#"]
playable: true
buildPath: "play/prospector"
order: 20
---

A solitaire-style card game where the player clears the tableau by picking
cards adjacent to the current draw card. Built in Unity with animated card
movement, a scoring system, and a polished UI.

## Code highlight

A reusable component animates any object along a Bezier curve with easing, then
fires a callback when it finishes. It is what makes the cards glide instead of
teleport.

```csharp
u = (Time.time - timeStart) / timeDuration;     // raw 0 to 1 progress
uCurved = Easing.Ease(u, easingCurve);          // apply easing curve
if (u >= 1) { uCurved = 1; state = eState.post; completionEvent.Invoke(); }
pos = Utils.Bezier(uCurved, bezierPts);          // sample the curve
```
