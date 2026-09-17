# Game Portfolio

**Live site → <https://beckhamyeoh.github.io/GamePortfolio/>**

Unity games and prototypes, playable in the browser via WebGL. Built with
[Astro](https://astro.build) and deployed to GitHub Pages.

## Games

- **Ophir's Revenge** — boss fight made in a week for Boss Fight Jam, where a
  ranger with almost no arrows has to scavenge every shot back mid-fight; placed
  5th of 18 overall and 3rd in Game Design
- **Space SHMUP** — vertical shoot-'em-up with stacking power-ups, varied enemy
  patterns, and a multi-phase boss
- **Prospector** — solitaire-style card game with Bézier-animated card movement
  and a scoring system
- **Apple Picker** — arcade catch-the-apples loop with scoring and lives
- **Mission Demolition** — Angry-Birds-style physics game; pull back and launch
  projectiles to topple structures
- **Boids** — flocking AI built from separation, alignment, and cohesion rules

The home page also has an Arduino obstacle-avoidance rover, with video and the
full sketch.

## Tech

- Astro static site, with content collections for game metadata
- Unity WebGL builds served from `public/play/<slug>/`, kept separate from the
  `/games/<slug>/` info-page routes to avoid URL collisions
- Gzip-compressed builds with Unity's decompression fallback, so they load from
  GitHub Pages without custom headers
- Auto-deployed via GitHub Actions on every push to `main`

<details>
<summary>Local development & adding a game</summary>

### Local development

```bash
npm install
npm run dev      # http://localhost:4321/GamePortfolio
npm run build    # outputs to dist/
npm run preview  # serve the built site locally
```

### Adding a new game

1. Create `src/content/games/<slug>.md` with frontmatter:
   ```yaml
   ---
   title: "My Game"
   tagline: "Short description."
   thumbnail: "screenshots/<slug>.png"
   tech: ["Unity", "C#"]
   playable: false
   buildPath: "play/<slug>"
   repo: "https://github.com/beckhamyeoh/<repo>"
   order: 80
   ---
   ```
   Lower `order` values appear first. Markdown below the frontmatter becomes the
   game's page body.
2. Add a 16:9 screenshot at `public/screenshots/<slug>.png`.
3. (Optional) Build the game's WebGL target from Unity into
   `public/play/<slug>/`. See `public/play/README.md` for details.
4. Flip `playable: true` once the WebGL build is in place.

</details>
