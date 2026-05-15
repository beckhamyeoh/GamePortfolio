# WebGL builds go here

Each game's WebGL build output should be placed in a subfolder matching the
`buildPath` field in its markdown file under `src/content/games/`.

## How to build a WebGL game in Unity

1. Open the Unity project (e.g. `~/UnityGames/ApplePicker`).
2. `File → Build Settings…`
3. Select **WebGL** as the platform, click **Switch Platform**.
4. Click **Build**. When asked for an output folder, point it at the matching
   directory below (e.g. `public/games/apple-picker`).
5. After the build finishes, that folder will contain `index.html`,
   `Build/`, and `TemplateData/`. The site picks it up automatically.
6. Flip `playable: true` in the corresponding markdown file under
   `src/content/games/` so the game page swaps in the iframe.

## Expected folder layout

```
public/games/
  apple-picker/      → buildPath: "games/apple-picker"
  boids/             → buildPath: "games/boids"
  mission-demolition/
  prospector/
  prospector-2/
  space-shmup-1/
  space-shmup-2/
```

## Tips

- In `Player Settings → Publishing Settings`, set **Compression Format** to
  **Disabled** or **Gzip**. GitHub Pages does not serve `.br` (Brotli) files
  with the right Content-Encoding header by default.
- Set **Decompression Fallback** to **on** if you keep gzip — it embeds a JS
  decompressor that works on static hosts.
