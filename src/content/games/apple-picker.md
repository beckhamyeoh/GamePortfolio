---
title: "Apple Picker"
tagline: "Catch falling apples in a basket. A Unity intro project."
thumbnail: "screenshots/apple-picker.png"
year: 2024
tech: ["Unity", "C#"]
playable: true
buildPath: "play/apple-picker"
order: 30
---

A simple arcade game where the player moves a basket left and right to catch
falling apples. Built as an introductory Unity project covering input,
spawning, scoring, and lives.

## Code highlight

The tree re-schedules its own next apple drop with `Invoke`, creating a steady
drip without tracking a timer in `Update`.

```csharp
void DropApple() {
    Instantiate(applePrefab).transform.position = transform.position;
    Invoke("DropApple", appleDropDelay);   // schedule the next drop
}
```
